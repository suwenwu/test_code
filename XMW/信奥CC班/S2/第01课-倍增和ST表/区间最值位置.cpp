/*
 *  @date: 2026-04-17 18:05:57  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 区间最值位置.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m;
struct node
{
    int value;
    int idx;
} st[N][20]; // 保存区间最大值和最大值位置

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &st[i][0].value);
        st[i][0].idx = i - 1;
    }
    for (int j = 1; j <= 19; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            if (st[i][j - 1].value > st[i + (1 << (j - 1))][j - 1].value)
                st[i][j] = st[i][j - 1];
            else
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
        }
    }
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l += 1, r += 1;
        int k = log2(r - l + 1);
        if (st[l][k].value > st[r - (1 << k) + 1][k].value)
            printf("%d %d\n", st[l][k].value, st[l][k].idx);
        else
            printf("%d %d\n", st[r - (1 << k) + 1][k].value, st[r - (1 << k) + 1][k].idx);
    }
    return 0;
}