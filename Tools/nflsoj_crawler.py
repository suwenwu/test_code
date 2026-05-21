#!/usr/bin/env python3
"""
NFLSOJ 套题爬取工具 - 交互式版
=================================
运行后按提示输入账号密码，选择要下载的套题即可。
"""

import os, sys, json, re, subprocess, shutil
from pathlib import Path

# ─── 依赖检测 ──────────────────────────────────────────
try:
    from playwright.sync_api import sync_playwright
except ImportError:
    print("❌ 缺少依赖 playwright，正在安装...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "playwright"])
    subprocess.check_call([sys.executable, "-m", "playwright", "install", "chromium"])
    from playwright.sync_api import sync_playwright

# ─── 路径 ──────────────────────────────────────────────
BASE_URL = "http://nfls.top:10443"
SCRIPT_DIR = Path(__file__).parent
OUTPUT_DIR = SCRIPT_DIR.parent / "XMW" / "crawled_problems"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


# ════════════════════════════════════════════════════════
#  主体
# ════════════════════════════════════════════════════════
class NFLSOJInteractive:
    def __init__(self):
        self.page = None
        self.browser = None
        self.pw = None
        self.missions = []

    # ── 启动 & 登录 ────────────────────────────────────
    def login(self, username, password):
        print("\n🔑 正在登录...")
        self.pw = sync_playwright().start()
        self.browser = self.pw.chromium.launch(headless=False)
        page = self.browser.new_page()
        self.page = page

        page.goto(f"{BASE_URL}/home", wait_until="networkidle")
        page.wait_for_timeout(1000)

        body = page.evaluate("document.body.innerText") or ""
        if "陈金洋" in body:
            print("✅ 已登录")
            return

        # 点登录按钮
        btn = page.locator("button").filter(has_text="登录")
        btn.first.click()
        page.wait_for_timeout(500)

        # 填表单
        inputs = page.locator("input")
        for i in range(inputs.count()):
            ph = inputs.nth(i).get_attribute("placeholder") or ""
            if "请输入" in ph:
                inputs.nth(i).fill(username)
            if "8-16" in ph:
                inputs.nth(i).fill(password)

        # 点确定
        ok = page.locator("button").filter(has_text="确")
        ok.first.click()
        page.wait_for_timeout(2000)
        print("✅ 登录成功")

    # ── 获取套题列表 ────────────────────────────────────
    def fetch_mission_list(self):
        print("\n📡 正在获取套题列表...")
        self.page.goto(f"{BASE_URL}/barrier/14", wait_until="domcontentloaded")
        self.page.wait_for_timeout(3000)

        # 如果没加载出来就点"套题"选项卡
        body = self.page.evaluate("document.body.innerText") or ""
        if "人过关" not in body:
            tabs = self.page.locator("text=套题")
            if tabs.count():
                tabs.first.click()
                self.page.wait_for_timeout(3000)
                body = self.page.evaluate("document.body.innerText") or ""

        # 滚动到底
        self.page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
        self.page.wait_for_timeout(500)

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

    # ── 显示菜单 ────────────────────────────────────────
    def show_menu(self):
        print(f"\n{'='*60}")
        print(f"📋 共 {len(self.missions)} 个可用套题:")
        print(f"{'='*60}")
        for i, m in enumerate(self.missions, 1):
            print(f"  {i:3d}. {m['name']:<30s} ({m['problems']}题)")
        print(f"{'='*60}")
        print(f"    0. 退出")
        print(f"    a. 下载全部")
        print(f"{'='*60}")

    # ── 获取 mission ID ────────────────────────────────
    def get_mission_id(self, name):
        try:
            self.page.goto(f"{BASE_URL}/barrier/14", wait_until="domcontentloaded")
            self.page.wait_for_timeout(2000)
            self.page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
            self.page.wait_for_timeout(300)
            self.page.locator(f"text={name}").first.click(timeout=5000)
            self.page.wait_for_timeout(1000)
            m = re.search(r"/barrier/14/(\d+)", self.page.url)
            return int(m.group(1)) if m else None
        except:
            return None

    # ── 批量搜索题目ID ──────────────────────────────────
    def batch_search_ids(self, titles):
        data = self.page.evaluate(f"""
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

    # ── 获取题目详情 ────────────────────────────────────
    def get_detail(self, pid):
        data = self.page.evaluate(f"""
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
            if not t: return ""
            for tag in ["<br>", "<br/>", "<br />"]: t = t.replace(tag, "\n")
            return re.sub(r"<[^>]+>", "", t).replace("<u>", "").replace("</u>", "")

        content = clean(qd.get("content"))
        infmt = clean(qd.get("inFormat"))
        outfmt = clean(qd.get("outFormat"))
        dr = clean(qd.get("dataRangePrompts"))

        exs = []
        try:
            raw = qd.get("inOutExample", "[]")
            exs = json.loads(raw) if isinstance(raw, str) else raw
        except:
            pass

        lines = [
            f"# {name}", "",
            f"> 时空限制：{qd.get('timeLimit',1)}秒 / {qd.get('memoryLimit',128)}MB", "",
            "## 题目描述", "", content, "",
            "## 输入格式", "", infmt, "",
            "## 输出格式", "", outfmt, "",
            "## 输入输出样例", "",
        ]
        for ex in exs:
            lines += ["```input", ex.get("inExample", ""), "```", "",
                       "```output", ex.get("outExample", ""), "```", ""]
            if ex.get("description"):
                lines += ["**说明：** " + clean(ex["description"]), ""]
        if dr.strip():
            lines += ["## 数据范围与提示", "", dr, ""]

        return "\n".join(lines)

    # ── 下载单个套题 ────────────────────────────────────
    def download(self, mission_name):
        print(f"\n📦 正在下载: {mission_name}")
        mid = self.get_mission_id(mission_name)
        if not mid:
            print(f"  ❌ 无法获取 {mission_name} 的 ID")
            return

        # 进入套题页面获取题目名称
        self.page.goto(f"{BASE_URL}/barrier/14/{mid}", wait_until="networkidle")
        self.page.wait_for_timeout(1000)
        titles = self.page.evaluate("""
            () => {
                const card = document.querySelector('.card___3xSwl');
                if (!card) return [];
                return Array.from(card.querySelectorAll('a')).map(a => a.textContent.trim()).filter(t => t);
            }
        """) or []

        if not titles:
            print("  ❌ 未找到题目")
            return

        print(f"  📝 找到 {len(titles)} 道题")

        # 搜索 ID
        id_map = self.batch_search_ids(titles)

        # 创建目录
        out = OUTPUT_DIR / mission_name
        out.mkdir(parents=True, exist_ok=True)

        ok = 0
        for title in titles:
            pid = id_map.get(title)
            if not pid:
                # 逐个搜索
                data = self.page.evaluate(f"""
                    async () => {{
                        const r = await fetch('/api/questions/questionList?pageSize=5000');
                        const d = await r.json();
                        if (d.code !== 0) return null;
                        const q = d.data.list.find(q => q.title.includes('{title}'));
                        return q ? q.id : null;
                    }}
                """)
                pid = data

            if not pid:
                print(f"  ⚠️ 跳过: {title}")
                continue

            detail = self.get_detail(pid)
            if not detail:
                print(f"  ⚠️ 获取失败: {title}")
                continue

            md = self.format_luogu(title, detail)
            safe = re.sub(r'[\\/:*?"<>|]', "", title.replace(" ", "_"))
            (out / f"{safe}.md").write_text(md, encoding="utf-8")
            print(f"  ✅ {title}")
            ok += 1

        print(f"\n📊 完成: {ok}/{len(titles)} 题 → {out}")

    # ── 清理 ────────────────────────────────────────────
    def close(self):
        if self.browser:
            self.browser.close()
        if self.pw:
            self.pw.stop()


# ════════════════════════════════════════════════════════
#  入口
# ════════════════════════════════════════════════════════
def main():
    print("=" * 54)
    print("   🏫  NFLSOJ 套题爬取工具  (交互式)")
    print("=" * 54)

    spider = NFLSOJInteractive()
    try:
        # ── 1. 登录 ──
        username = input("\n👤 账号: ").strip()
        password = input("🔑 密码: ").strip()
        spider.login(username, password)

        # ── 2. 获取列表 ──
        missions = spider.fetch_mission_list()
        if not missions:
            print("❌ 未获取到套题列表")
            return

        while True:
            spider.show_menu()
            choice = input("📌 请选择编号 (输入序号, 用逗号分隔多个): ").strip()

            if choice == "0":
                print("👋 再见！")
                break

            elif choice.lower() == "a":
                confirm = input(f"⚠️  确定下载全部 {len(missions)} 套题？(y/N): ").strip().lower()
                if confirm == "y":
                    for m in missions:
                        spider.download(m["name"])
                else:
                    print("已取消")

            else:
                # 解析序号
                indices = []
                for part in choice.split(","):
                    part = part.strip()
                    try:
                        idx = int(part)
                        if 1 <= idx <= len(missions):
                            indices.append(idx - 1)
                        else:
                            print(f"  ⚠️ 序号 {idx} 超出范围")
                    except:
                        print(f"  ⚠️ 无法解析: {part}")

                if indices:
                    for idx in indices:
                        spider.download(missions[idx]["name"])

    except KeyboardInterrupt:
        print("\n\n👋 已取消")
    finally:
        spider.close()


if __name__ == "__main__":
    main()
