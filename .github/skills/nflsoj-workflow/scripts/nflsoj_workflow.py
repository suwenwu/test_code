#!/usr/bin/env python3
"""
NFLSOJ 套题爬取工作流
======================
从 NFLSOJ (http://nfls.top:10443/barrier/14) 爬取套题并保存为洛谷格式。

使用方法：
  1. 列出所有可用套题:  python3 nflsoj_workflow.py --list
  2. 下载指定套题:      python3 nflsoj_workflow.py --download "套题名称"
  3. 下载多个套题:      python3 nflsoj_workflow.py --download "2024南京市" "NJ2025"
  4. 按序号下载:        python3 nflsoj_workflow.py --ids 319 305 269

首次运行时需要登录，账号密码通过环境变量传入：
  NFLSOJ_USER=your_username NFLSOJ_PASS=your_password python3 nflsoj_workflow.py --list

或者直接修改脚本中的 ACCOUNT 变量。
"""

import os
import sys
import json
import re
import argparse
from pathlib import Path

# ============ 配置区 ============
ACCOUNT = {
    "username": os.environ.get("NFLSOJ_USER", "2026xw027"),
    "password": os.environ.get("NFLSOJ_PASS", "Xw3.1415"),
}
BASE_URL = "http://nfls.top:10443"
OUTPUT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "XMW", "crawled_problems")
# ===============================


def parse_args():
    parser = argparse.ArgumentParser(description="NFLSOJ 套题爬取工具")
    parser.add_argument("--list", action="store_true", help="列出所有可用套题")
    parser.add_argument("--download", nargs="+", help="下载指定名称的套题")
    parser.add_argument("--ids", nargs="+", type=int, help="按 mission ID 下载套题")
    parser.add_argument("--all", action="store_true", help="下载所有套题")
    parser.add_argument("--output", default=OUTPUT_DIR, help="输出目录")
    parser.add_argument("--headless", action="store_true", help="无头模式运行")
    return parser.parse_args()


class NFLSOJSpider:
    """NFLSOJ 爬虫"""

    def __init__(self, output_dir=OUTPUT_DIR):
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)
        self.page = None
        self.browser = None
        self.context = None
        self._missions_cache = None
        self._problems_cache = {}

    def start(self, headless=False):
        """启动浏览器并登录"""
        from playwright.sync_api import sync_playwright

        self._pw = sync_playwright().start()
        self.browser = self._pw.chromium.launch(headless=headless)
        self.context = self.browser.new_context(
            viewport={"width": 1280, "height": 800}
        )
        self.page = self.context.new_page()

        # 登录
        print(f"🌐 打开 {BASE_URL}/home ...")
        self.page.goto(f"{BASE_URL}/home", wait_until="networkidle")
        self.page.wait_for_timeout(1000)

        # 检查是否已登录
        body = self.page.evaluate("document.body.innerText") or ""
        if "陈金洋" in (body or ""):
            print("✅ 已登录")
            return

        # 点击登录按钮
        print(f"🔑 登录中...")
        login_btn = self.page.locator("button").filter(has_text="登录")
        login_btn.first.click()
        self.page.wait_for_timeout(500)

        # 填写表单
        inputs = self.page.locator("input")
        count = inputs.count()
        for i in range(count):
            ph = inputs.nth(i).get_attribute("placeholder") or ""
            if "请输入" in ph:
                inputs.nth(i).fill(ACCOUNT["username"])
            if "8-16" in ph:
                inputs.nth(i).fill(ACCOUNT["password"])

        # 点击确定
        confirm = self.page.locator("button").filter(has_text="确")
        confirm.first.click()
        self.page.wait_for_timeout(2000)
        print("✅ 登录成功")

    def stop(self):
        """关闭浏览器"""
        if self.browser:
            self.browser.close()
        if hasattr(self, "_pw") and self._pw:
            self._pw.stop()

    def _navigate_to_barrier(self):
        """导航到关卡/套题页面"""
        print("  🚀 导航到套题页面...")
        self.page.goto(f"{BASE_URL}/barrier/14", wait_until="domcontentloaded")
        self.page.wait_for_timeout(3000)
        
        # 检查页面内容
        body = self.page.text_content("body") or ""
        
        # 如果看到"暂无关卡"说明页面没加载好，重试
        if "暂无关卡" in body:
            print("  ⚠️ 页面加载中，重试...")
            self.page.wait_for_timeout(3000)
            body = self.page.evaluate("document.body.innerText") or ""
        
        # 如果没有套题内容，点击"套题"选项卡
        if "套题" not in body or "人过关" not in body:
            print("  🔍 点击套题选项卡...")
            try:
                tabs = self.page.locator("text=套题")
                if tabs.count() > 0:
                    tabs.first.click()
                    self.page.wait_for_timeout(3000)
                    body = self.page.evaluate("document.body.innerText") or ""
            except:
                pass
        
        print(f"  📄 页面URL: {self.page.url}")
        has_missions = "人过关" in (body or "")
        print(f"  {'✅' if has_missions else '❌'} 页面包含套题列表")

    def list_missions(self):
        """解析页面获取套题名称列表"""
        if self._missions_cache:
            return self._missions_cache

        self._navigate_to_barrier()

        # 滚动到底部加载全部
        self.page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
        self.page.wait_for_timeout(800)

        # 获取页面文本解析名称
        body = self.page.evaluate("document.body.innerText") or ""

        # 调试：找出包含"人过关"的行的前后文
        lines = body.split('\n')
        print(f"  📝 页面共 {len(lines)} 行")
        
        missions = []
        for i in range(len(lines)):
            if '人过关' in lines[i] and i > 0:
                name = lines[i-1].strip()
                if not name or len(name) <= 1:
                    # 尝试更前面一行
                    if i > 1 and len(lines[i-2].strip()) > 1:
                        name = lines[i-2].strip()
                
                passed_str = lines[i].replace('人过关', '').strip()
                probs = 0
                # 查找题目数量
                for offset in [1, 2]:
                    if i + offset < len(lines):
                        import re as re2
                        pm = re2.search(r'(\d+)道题', lines[i + offset])
                        if pm:
                            probs = int(pm.group(1))
                            break
                
                if name and len(name) > 1:
                    missions.append({
                        "name": name,
                        "passed": int(passed_str) if passed_str.isdigit() else 0,
                        "problems": probs,
                    })

        # 去重
        seen = set()
        unique = []
        for m in missions:
            if m["name"] not in seen:
                seen.add(m["name"])
                unique.append(m)

        print(f"  📊 解析到 {len(unique)} 个套题")
        if len(unique) == 0:
            # 调试输出
            for i in range(min(50, len(lines))):
                if '人过关' in lines[i] or '关卡14' in lines[i] or (i > 0 and lines[i-1].strip() and len(lines[i-1].strip()) > 2 and '人过关' in lines[i]):
                    print(f"  🔍 行{i-1}:{lines[i-1][:30]} | 行{i}:{lines[i][:30]} | 行{i+1}:{lines[i+1][:30] if i+1 < len(lines) else ''}")

        self._missions_cache = unique
        return unique

    def find_mission_id(self, name):
        """通过点击套题获取其 mission ID"""
        self._navigate_to_barrier()
        self.page.wait_for_timeout(1000)
        self.page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
        self.page.wait_for_timeout(500)

        try:
            link = self.page.locator(f"text={name}").first
            link.click(timeout=5000)
            self.page.wait_for_timeout(1000)
            url = self.page.url
            m = re.search(r'/barrier/14/(\d+)', url)
            if m:
                return int(m.group(1))
        except:
            pass
        return None

    def get_mission_problems(self, mission_id):
        """获取指定 mission 的题目列表"""
        if mission_id in self._problems_cache:
            return self._problems_cache[mission_id]

        url = f"{BASE_URL}/api/level/14/mission/{mission_id}"
        resp = self.page.evaluate(f"""
            async () => {{
                const resp = await fetch('{url}');
                const data = await resp.json();
                return JSON.stringify(data);
            }}
        """)
        data = json.loads(resp)
        if data.get("code") != 0:
            print(f"  ❌ 获取 mission {mission_id} 失败: {data.get('message')}")
            return []

        # 导航到该 mission 的页面获取题目列表
        self.page.goto(f"{BASE_URL}/barrier/14/{mission_id}", wait_until="networkidle")
        self.page.wait_for_timeout(1000)

        # 从页面提取题目名称
        problems = self.page.evaluate("""
            () => {
                const card = document.querySelector('.card___3xSwl');
                if (!card) return [];
                const links = card.querySelectorAll('a');
                return Array.from(links).map(a => a.textContent.trim()).filter(t => t.length > 0);
            }
        """) or []

        self._problems_cache[mission_id] = problems
        return problems

    def get_problem_detail(self, problem_id):
        """获取题目详情"""
        resp = self.page.evaluate(f"""
            async () => {{
                const resp = await fetch('/api/questions/questionDetail/{problem_id}');
                const data = await resp.json();
                return JSON.stringify(data);
            }}
        """)
        data = json.loads(resp)
        if data.get("code") != 0:
            return None
        return data["data"]["currentQuestion"]

    def search_problem_id(self, title):
        """按标题搜索题目ID"""
        resp = self.page.evaluate(f"""
            async () => {{
                const resp = await fetch('/api/questions/questionList?pageSize=5000');
                const data = await resp.json();
                if (data.code !== 0) return '[]';
                const found = data.data.list.filter(q => q.title.includes('{title}'));
                return JSON.stringify(found);
            }}
        """)
        results = json.loads(resp)
        if results:
            return results[0]["id"]
        return None

    def batch_search_ids(self, titles):
        """批量搜索题目ID，返回 {title: id} 映射"""
        resp = self.page.evaluate(f"""
            async () => {{
                const resp = await fetch('/api/questions/questionList?pageSize=5000');
                const data = await resp.json();
                if (data.code !== 0) return '{{}}';
                const allQ = data.data.list;
                const searches = {json.dumps(titles)};
                const found = {{}};
                for (const q of allQ) {{
                    for (const term of searches) {{
                        if (q.title.includes(term)) {{
                            found[q.title] = q.id;
                            break;
                        }}
                    }}
                }}
                return JSON.stringify(found);
            }}
        """)
        return json.loads(resp)

    def format_luogu(self, name, problem):
        """格式化为洛谷风格 Markdown"""
        qd = problem.get("questionDetail", {})
        
        # 清理内容
        def clean(text):
            if not text:
                return ""
            text = text.replace("<br>", "\n").replace("<br/>", "\n").replace("<br />", "\n")
            text = re.sub(r'<img[^>]*>', '', text)
            text = text.replace("<u>", "").replace("</u>", "")
            text = text.replace("<strong/>", "").replace("<strong>", "").replace("</strong>", "")
            return text

        content = clean(qd.get("content", ""))
        in_fmt = clean(qd.get("inFormat", ""))
        out_fmt = clean(qd.get("outFormat", ""))
        data_range = clean(qd.get("dataRangePrompts", ""))

        # 解析样例
        examples = []
        try:
            raw = qd.get("inOutExample", "[]")
            examples = json.loads(raw) if isinstance(raw, str) else raw
        except:
            pass

        lines = [
            f"# {name}",
            "",
            f"> 时空限制：{qd.get('timeLimit', 1)}秒 / {qd.get('memoryLimit', 128)}MB",
            "",
            "## 题目描述",
            "",
            content,
            "",
            "## 输入格式",
            "",
            in_fmt,
            "",
            "## 输出格式",
            "",
            out_fmt,
            "",
            "## 输入输出样例",
            "",
        ]
        for ex in examples:
            lines += [
                "```input",
                ex.get("inExample", ""),
                "```",
                "",
                "```output",
                ex.get("outExample", ""),
                "```",
                "",
            ]
            if ex.get("description"):
                lines += ["**说明：** " + clean(ex["description"]), ""]

        if data_range.strip():
            lines += ["## 数据范围与提示", "", data_range, ""]

        return "\n".join(lines)

    def download_mission(self, mission_id, set_name=None):
        """下载指定 mission 的所有题目"""
        print(f"\n📦 下载: {set_name or f'Mission {mission_id}'}")

        # 导航到该 mission 的页面
        self.page.goto(f"{BASE_URL}/barrier/14/{mission_id}", wait_until="networkidle")
        self.page.wait_for_timeout(1000)

        # 获取题目名称列表
        problems = self.page.evaluate("""
            () => {
                const card = document.querySelector('.card___3xSwl');
                if (!card) return [];
                const links = card.querySelectorAll('a');
                return Array.from(links).map(a => a.textContent.trim()).filter(t => t.length > 0);
            }
        """) or []

        if not problems:
            print(f"  ❌ 未找到题目")
            return 0

        print(f"  📝 找到 {len(problems)} 道题: {', '.join(problems[:3])}...")

        # 批量搜索题目ID
        id_map = self.batch_search_ids(problems)

        # 创建输出目录
        set_dir = self.output_dir / (set_name or f"Mission_{mission_id}")
        set_dir.mkdir(parents=True, exist_ok=True)

        success = 0
        for title in problems:
            # 查找ID
            pid = id_map.get(title)
            if not pid:
                pid = self.search_problem_id(title)
            if not pid:
                print(f"  ⚠️ 未找到题目ID: {title}")
                continue

            # 获取详情
            detail = self.get_problem_detail(pid)
            if not detail:
                print(f"  ⚠️ 获取失败: {title}")
                continue

            # 格式化为洛谷格式
            md = self.format_luogu(title, detail)

            # 保存文件
            safe_name = re.sub(r'[\\/:*?"<>|]', '', title.replace(" ", "_"))
            filepath = set_dir / f"{safe_name}.md"
            with open(filepath, "w", encoding="utf-8") as f:
                f.write(md)
            print(f"  ✅ {title}")
            success += 1

        print(f"\n📊 完成: {success}/{len(problems)} 题已保存到 {set_dir}")
        return success


def main():
    args = parse_args()
    spider = NFLSOJSpider(output_dir=args.output)

    try:
        spider.start(headless=args.headless)

        if args.list:
            missions = spider.list_missions()
            print(f"\n{'='*60}")
            print(f"📋 共找到 {len(missions)} 个套题:")
            print(f"{'='*60}")
            for i, m in enumerate(missions, 1):
                print(f"  {i:3d}. {m['name']:30s}  {m['problems']}题  {m['passed']}人过关")
            print(f"{'='*60}")
            print(f"下载示例: python3 {sys.argv[0]} --download \"2024南京市\" \"NJ2025\"")

        elif args.download:
            missions = spider.list_missions()
            
            for query in args.download:
                # 完全匹配
                matched = [m for m in missions if m["name"] == query]
                if not matched:
                    # 模糊匹配
                    matched = [m for m in missions if query in m["name"]]
                
                if matched:
                    for m in matched:
                        print(f"  找到: {m['name']}")
                        mid = spider.find_mission_id(m["name"])
                        if mid:
                            spider.download_mission(mid, set_name=m["name"])
                        else:
                            print(f"  ❌ 无法获取 {m['name']} 的 mission ID")
                else:
                    print(f"  ❌ 未找到套题: {query}")
                    print(f"  使用 --list 查看所有可用套题")

        elif args.ids:
            for mid in args.ids:
                spider.download_mission(mid, set_name=f"Mission_{mid}")

        elif args.all:
            missions = spider.list_missions()
            print(f"\n📋 共 {len(missions)} 个套题，开始下载...")
            for m in missions:
                print(f"\n🔍 查找 {m['name']} 的 mission ID...")
                mid = spider.find_mission_id(m["name"])
                if mid:
                    spider.download_mission(mid, set_name=m["name"])
                else:
                    print(f"  ❌ 无法获取 {m['name']} 的 mission ID")

        else:
            print("请指定操作，使用 --help 查看帮助")

    finally:
        spider.stop()


if __name__ == "__main__":
    main()
