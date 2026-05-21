#!/usr/bin/env python3
"""
2024南京市信息与未来 - 测试数据生成脚本
为6道题各生成20个刁钻测试点，打包为zip（解压后直接是in/out文件）
"""

import os
import random
import subprocess
import zipfile
import shutil
import math
import sys
from collections import Counter

BASE_DIR = "/Users/s/Documents/workspace/vscode/XMW/信息与未来/2024南京"
OUTPUT_DIR = "/Users/s/Documents/workspace/vscode/XMW/测试数据_2024"

PROBLEMS = [
    "左邻右舍",
    "中位数",
    "乐乐玩木棒",
    "书签制作",
    "城镇地图",
    "趣味进制",
]


def get_cpp_path(name):
    return os.path.join(BASE_DIR, f"{name}.cpp")


def get_bin_path(name):
    return os.path.join(BASE_DIR, f"{name}_bin")


def compile_cpp(name):
    src = get_cpp_path(name)
    dst = get_bin_path(name)
    print(f"  编译 {name}...", end=" ", flush=True)
    result = subprocess.run(
        ["/usr/bin/clang++", "-std=c++23", "-O2", "-o", dst, src],
        capture_output=True, text=True, timeout=30
    )
    if result.returncode != 0:
        print(f"失败: {result.stderr[:100]}")
        return False
    print("成功")
    return True


def run_cpp(name, input_str):
    bin_path = get_bin_path(name)
    result = subprocess.run(
        [bin_path],
        input=input_str,
        capture_output=True, text=True, timeout=10
    )
    return result.stdout.strip()


def make_test_dir(problem_name):
    path = os.path.join(OUTPUT_DIR, problem_name)
    os.makedirs(path, exist_ok=True)
    return path


def write_test_case(problem_name, case_id, input_str, output_str):
    dir_path = make_test_dir(problem_name)
    in_path = os.path.join(dir_path, f"{case_id:02d}.in")
    out_path = os.path.join(dir_path, f"{case_id:02d}.out")
    with open(in_path, "w") as f:
        f.write(input_str.strip() + "\n")
    with open(out_path, "w") as f:
        f.write(output_str.strip() + "\n")


def zip_problem(problem_name):
    dir_path = os.path.join(OUTPUT_DIR, problem_name)
    zip_path = os.path.join(OUTPUT_DIR, f"{problem_name}.zip")
    with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zf:
        for fname in sorted(os.listdir(dir_path)):
            if fname.endswith('.in') or fname.endswith('.out'):
                full_path = os.path.join(dir_path, fname)
                zf.write(full_path, arcname=fname)
    file_size = os.path.getsize(zip_path)
    print(f"  {problem_name}.zip ({file_size} bytes)")


# ==================== 左邻右舍 ====================

def generate_左邻右舍():
    """n个人围成圈，找x的左右邻居（从小到大输出）"""
    name = "左邻右舍"
    print(f"\n▶ {name}")
    cid = 0

    cases = []
    
    # 1-3: n=3 (最小) 的各种情况
    cases.append((3, 1, "最小n=3, x=1, 邻居是2和3"))
    cases.append((3, 2, "最小n=3, x=2, 邻居是1和3"))
    cases.append((3, 3, "最小n=3, x=3, 邻居是1和2"))
    
    # 4-5: n=4, 各种边界
    cases.append((4, 1, "n=4, x=1边界"))
    cases.append((4, 4, "n=4, x=4边界"))
    
    # 6-8: 一般情况
    cases.append((10, 5, "n=10中间, x=5"))
    cases.append((10, 6, "n=10中间, x=6"))
    cases.append((20, 7, "n=20, x=7"))
    
    # 9-12: 各种n的边界
    cases.append((50, 1, "n=50, x=1"))
    cases.append((50, 50, "n=50, x=50"))
    cases.append((100, 1, "n=100最大, x=1边界"))
    cases.append((100, 100, "n=100最大, x=100边界"))
    
    # 13-16: 中间位置
    cases.append((30, 15, "n=30, x=15"))
    cases.append((60, 30, "n=60, x=30"))
    cases.append((80, 40, "n=80, x=40"))
    cases.append((100, 50, "n=100, x=50中央"))
    
    # 17-20: 更多刁钻值
    cases.append((7, 4, "n=7, x=4"))
    cases.append((99, 50, "n=99奇数, x=50"))
    cases.append((100, 99, "n=100, x=99近边界"))
    cases.append((100, 2, "n=100, x=2近边界"))

    for n, x, desc in cases:
        cid += 1
        inp = f"{n} {x}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")


# ==================== 中位数 ====================

def generate_中位数():
    """找中位数（大于和小于它的元素数量相等），否则-1"""
    name = "中位数"
    print(f"\n▶ {name}")
    cid = 0

    # 直接用程序的输出
    def make_case(arr, desc):
        nonlocal cid
        cid += 1
        n = len(arr)
        inp = f"{n}\n" + " ".join(map(str, arr))
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: 样例1 - 有中位数 (n=5)
    make_case([1, 4, 2, 5, 7], "样例1: 有中位数4")
    
    # 2: 样例2 - 无中位数 (n=4)
    make_case([1, 5, 8, 3], "样例2: 无中位数→-1")
    
    # 3: 样例3
    make_case([66, 53, 47, 86, 18, 21, 97, 92, 15], "样例3: 中位数53")
    
    # 4: n=1, 唯一元素就是中位数
    make_case([42], "n=1单元素→42")
    
    # 5: n=2 → 无中位数
    make_case([1, 2], "n=2→无中位数-1")
    
    # 6: n=3, 中间的是中位数
    make_case([10, 5, 1], "n=3, 排序后中间是5")
    
    # 7: n=3, 中间的不是中位数（因为元素不重复不可能）
    # 实际上排序后 [1,3,5] 中间3, 小于1个大于1个 → 是中位数
    make_case([1, 3, 5], "n=3, 3是中位数")
    
    # 8: n=6偶数, 无中位数
    make_case([1, 2, 3, 4, 5, 6], "n=6偶数→-1")
    
    # 9: n=6但可能有中位数？不会，因为元素都不同，偶数个不可能
    make_case([10, 20, 30, 40, 50, 60], "n=6偶数递增→-1")
    
    # 10: n=7, 中间元素检查
    make_case([7, 1, 6, 2, 5, 3, 4], "n=7完全对称")
    
    # 11: n=9, 中间是正中间
    make_case([9, 8, 7, 6, 5, 4, 3, 2, 1], "n=9递减, 中间为5")
    
    # 12: n=10偶数, 不可能有中位数
    make_case([10, 9, 8, 7, 6, 5, 4, 3, 2, 1], "n=10递减→-1")
    
    # 13: n=50最大值, 有中位数
    arr = list(range(1, 51))  # 1..50, n=50偶数 → 无中位数
    make_case(arr, "n=50全排列→-1")
    
    # 14: n=49, 有中位数
    arr = list(range(1, 50))  # 1..49, n=49奇数
    make_case(arr, "n=49全排列")
    
    # 15: n=11打乱
    arr = [11, 7, 3, 9, 1, 5, 10, 2, 8, 4, 6]
    make_case(arr, "n=11打乱")
    
    # 16: n=50最大值, 打乱有中位数
    arr = list(range(1, 51))
    random.seed(999)
    random.shuffle(arr)
    make_case(arr, "n=50打乱→-1")
    
    # 17-20: 各种刁钻情况
    make_case([100, 1], "n=2极端值→-1")
    make_case([100, 50, 1], "n=3极端值")
    arr = list(range(1, 48)) + [99, 100]  # n=49
    make_case(arr, "n=49含大值")
    make_case([50, 49, 48, 47, 46, 45], "n=6递减→-1")


# ==================== 乐乐玩木棒 ====================

def generate_乐乐玩木棒():
    """
    木棒拼数字，求能拼出的最大数（不含前导0）
    贪心策略：先确定最大长度，再从左到右填最大可能数字
    """
    name = "乐乐玩木棒"
    print(f"\n▶ {name}")
    cid = 0

    def make_case(costs, n_sticks, desc):
        nonlocal cid
        cid += 1
        inp = " ".join(map(str, costs)) + f"\n{n_sticks}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → len={len(out)}")

    # 1: 样例1
    make_case([6, 7, 8, 22, 22, 22, 22, 22, 22, 22], 21, "样例1→210")
    
    # 2: 样例2（1只需要1根）
    make_case([1, 7, 8, 22, 22, 22, 22, 22, 22, 22], 21, "样例2→100000000000000")
    
    # 3: 0最便宜且首位不能为0，所以用最便宜的1位数字
    make_case([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 10, "0最便宜,首位禁0")
    
    # 4: 只有1根木棍 → 只能用1（0不能做首位）
    make_case([10, 1, 10, 10, 10, 10, 10, 10, 10, 10], 1, "仅1根→只能拼1")
    
    # 5: 很多木棍，9最便宜
    make_case([10, 10, 10, 10, 10, 10, 10, 10, 10, 1], 100, "9最便宜, 全9")
    
    # 6: 0和1都很便宜
    make_case([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 100, "0和1便宜→长串1")
    
    # 7: 所有数字等成本
    make_case([5, 5, 5, 5, 5, 5, 5, 5, 5, 5], 50, "等成本, 尽量大数字")
    
    # 8: 只有偶数数字可用（奇数成本超高）
    make_case([100, 100, 2, 100, 2, 100, 2, 100, 2, 100], 100, "偶数便宜→全是偶数")
    
    # 9: 恰好拼一个数字
    make_case([5, 5, 10, 10, 10, 10, 10, 10, 10, 10], 5, "恰好1根→拼1")
    
    # 10: 与样例不同，数字8成本更低
    make_case([6, 7, 3, 22, 22, 22, 22, 22, 22, 22], 30, "8成本3根")
    
    # 11: 1很贵，但0便宜，最终需要以1-9开头
    make_case([2, 100, 100, 100, 100, 100, 100, 100, 100, 100], 100, "0便宜但1极贵")
    
    # 12: 最大n=10000
    make_case([6, 2, 5, 5, 4, 5, 6, 3, 7, 6], 10000, "n=10000大规模")
    
    # 13: 只有9和1可用（其他成本极高）
    make_case([1000, 1, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1], 5000, "1和9便宜")
    
    # 14: 所有数字成本随机
    random.seed(42)
    costs = [random.randint(1, 100) for _ in range(10)]
    make_case(costs, 5000, "随机成本 n=5000")
    
    # 15: 随机成本 大n
    random.seed(123)
    costs = [random.randint(1, 50) for _ in range(10)]
    make_case(costs, 10000, "随机成本 n=10000")
    
    # 16-20: 更多刁钻
    # 极端：首位只能用9（1、0都很贵，9相对便宜）
    make_case([100, 100, 100, 100, 100, 100, 100, 100, 5, 100], 100, "只有9便宜")
    
    # 大部分数字需要等量木棍
    make_case([3, 3, 3, 3, 3, 3, 3, 3, 3, 3], 10000, "全等成本大n")
    
    # 0超级便宜但禁首位
    make_case([1, 100, 100, 100, 100, 100, 100, 100, 100, 100], 2000, "0极便宜禁首位")
    
    # 最小成本2，余数刁钻
    make_case([2, 2, 2, 2, 2, 2, 2, 2, 2, 2], 9999, "全成本2,n=9999")
    
    # 成本递增
    make_case([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 7777, "递增成本")


# ==================== 书签制作 ====================

def generate_书签制作():
    """有序贝尔数（Fubini数）：f(n) = sum C(n,k) * f(n-k)"""
    name = "书签制作"
    print(f"\n▶ {name}")
    cid = 0

    def make_case(n, desc):
        nonlocal cid
        cid += 1
        inp = str(n)
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: n=1
    make_case(1, "n=1最小值")
    # 2: n=2
    make_case(2, "n=2")
    # 3: 样例 n=3
    make_case(3, "样例1: n=3→13")
    # 4: n=4
    make_case(4, "n=4")
    # 5: n=5
    make_case(5, "n=5")
    # 6: n=6
    make_case(6, "n=6")
    # 7: n=7
    make_case(7, "n=7")
    # 8: n=8
    make_case(8, "n=8")
    # 9: n=9
    make_case(9, "n=9")
    # 10: n=10
    make_case(10, "n=10")
    # 11: n=11
    make_case(11, "n=11")
    # 12: n=12
    make_case(12, "n=12")
    # 13: n=13
    make_case(13, "n=13")
    # 14: n=14
    make_case(14, "n=14")
    # 15: n=15
    make_case(15, "n=15")
    # 16: n=16
    make_case(16, "n=16")
    # 17: 样例 n=17
    make_case(17, "样例2: n=17→130370767029135901")
    # 18: n=17 again for completeness
    make_case(17, "n=17最大值")
    # 19: n=11 (重复)
    make_case(11, "n=11确认")
    # 20: n=16 (重复)
    make_case(16, "n=16近最大值")


# ==================== 城镇地图 ====================

def generate_城镇地图():
    """5x5地图绘制，根据方向显示不同字符"""
    name = "城镇地图"
    print(f"\n▶ {name}")
    cid = 0

    def make_case(n, m, X, Y, queries, desc):
        nonlocal cid
        cid += 1
        lines = [f"{n} {m} {X} {Y}", str(len(queries))]
        for x, y in queries:
            lines.append(f"{x} {y}")
        inp = "\n".join(lines)
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc}")

    # 1: 样例
    make_case(6, 15, 4, 8, [(1, 1), (2, 7)], "样例1")

    # 2: 中心刚好在正中间
    make_case(11, 11, 6, 6, [(6, 6), (1, 1), (11, 11)], "中心正中间+角落")

    # 3: 中心在左上角边界
    make_case(5, 5, 1, 1, [(1, 1), (3, 3)], "中心在左上角")

    # 4: 中心在右下角边界
    make_case(5, 5, 5, 5, [(5, 5), (1, 1)], "中心在右下角")

    # 5: 中心在右上角
    make_case(5, 5, 1, 5, [(1, 5), (3, 3)], "中心在右上角")

    # 6: 中心在左下角
    make_case(5, 5, 5, 1, [(5, 1), (3, 3)], "中心在左下角")

    # 7: 请求点在边界外附近（显示#）
    make_case(10, 10, 5, 5, [(1, 1), (10, 10)], "边界外附近")

    # 8: 大量请求
    make_case(20, 20, 10, 10, 
              [(1, 1), (5, 5), (10, 10), (15, 15), (20, 20), 
               (3, 7), (7, 3), (12, 18), (18, 12), (1, 20)],
              "10个请求多点")

    # 9: 中心不在中央，不对称
    make_case(7, 15, 3, 10, [(3, 10), (1, 1), (7, 15)], "中心偏左上")

    # 10: 小地图
    make_case(3, 3, 2, 2, [(1, 1), (2, 2), (3, 3)], "最小3x3地图")

    # 11: 宽地图
    make_case(5, 20, 3, 10, [(1, 1), (3, 10), (5, 20)], "宽地图")

    # 12: 高地图
    make_case(20, 5, 10, 3, [(1, 1), (10, 3), (20, 5)], "高地图")

    # 13: 中心偏离，请求在8个方向区域
    make_case(10, 10, 5, 5,
              [(2, 2), (2, 5), (2, 8), (5, 2), (5, 8), (8, 2), (8, 5), (8, 8)],
              "8方向区域各一")

    # 14: 超大n,m
    make_case(1000, 1000, 500, 500,
              [(500, 500), (1, 1), (1000, 1000), (250, 750)],
              "超大1000x1000地图")

    # 15: 多个请求在边界
    make_case(6, 10, 3, 5,
              [(1, 1), (1, 5), (1, 10), (6, 1), (6, 5), (6, 10)],
              "四角边界请求")

    # 16: 中心在(1,1)的超小地图
    make_case(3, 3, 1, 1, [(1, 1), (2, 2), (3, 3)], "中心1,1的3x3")

    # 17: 中心在边缘
    make_case(10, 10, 1, 5, [(1, 5), (5, 5), (10, 5)], "中心在上边缘")

    # 18: 中心在边缘
    make_case(10, 10, 5, 1, [(5, 1), (5, 5), (5, 10)], "中心在左边缘")

    # 19: 15x15 中心偏离
    make_case(15, 15, 4, 12,
              [(1, 1), (7, 7), (15, 15), (4, 12), (2, 14)],
              "中心偏右上")

    # 20: Q=1000最大值部分
    make_case(100, 100, 50, 50,
              [(i * 10 % 100 + 1, i * 7 % 100 + 1) for i in range(20)],
              "20个随机请求")


# ==================== 趣味进制 ====================

def generate_趣味进制():
    """
    二进制格式为 1...10...0 的数（至少一个1和一个0）
    在[1, n]中计数
    """
    name = "趣味进制"
    print(f"\n▶ {name}")
    cid = 0

    def make_case(n, desc):
        nonlocal cid
        cid += 1
        inp = str(n)
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: 样例 n=12
    make_case(12, "样例1: n=12→5")
    
    # 2: 样例 n=16384
    make_case(16384, "样例2: n=16384→92")
    
    # 3: n=1 → 没有（至少1个1和1个0）
    make_case(1, "n=1最小值→0")
    
    # 4: n=2 → 只有2(10)
    make_case(2, "n=2→1")
    
    # 5: n=3 → 2(10) 
    make_case(3, "n=3→1")
    
    # 6: n=4 → 2(10),4(100)
    make_case(4, "n=4→2")
    
    # 7: n=7 → 2,4,6 → 3个
    make_case(7, "n=7→3")
    
    # 8: n=100
    make_case(100, "n=100")
    
    # 9: n=1000
    make_case(1000, "n=1000")
    
    # 10: n=100000 (60%数据边界)
    make_case(100000, "n=100000")
    
    # 11: n=999999
    make_case(999999, "n=999999")
    
    # 12: n=1000000000 (100%数据最大边界)
    make_case(1000000000, "n=10亿最大边界")
    
    # 13: n=2^30-1 (约10.7亿)
    make_case((1 << 30) - 1, "n=2^30-1")
    
    # 14: n=500000000
    make_case(500000000, "n=5亿")
    
    # 15: n=2^k * (2^m - 1) 附近（趣味数本身）
    make_case(12, "n=12(本身就是趣味数)")
    
    # 16: n=65535 (2^16-1，全是1)
    make_case(65535, "n=65535")
    
    # 17: n=65536 (2^16)
    make_case(65536, "n=65536")
    
    # 18: n=131071 (2^17-1)
    make_case(131071, "n=131071")
    
    # 19: n=131072 (2^17)
    make_case(131072, "n=131072")
    
    # 20: n=1048575 (2^20-1)
    make_case(1048575, "n=2^20-1")


# ==================== 主函数 ====================

def main():
    print("=" * 60)
    print("2024南京市信息与未来 - 测试数据生成")
    print(f"共 {len(PROBLEMS)} 题，每题20个测试点")
    print("=" * 60)

    # 清理
    if os.path.exists(OUTPUT_DIR):
        shutil.rmtree(OUTPUT_DIR)
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # 编译
    print("\n>>> 编译C++代码...")
    failed = []
    for name in PROBLEMS:
        if not compile_cpp(name):
            failed.append(name)
    if failed:
        print(f"编译失败: {failed}")
        return

    # 生成
    print("\n>>> 生成测试数据 (每题20组)...")
    random.seed(2024)
    generate_左邻右舍()
    generate_中位数()
    generate_乐乐玩木棒()
    generate_书签制作()
    generate_城镇地图()
    generate_趣味进制()

    # 打包
    print("\n>>> 打包ZIP...")
    for name in PROBLEMS:
        zip_problem(name)

    # 统计
    print(f"\n{'=' * 60}")
    print(f"完成！输出目录: {OUTPUT_DIR}")
    for name in PROBLEMS:
        dir_path = os.path.join(OUTPUT_DIR, name)
        files = [f for f in os.listdir(dir_path) if f.endswith('.in')]
        print(f"  {name}: {len(files)} 组测试数据")
    print(f"{'=' * 60}")


if __name__ == "__main__":
    main()
