#!/usr/bin/env python3
"""
NFLSOJ 套题爬取工具 - 异步并发版
===================================
运行后按提示输入账号密码，选择要下载的套题即可。
支持同时下载多套题目，同一套题内并发获取题目详情，大幅提升速度。
"""

import asyncio
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

# ─── 依赖检测 ──────────────────────────────────────────
try:
    from playwright.async_api import async_playwright
except ImportError:
    print("❌ 缺少依赖 playwright，正在安装...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "playwright"])
    subprocess.check_call([sys.executable, "-m", "playwright", "install", "chromium"])
    from playwright.async_api import async_playwright

# ─── 路径与并发配置 ────────────────────────────────────
BASE_URL = "http://nfls.top:10443"
SCRIPT_DIR = Path(__file__).parent
OUTPUT_DIR = SCRIPT_DIR.parent / "XMW" / "crawled_problems"

# ─── 并发控制 ──────────────────────────────────────────
MAX_CONCURRENT_MISSIONS = 3    # 最多同时下载几个套题
MAX_CONCURRENT_API = 15        # 每套题内同时发起的 API 请求数


# ════════════════════════════════════════════════════════
#  主体
# ════════════════════════════════════════════════════════
class NFLSOJCrawler:
    def __init__(self):
        self.browser = None
        self.context = None
        self.pw = None
        self.missions = []

    # ── 启动 & 登录 ────────────────────────────────────
    async def login(self, username, password):
        print("\n🔑 正在登录...")
        self.pw = await async_playwright().start()
        self.browser = await self.pw.chromium.launch(headless=False)
        self.context = await self.browser.new_context()

        page = await self.context.new_page()
        try:
            await page.goto(f"{BASE_URL}/home", wait_until="networkidle")
            await page.wait_for_timeout(1000)

            body = await page.evaluate("document.body.innerText") or ""
            if "陈金洋" in body:
                print("✅ 已登录")
                return

            # 点登录按钮
            btn = page.locator("button").filter(has_text="登录")
            await btn.first.click()
            await page.wait_for_timeout(500)

            # 填表单
            inputs = page.locator("input")
            for i in range(await inputs.count()):
                ph = await inputs.nth(i).get_attribute("placeholder") or ""
                if "请输入" in ph:
                    await inputs.nth(i).fill(username)
                if "8-16" in ph:
                    await inputs.nth(i).fill(password)

            # 点确定
            ok = page.locator("button").filter(has_text="确")
            await ok.first.click()
            await page.wait_for_timeout(2000)
            print("✅ 登录成功")
        finally:
            await page.close()

    # ── 获取套题列表 ────────────────────────────────────
    async def fetch_mission_list(self):
        print("\n📡 正在获取套题列表...")
        page = await self.context.new_page()
        try:
            await page.goto(f"{BASE_URL}/barrier/14", wait_until="domcontentloaded")
            await page.wait_for_timeout(3000)

            # 如果没加载出来就点"套题"选项卡
            body = await page.evaluate("document.body.innerText") or ""
            if "人过关" not in body:
                tabs = page.locator("text=套题")
                if await tabs.count():
                    await tabs.first.click()
                    await page.wait_for_timeout(3000)
                    body = await page.evaluate("document.body.innerText") or ""

            # 滚动到底
            await page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
            await page.wait_for_timeout(500)

            lines = body.split("\n")
            missions = []
            for i, line in enumerate(lines):
                if "人过关" in line and i > 0:
                    name = lines[i - 1].strip()
                    if not name or len(name) <= 1:
                        continue
                    probs = 0
                    for off in [1, 2]:
                        if i + off < len(lines):
                            m = re.search(r"(\d+)道题", lines[i + off])
                            if m:
                                probs = int(m.group(1))
                                break
                    missions.append({"name": name, "problems": probs})

            # 去重
            seen = set()
            self.missions = []
            for m in missions:
                if m["name"] not in seen:
                    seen.add(m["name"])
                    self.missions.append(m)
            return self.missions
        finally:
            await page.close()

    # ── 显示菜单 ────────────────────────────────────────
    def show_menu(self):
        print(f"\n{'='*60}")
        print(f"📋 共 {len(self.missions)} 个可用套题:")
        print(f"{'='*60}")
        for i, m in enumerate(self.missions, 1):
            print(f"  {i:3d}. {m['name']:<30s} ({m['problems']}题)")
        print(f"{'='*60}")
        print(f"    0. 退出")
        print(f"    a. 下载全部  (并发 {MAX_CONCURRENT_MISSIONS} 套)")
        print(f"{'='*60}")

    # ── 获取 mission ID（在指定 page 上操作）────────────
    async def _get_mission_id(self, page, name):
        try:
            await page.goto(f"{BASE_URL}/barrier/14", wait_until="domcontentloaded")
            await page.wait_for_timeout(2000)
            await page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
            await page.wait_for_timeout(300)
            await page.locator(f"text={name}").first.click(timeout=5000)
            await page.wait_for_timeout(1000)
            m = re.search(r"/barrier/14/(\d+)", page.url)
            return int(m.group(1)) if m else None
        except Exception:
            return None

    # ── 从套题页提取题目名称列表 ──────────────────────
    async def _get_titles(self, page, mission_id):
        await page.goto(f"{BASE_URL}/barrier/14/{mission_id}", wait_until="networkidle")
        await page.wait_for_timeout(1000)
        titles = await page.evaluate("""
            () => {
                const card = document.querySelector('.card___3xSwl');
                if (!card) return [];
                return Array.from(card.querySelectorAll('a')).map(a => a.textContent.trim()).filter(t => t);
            }
        """) or []
        return titles

    # ── 批量搜索题目 ID ────────────────────────────────
    async def _batch_search_ids(self, page, titles):
        data = await page.evaluate(f"""
            async () => {{
                const r = await fetch('/api/questions/questionList?pageSize=5000');
                const d = await r.json();
                if (d.code !== 0) return '{{}}';
                const list = d.data.list;
                const search = {json.dumps(titles)};
                const found = {{}};
                for (const q of list)
                    for (const t of search)
                        if (q.title.includes(t)) {{ found[q.title] = q.id; break; }}
                return JSON.stringify(found);
            }}
        """)
        return json.loads(data)

    # ── 单个搜索题目 ID（兜底）───────────────────────────
    async def _search_single_id(self, page, title):
        data = await page.evaluate(f"""
            async () => {{
                const r = await fetch('/api/questions/questionList?pageSize=5000');
                const d = await r.json();
                if (d.code !== 0) return null;
                const q = d.data.list.find(q => q.title.includes('{title}'));
                return q ? q.id : null;
            }}
        """)
        return data

    # ── 获取题目详情 ────────────────────────────────────
    async def _get_detail(self, page, pid):
        data = await page.evaluate(f"""
            async () => {{
                const r = await fetch('/api/questions/questionDetail/{pid}');
                const d = await r.json();
                return JSON.stringify(d);
            }}
        """)
        d = json.loads(data)
        return d.get("data", {}).get("currentQuestion") if d.get("code") == 0 else None

    # ── 格式化洛谷 Markdown ────────────────────────────
    def format_luogu(self, name, q):
        qd = q.get("questionDetail", {})

        def clean(t):
            if not t:
                return ""
            for tag in ["<br>", "<br/>", "<br />"]:
                t = t.replace(tag, "\n")
            return re.sub(r"<[^>]+>", "", t).replace("<u>", "").replace("</u>", "")

        content = clean(qd.get("content"))
        infmt = clean(qd.get("inFormat"))
        outfmt = clean(qd.get("outFormat"))
        dr = clean(qd.get("dataRangePrompts"))

        exs = []
        try:
            raw = qd.get("inOutExample", "[]")
            exs = json.loads(raw) if isinstance(raw, str) else raw
        except Exception:
            pass

        lines = [
            f"# {name}", "",
            f"> 时空限制：{qd.get('timeLimit', 1)}秒 / {qd.get('memoryLimit', 128)}MB", "",
            "## 题目描述", "", content, "",
            "## 输入格式", "", infmt, "",
            "## 输出格式", "", outfmt, "",
            "## 输入输出样例", "",
        ]
        for ex in exs:
            lines += [
                "```input",
                ex.get("inExample", ""),
                "```", "",
                "```output",
                ex.get("outExample", ""),
                "```", "",
            ]
            if ex.get("description"):
                lines += ["**说明：** " + clean(ex["description"]), ""]
        if dr.strip():
            lines += ["## 数据范围与提示", "", dr, ""]

        return "\n".join(lines)

    # ── 下载单个套题（每个套题使用独立 page）───────────
    async def download_mission(self, mission_name):
        page = await self.context.new_page()
        try:
            # 1. 获取 mission ID
            mid = await self._get_mission_id(page, mission_name)
            if not mid:
                print(f"  ❌ 无法获取「{mission_name}」的 ID")
                return 0, 0

            # 2. 获取题目名称列表
            titles = await self._get_titles(page, mid)
            if not titles:
                print(f"  ❌ 「{mission_name}」未找到题目")
                return 0, 0

            print(f"  📝 {mission_name}: 找到 {len(titles)} 道题")

            # 3. 批量搜索题目 ID
            id_map = await self._batch_search_ids(page, titles)

            # 4. 收集有效 (title, pid) 对（单题搜索兜底）
            to_fetch = []
            for title in titles:
                pid = id_map.get(title)
                if not pid:
                    pid = await self._search_single_id(page, title)
                if pid:
                    to_fetch.append((title, pid))
                else:
                    print(f"  ⚠️ 跳过: {mission_name} / {title}")

            if not to_fetch:
                print(f"  ⚠️ {mission_name}: 没有可下载的题目")
                return 0, len(titles)

            # 5. 创建输出目录
            out_dir = OUTPUT_DIR / mission_name
            out_dir.mkdir(parents=True, exist_ok=True)

            # 6. 并发获取题目详情并写入文件
            sem = asyncio.Semaphore(MAX_CONCURRENT_API)

            async def fetch_and_save(title, pid):
                async with sem:
                    detail = await self._get_detail(page, pid)
                    if not detail:
                        return False
                    md = self.format_luogu(title, detail)
                    safe_name = re.sub(r'[\\/:*?"<>|]', "", title.replace(" ", "_"))
                    (out_dir / f"{safe_name}.md").write_text(md, encoding="utf-8")
                    print(f"    ✅ {title}")
                    return True

            results = await asyncio.gather(
                *[fetch_and_save(t, p) for t, p in to_fetch]
            )
            ok = sum(1 for r in results if r)
            print(f"\n  📊 {mission_name}: {ok}/{len(titles)} 题 → {out_dir}")
            return ok, len(titles)
        finally:
            await page.close()

    # ── 并发下载多个套题 ────────────────────────────────
    async def download_missions(self, selected):
        sem = asyncio.Semaphore(MAX_CONCURRENT_MISSIONS)

        async def run_one(m):
            async with sem:
                return await self.download_mission(m["name"])

        tasks = [run_one(m) for m in selected]
        results = await asyncio.gather(*tasks, return_exceptions=True)

        total_ok = 0
        total_all = 0
        for r in results:
            if isinstance(r, Exception):
                print(f"  ❌ 套题下载异常: {r}")
            else:
                total_ok += r[0]
                total_all += r[1]

        print(f"\n{'='*60}")
        print(f"🏁 全部任务完成: {total_ok}/{total_all} 题")

    # ── 清理 ────────────────────────────────────────────
    async def close(self):
        if self.context:
            await self.context.close()
        if self.browser:
            await self.browser.close()
        if self.pw:
            await self.pw.stop()

    # ── 主交互流程 ──────────────────────────────────────
    async def run(self):
        print("=" * 54)
        print("   🏫  NFLSOJ 套题爬取工具  (异步并发版)")
        print(f"   并发: 最多 {MAX_CONCURRENT_MISSIONS} 套 / "
              f"每套 {MAX_CONCURRENT_API} 个请求")
        print("=" * 54)

        try:
            # 1. 登录
            username = input("\n👤 账号: ").strip()
            password = input("🔑 密码: ").strip()
            await self.login(username, password)

            # 2. 获取套题列表
            missions = await self.fetch_mission_list()
            if not missions:
                print("❌ 未获取到套题列表")
                return

            # 3. 交互选择
            while True:
                self.show_menu()
                choice = input("📌 请选择编号 (输入序号, 用逗号分隔多个): ").strip()

                if choice == "0":
                    print("👋 再见！")
                    break

                elif choice.lower() == "a":
                    confirm = input(
                        f"⚠️  确定下载全部 {len(missions)} 套题？"
                        f"(y/N): "
                    ).strip().lower()
                    if confirm == "y":
                        await self.download_missions(missions)
                    else:
                        print("已取消")

                else:
                    indices = []
                    for part in choice.split(","):
                        part = part.strip()
                        try:
                            idx = int(part)
                            if 1 <= idx <= len(missions):
                                indices.append(idx - 1)
                            else:
                                print(f"  ⚠️ 序号 {idx} 超出范围")
                        except ValueError:
                            print(f"  ⚠️ 无法解析: {part}")

                    if indices:
                        selected = [missions[i] for i in indices]
                        await self.download_missions(selected)

        except KeyboardInterrupt:
            print("\n\n👋 已取消")
        finally:
            await self.close()


# ════════════════════════════════════════════════════════
#  入口
# ════════════════════════════════════════════════════════
def main():
    crawler = NFLSOJCrawler()
    asyncio.run(crawler.run())


if __name__ == "__main__":
    main()
