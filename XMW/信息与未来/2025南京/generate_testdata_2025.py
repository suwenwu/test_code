#!/usr/bin/env python3
"""
2025南京市信息与未来 - 测试数据生成脚本
为6道题各生成20个刁钻测试点，打包为zip（解压后直接是in/out文件）
"""

import os
import random
import subprocess
import zipfile
import shutil
import string

BASE_DIR = "/Users/s/Documents/workspace/vscode/XMW/信息与未来/2025南京"
OUTPUT_DIR = "/Users/s/Documents/workspace/vscode/XMW/测试数据_2025"

# 注意：文件名中有特殊Unicode字符（异体/兼容汉字）
# "⻦" = U+2EE6 (CJK RADICAL BIRD) 而非 "鸟" U+9E1F
# "⽣" = U+2F63 (CJK RADICAL LIFE) 而非 "生" U+751F
PROBLEMS = [
    "九头\u2ee6和九尾\u2ee6",  # 九头⻦和九尾⻦
    "后缀排序",
    "农场道路",
    "身份证校验",
    "蚂蚁游戏",
    "迷宫\u2f63成",  # 迷宫⽣成
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
        capture_output=True, text=True, timeout=30
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


# ==================== 九头鸟和九尾鸟 ====================

def generate_九头鸟和九尾鸟(name):
    """
    九头鸟(9头1尾), 九尾鸟(1头9尾)
    已知头总数h, 尾总数t, 求九头鸟数量x
    公式: 9x + y = h, x + 9y = t → x = (9h - t) / 80
    """
    print(f"\n▶ {name}")
    cid = 0

    def make_case(h, t, desc):
        nonlocal cid
        cid += 1
        inp = f"{h} {t}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: 样例1
    make_case(29, 21, "样例1: 29头21尾→3")

    # 2: 样例2
    make_case(381, 469, "样例2: 381头469尾→37")

    # 3: 最小: 1只九头鸟, 0只九尾鸟
    make_case(9, 1, "1只九头鸟: 9头1尾→1")

    # 4: 0只九头鸟, 1只九尾鸟
    make_case(1, 9, "1只九尾鸟: 1头9尾→0")

    # 5: 1只各
    make_case(10, 10, "各1只: 10头10尾→1")

    # 6: 最大量: 接近10^6
    make_case(999999, 111111, "大量, h=999999")

    # 7: 九头鸟多
    make_case(900000, 100000, "九头鸟多: 9万头")

    # 8: 九尾鸟多
    make_case(100000, 900000, "九尾鸟多: 9万尾")

    # 9: 各500只
    h = 9*500 + 500
    t = 500 + 9*500
    make_case(h, t, "各500只")

    # 10: 各1000只
    h = 9*1000 + 1000
    t = 1000 + 9*1000
    make_case(h, t, "各1000只")

    # 11: 九头鸟多, 九尾鸟少
    make_case(9*100 + 1, 100 + 9*1, "100只九头鸟+1只九尾鸟")

    # 12: 只有九头鸟 (0只九尾鸟)
    make_case(9*50, 50, "50只九头鸟: 450头50尾→50")

    # 13: 只有九尾鸟
    make_case(50, 9*50, "50只九尾鸟→0")

    # 14: (h+t)不能被10整除的边界
    make_case(91, 19, "h+t=110可整除")

    # 15: 复杂值
    make_case(9*77 + 23, 77 + 9*23, "77只九头鸟+23只九尾鸟")

    # 16: 大数随机
    random.seed(2025)
    for _ in range(5):
        x = random.randint(1, 10000)
        y = random.randint(1, 10000)
        h = 9*x + y
        t = x + 9*y
        cid += 1
        inp = f"{h} {t}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
    print(f"  [{cid-4}-{cid}] 随机大数")


# ==================== 后缀排序 ====================

def generate_后缀排序(name):
    """字符串后缀按字典序排序，输出起始位置"""
    print(f"\n▶ {name}")
    cid = 0

    def make_case(s, desc):
        nonlocal cid
        cid += 1
        inp = s
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out[:40]}...")

    # 1: 样例1
    make_case("BANANA", "样例1: BANANA")

    # 2: 样例2
    make_case("XINXIYUWEILAI", "样例2: XINXIYUWEILAI")

    # 3: 单字符
    make_case("A", "单字符A")

    # 4: 双字符有序
    make_case("AB", "双字符AB")

    # 5: 双字符逆序
    make_case("BA", "双字符BA")

    # 6: 全相同字符
    make_case("AAAAAA", "全相同A")

    # 7: 全相同长串
    make_case("Z" * 20, "全相同Z×20")

    # 8: 递增序列
    make_case("ABCDEFGHIJ", "递增ABCDEFGHIJ")

    # 9: 递减序列
    make_case("FEDCBA", "递减FEDCBA")

    # 10: 回文
    make_case("ABCBA", "回文ABCBA")

    # 11: 重复模式
    make_case("ABABABABAB", "重复AB×5")

    # 12: 较长随机
    random.seed(2025)
    s = ''.join(random.choices(string.ascii_uppercase, k=50))
    make_case(s, "随机50字符")

    # 13: 较长随机
    s = ''.join(random.choices(string.ascii_uppercase, k=100))
    make_case(s, "随机100字符")

    # 14: 较长随机
    s = ''.join(random.choices(string.ascii_uppercase, k=200))
    make_case(s, "随机200字符")

    # 15: 接近最大
    s = ''.join(random.choices(string.ascii_uppercase, k=500))
    make_case(s, "随机500字符")

    # 16: 最大n=1000
    s = ''.join(random.choices(string.ascii_uppercase, k=1000))
    make_case(s, "最大n=1000")

    # 17: 只有A和B交替
    s = "AB" * 250  # 500 chars
    make_case(s, "AB交替×250")

    # 18: Z开头长串
    s = "Z" + "A" * 99
    make_case(s, "Z开头后跟99个A")

    # 19: A开头长串
    s = "A" * 50 + "Z" * 50
    make_case(s, "50个A后跟50个Z")

    # 20: 字母表顺序
    make_case(string.ascii_uppercase, "26字母表")


# ==================== 农场道路 ====================

def generate_农场道路(name):
    """
    n只奶牛，可分裂条件: n>k 且 (n+k)%2==0
    分裂为 (n+k)/2 和 (n-k)/2，BFS模拟直到不能再分裂
    """
    print(f"\n▶ {name}")
    cid = 0

    def make_case(n, k, desc):
        nonlocal cid
        cid += 1
        inp = f"{n} {k}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: 样例1
    make_case(6, 2, "样例1: n=6,k=2→3")

    # 2: 样例2
    make_case(41, 3, "样例2: n=41,k=3→6")

    # 3: n<=k, 不能分裂
    make_case(5, 5, "n=k=5→1群")

    # 4: n<k, 不能分裂
    make_case(3, 10, "n=3<k=10→1群")

    # 5: n=1最小值
    make_case(1, 1, "n=1,k=1→1")

    # 6: n=2, k=1, (2+1)%2≠0
    make_case(2, 1, "n=2,k=1不能分→1")

    # 7: n=3, k=1, (3+1)%2=0→2和1
    make_case(3, 1, "n=3,k=1→2群")

    # 8: n=7, k=1 → (7+1)/2=4, (7-1)/2=3, 4→2和2, 3→2和1
    make_case(7, 1, "n=7,k=1")

    # 9: n=15, k=1
    make_case(15, 1, "n=15,k=1")

    # 10: n=100, k=1 (全奇分裂)
    make_case(100, 1, "n=100,k=1")

    # 11: k=2
    make_case(100, 2, "n=100,k=2")

    # 12: k=1000最大
    make_case(1000000000, 1000, "n=10亿,k=1000最大")

    # 13: 大n, k=1
    make_case(999999937, 1, "大n=999999937,k=1")

    # 14: 大n, k=7
    make_case(1000000000, 7, "n=10亿,k=7")

    # 15: 2的幂减1, k=1
    make_case(1023, 1, "n=1023,k=1(2^10-1)")

    # 16: 2的幂, k=1
    make_case(1024, 1, "n=1024,k=1(2^10)")

    # 17: n=999999999, k=2
    make_case(999999999, 2, "n=999999999,k=2")

    # 18: n=10, k=3
    make_case(10, 3, "n=10,k=3")

    # 19: n=63, k=1 (2^6-1)
    make_case(63, 1, "n=63,k=1(2^6-1)")

    # 20: n=100, k=99
    make_case(100, 99, "n=100,k=99大k")


# ==================== 身份证校验 ====================

def generate_身份证校验(name):
    """校验18位身份证号：校验位+日期合法性"""
    print(f"\n▶ {name}")
    cid = 0

    def make_case(ids, desc):
        nonlocal cid
        cid += 1
        inp = f"{len(ids)}\n" + "\n".join(ids)
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        out_lines = out.split('\n')
        print(f"  [{cid:02d}] {desc} → {' '.join(out_lines[:3])}...")

    # 根据校验算法生成合法身份证号
    # C++代码: for i=18..1: sum += a[i]*p; p*=2; p%=11; 最终要求 sum%11==1
    # 即 a[18]*1 + a[17]*2 + a[16]*4 + ... + a[1]*2^17 ≡ 1 (mod 11)
    def make_valid_id(year, month, day, addr="110101"):
        """生成一个合法的身份证号"""
        # 顺序码（3位，随机奇数表示男）
        seq = f"{random.randint(1, 999):03d}"
        body = addr + f"{year:04d}{month:02d}{day:02d}" + seq
        
        # 计算校验位: 先算 body 位（位置1~17）的加权和
        # 位置17(body[16])乘2^1, 位置16(body[15])乘2^2, ..., 位置1(body[0])乘2^17
        a = [int(c) for c in body]
        total = 0
        p = 2  # 从2^1开始（位置17的乘数）
        for i in range(16, -1, -1):  # i=16..0 对应位置17..1
            total = (total + a[i] * p) % 11
            p = (p * 2) % 11
        
        # 需要: check_digit + total ≡ 1 (mod 11)
        check_digit = (1 - total) % 11
        
        if check_digit == 10:
            return body + "X"
        else:
            return body + str(check_digit)

    def make_invalid_checksum(year, month, day, addr="110101"):
        """生成校验位错误的身份证"""
        valid = make_valid_id(year, month, day, addr)
        # 改最后一位
        last = valid[-1]
        if last == 'X':
            return valid[:-1] + '0'
        elif last == '0':
            return valid[:-1] + '1'
        elif last == '9':
            return valid[:-1] + '8'
        # 简单加1
        new_last = str((int(last) + 1) % 10)
        return valid[:-1] + new_last

    # 1: 样例
    make_case(["14021320141203937X", "140213201412039372"], "样例: PASS+FAIL")

    # 2: 合法日期1900-01-01
    make_case([make_valid_id(1900, 1, 1)], "合法:1900-01-01")

    # 3: 合法日期2025-05-10（上界）
    make_case([make_valid_id(2025, 5, 10)], "合法:2025-05-10上界")

    # 4: 合法日期2000-02-29（闰年）
    make_case([make_valid_id(2000, 2, 29)], "合法:2000-02-29闰年")

    # 5: 非法日期: 2025-05-11（超上界1天）
    make_case([make_invalid_checksum(2025, 5, 11)], "非法:日期超上界→FAIL")
    # 改为手动构造日期合法但超范围的
    body = "110101" + "20250511" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    id1 = body + ("X" if cd == 10 else str(cd))
    make_case([id1], "非法:2025-05-11超范围(校验位正确)")

    # 6: 非法日期: 1900年之前
    body = "110101" + "18991231" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    id2 = body + ("X" if cd == 10 else str(cd))
    make_case([id2], "非法:1899-12-31(校验位正确)")

    # 7: 非法: 2月30日
    body = "110101" + "20200230" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    id3 = body + ("X" if cd == 10 else str(cd))
    make_case([id3], "非法:2020-02-30不存在")

    # 8: 非法: 非闰年2月29日
    body = "110101" + "20230229" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    id4 = body + ("X" if cd == 10 else str(cd))
    make_case([id4], "非法:2023-02-29非闰年")

    # 9: 校验位错误+X混合
    make_case([make_valid_id(2000, 6, 15), make_invalid_checksum(2000, 6, 15)],
              "合法+同号校验位错误")

    # 10: 大量混合测试
    ids = []
    valid_dates = [
        (1990, 3, 15), (2001, 7, 8), (1985, 12, 1),
        (2010, 4, 30), (1976, 8, 22), (2004, 1, 1),
        (2025, 1, 1), (2025, 5, 10), (1900, 6, 15),
        (2008, 8, 8), (1999, 9, 9), (1964, 10, 1),
        (2000, 11, 11), (2020, 12, 12), (1988, 3, 3),
    ]
    for y, m, d in valid_dates:
        ids.append(make_valid_id(y, m, d))
    make_case(ids, f"{len(ids)}个合法ID")

    # 11: 全是校验位错误的
    bad_ids = []
    for y, m, d in valid_dates[:10]:
        bad_ids.append(make_invalid_checksum(y, m, d))
    make_case(bad_ids, "10个校验位错误ID")

    # 12: 边界混合
    make_case([
        make_valid_id(1900, 1, 1),
        make_valid_id(2025, 5, 10),
        make_invalid_checksum(2000, 1, 1),
        make_invalid_checksum(2025, 5, 10),
    ], "边界混合:上下界+错误")

    # 13: 含X校验位的合法身份证
    # 构造一个校验位为10的
    for attempt in range(1000):
        addr = "110101"
        seq = f"{random.randint(1, 999):03d}"
        body = addr + f"{random.randint(1990, 2020):04d}{random.randint(1, 12):02d}{random.randint(1, 28):02d}" + seq
        a = [int(c) for c in body]
        total = 0; p = 2
        for i in range(16, -1, -1):
            total = (total + a[i] * p) % 11
            p = (p * 2) % 11
        cd = (1 - total) % 11
        if cd == 10:
            make_case([body + "X"], "校验位为X的合法ID")
            break
    else:
        make_case([make_valid_id(2001, 1, 1)], "未能构造X→用普通ID代替")

    # 14: 多个ID测试
    ids14 = []
    for i in range(20):
        y = random.randint(1900, 2025)
        m = random.randint(1, 12)
        d = random.randint(1, 28)
        ids14.append(make_valid_id(y, m, d))
    make_case(ids14, "20个随机合法ID")

    # 15: 混合20个
    ids15 = []
    for i in range(10):
        y = random.randint(1900, 2025)
        m = random.randint(1, 12)
        d = random.randint(1, 28)
        ids15.append(make_valid_id(y, m, d))
    for i in range(10):
        y = random.randint(1900, 2025)
        m = random.randint(1, 12)
        d = random.randint(1, 28)
        ids15.append(make_invalid_checksum(y, m, d))
    random.shuffle(ids15)
    make_case(ids15, "10合法+10非法混合")

    # 16-20: 更多
    # 非法: 月份13
    body = "110101" + "20251301" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    make_case([body + ("X" if cd == 10 else str(cd))], "非法月份13")

    # 非法: 日期0
    body = "110101" + "20250100" + "001"
    a = [int(c) for c in body]
    total = 0; p = 2
    for i in range(16, -1, -1):
        total = (total + a[i] * p) % 11
        p = (p * 2) % 11
    cd = (1 - total) % 11
    make_case([body + ("X" if cd == 10 else str(cd))], "非法日期00")

    # 小规模批量
    ids18 = [make_valid_id(2000, 1, 1) for _ in range(5)]
    make_case(ids18, "5个相同合法ID")

    # 40个随机混合（凑满20组）
    ids19 = []
    for i in range(40):
        y = random.randint(1900, 2025)
        m = random.randint(1, 12)
        d = random.randint(1, 28)
        if random.random() < 0.5:
            ids19.append(make_valid_id(y, m, d))
        else:
            ids19.append(make_invalid_checksum(y, m, d))
    make_case(ids19, "40个随机混合ID")


# ==================== 蚂蚁游戏 ====================

def generate_蚂蚁游戏(name):
    """
    蚂蚁在杆上，相遇掉头。求所有蚂蚁掉下去的最短和最长时间。
    等价于：蚂蚁穿过对方，min_time = max(min(x, L-x)), max_time = max(max(x, L-x))
    """
    print(f"\n▶ {name}")
    cid = 0

    def make_case(L, positions, desc):
        nonlocal cid
        cid += 1
        inp = f"{L} {len(positions)}\n" + " ".join(map(str, positions))
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] {desc} → {out}")

    # 1: 样例
    make_case(27, [7, 11, 3, 17, 23], "样例: 27,5只→11 24")

    # 2: 单只蚂蚁
    make_case(100, [50], "单只在中间")

    # 3: 单只在端点
    make_case(100, [0], "单只在左端点")

    # 4: 单只在右端点
    make_case(100, [100], "单只在右端点")

    # 5: 两只分别靠近两端
    make_case(100, [1, 99], "两只各靠近端点")

    # 6: 两只都在中间
    make_case(100, [48, 52], "两只在中间附近")

    # 7: 大量蚂蚁聚集一端
    make_case(1000, [1] * 50, "50只全在左端")

    # 8: 均匀分布
    make_case(1000, list(range(0, 1001, 100)), "均匀分布11只")

    # 9: 大L=10^9
    make_case(1000000000, [1, 999999999], "L=10亿,两端各一只")

    # 10: 大L中间
    make_case(1000000000, [500000000], "L=10亿,中间一只")

    # 11: 最大n=10000, 全部在左端
    make_case(1000000000, [1] * 10000, "n=10000全左端")

    # 12: 最大n, 全在右端
    make_case(1000000000, [999999999] * 10000, "n=10000全右端")

    # 13: n=10000分散
    random.seed(2025)
    pos = sorted(random.sample(range(1, 1000000000), 10000))
    make_case(1000000000, pos, "n=10000随机分散")

    # 14: 中等规模
    pos = sorted(random.sample(range(1, 1000000), 500))
    make_case(1000000, pos, "n=500随机")

    # 15: 靠近中间
    make_case(1000, [499, 500, 501], "3只在中间附近")

    # 16: 单只蚂蚁在0
    make_case(10, [0], "单只x=0")

    # 17: 两只在相同位置? 题目没有说是否可能在相同位置. 加一个防范
    make_case(100, [50, 50], "两只同位置")

    # 18-20: 更多随机
    for L, n in [(500, 50), (5000, 200), (100000, 1000)]:
        cid += 1
        pos = sorted(random.sample(range(1, L), n))
        inp = f"{L} {n}\n" + " ".join(map(str, pos))
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        print(f"  [{cid:02d}] L={L}, n={n} → {out}")


# ==================== 迷宫生成 ====================

def generate_迷宫生成(name):
    """
    生成n×m迷宫，左上到右下最短路径恰好为k步
    DFS回溯法：从(1,1)出发走k步到达(n,m)，路径上为'.'，其余为'#'
    """
    print(f"\n▶ {name}")
    cid = 0

    def make_case(n, m, k, desc):
        nonlocal cid
        cid += 1
        inp = f"{n} {m} {k}"
        out = run_cpp(name, inp)
        write_test_case(name, cid, inp, out)
        # 验证是否有输出
        if out:
            lines = out.split('\n')
            print(f"  [{cid:02d}] {desc} → {len(lines)}行迷宫")
        else:
            print(f"  [{cid:02d}] {desc} → 无输出(无解)")

    # 1: 样例1
    make_case(4, 4, 6, "样例1: 4×4 k=6")

    # 2: 样例2
    make_case(3, 5, 10, "样例2: 3×5 k=10")

    # 3: 最小迷宫：1×1
    make_case(1, 1, 0, "1×1 k=0")

    # 4: 2×2 最短路径
    make_case(2, 2, 2, "2×2 k=2(最短)")

    # 5: 2×2 最长路径
    make_case(2, 2, 3, "2×2 k=3(最长)")

    # 6: 2×3
    make_case(2, 3, 3, "2×3 k=3")

    # 7: 3×3 各种k
    make_case(3, 3, 4, "3×3 k=4")

    # 8: 3×3 k=6
    make_case(3, 3, 6, "3×3 k=6")

    # 9: 3×3 k=8
    make_case(3, 3, 8, "3×3 k=8(最长)")

    # 10: 4×4 k=5
    make_case(4, 4, 5, "4×4 k=5")

    # 11: 4×4 k=8
    make_case(4, 4, 8, "4×4 k=8")

    # 12: 4×4 k=11
    make_case(4, 4, 11, "4×4 k=11")

    # 13: 5×5 k=8 (最短n+m-2=8)
    make_case(5, 5, 8, "5×5 k=8(最短)")

    # 14: 5×5 k=12
    make_case(5, 5, 12, "5×5 k=12")

    # 15: 5×5 k=16
    make_case(5, 5, 16, "5×5 k=16")

    # 16: 3×4 k=5
    make_case(3, 4, 5, "3×4 k=5")

    # 17: 6×6 k=10
    make_case(6, 6, 10, "6×6 k=10")

    # 18: 6×6 k=15
    make_case(6, 6, 15, "6×6 k=15")

    # 19: 8×8 k=14
    make_case(8, 8, 14, "8×8 k=14")

    # 20: 8×8 k=20
    make_case(8, 8, 20, "8×8 k=20")


# ==================== 主函数 ====================

def main():
    print("=" * 60)
    print("2025南京市信息与未来 - 测试数据生成")
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
    random.seed(2025)
    generate_九头鸟和九尾鸟(PROBLEMS[0])
    generate_后缀排序(PROBLEMS[1])
    generate_农场道路(PROBLEMS[2])
    generate_身份证校验(PROBLEMS[3])
    generate_蚂蚁游戏(PROBLEMS[4])
    generate_迷宫生成(PROBLEMS[5])

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
