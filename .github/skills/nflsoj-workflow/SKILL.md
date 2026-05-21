---
name: nflsoj-workflow
description: '爬取 NFLSOJ (http://nfls.top:10443) 上的竞赛套题，保存为洛谷格式 Markdown。Use when: 需要下载NFLSOJ题目、爬取套题、同步ACGO题目、备份竞赛试题、获取南京/江苏历年市赛省赛试题。参数：--list 列出套题，--download "名称" 按名下载，--ids 按ID下载。'
user-invocable: true
argument-hint: '--list | --download "套题名称" | --ids 123 456'
---

# NFLSOJ 套题爬取工作流

从 NFLSOJ (http://nfls.top:10443/barrier/14) 爬取竞赛套题（南京/江苏市赛省赛等），保存为洛谷格式 Markdown。

## 使用方法

```bash
# 列出所有套题
python3 scripts/nflsoj_workflow.py --list

# 按名称下载
python3 scripts/nflsoj_workflow.py --download "2024南京市"
python3 scripts/nflsoj_workflow.py --download "NJ2025"

# 按 mission ID 下载
python3 scripts/nflsoj_workflow.py --ids 269 305 319

# 无头模式（不弹出浏览器）
python3 scripts/nflsoj_workflow.py --download "2024江苏省赛" --headless
```

## 参数说明

| 参数 | 说明 |
|------|------|
| `--list` | 列出全部可用套题（共60套） |
| `--download "名称"` | 按名称下载（支持模糊匹配） |
| `--ids 1 2 3` | 按 mission ID 下载 |
| `--all` | 下载全部套题 |
| `--headless` | 无头模式运行 |
| `--output 路径` | 自定义输出目录（默认: XMW/crawled_problems/） |

## 输出位置

题目保存到 `XMW/crawled_problems/`，每套题一个子目录，每道题一个 `.md` 文件，格式：

```
# 题目名称

> 时空限制：1秒 / 128MB

## 题目描述
...
## 输入格式
...
## 输出格式
...
## 输入输出样例
```input
...
```output
...
## 数据范围与提示
...
```

## 账号配置

脚本内置了默认账号，也可通过环境变量覆盖：

```bash
NFLSOJ_USER=账号 NFLSOJ_PASS=密码 python3 scripts/nflsoj_workflow.py --list
```

## 工作流步骤（供 Agent 参考）

1. **列出套题** → 用户输入 `/nflsoj` 或提及"套题"时，运行 `--list`
2. **下载指定套题** → 用户给出套题名称时，用 `--download "名称"` 下载
3. **处理多个套题** → 可在一次命令中传入多个名称
4. **结果输出** → 所有文件保存到 `XMW/crawled_problems/` 对应目录
