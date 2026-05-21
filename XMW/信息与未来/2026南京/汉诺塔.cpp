/*
 *  @date: 2026-05-14 18:00:04  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

string s;
int n;

void hannuota(int k, char a, char b, char c)
{
    if (k == 0)
        return;
    hannuota(k - 1, a, c, b);   // 将前k-1个圆盘从a柱子移到b柱子上
    printf("%c -> %c\n", a, c); // 将第k个圆盘从a柱子移到c柱子上
    hannuota(k - 1, b, a, c);   // 将前k-1个圆盘从b柱子移到c柱子上
}

void solve(int k, char target) // 将前k个圆盘移到target柱子上
{
    if (k == 0)
        return;
    char tmp = s[k - 1]; // 第k个圆盘所在柱子
    if (tmp == target)
        solve(k - 1, target); // 如果第k个圆盘已经在目标柱子上，继续处理前k-1个圆盘
    else
    {
        char other = 'A' + 'B' + 'C' - tmp - target; // 辅助柱
        solve(k - 1, other);                         // 先将前k-1个圆盘移到other柱子上
        printf("%c -> %c\n", tmp, target);           // 将第k个圆盘从tmp柱子移到target柱子上
        hannuota(k - 1, other, tmp, target);         // 将前k-1个圆盘从other柱子移到target柱子上
    }
}

int main()
{
    cin >> n >> s;
    solve(n, 'C');
    return 0;
}