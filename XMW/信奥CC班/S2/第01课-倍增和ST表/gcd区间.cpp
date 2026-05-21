/*
 *  @date: 2026-04-17 19:17:06  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: gcd区间.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1005
#define ll long long

using namespace std;

int n, m, l, r, st[N][12];

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &st[i][0]);
    int k = log2(n);
    for (int j = 1; j <= k; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    while (m--)
    {
        scanf("%d%d", &l, &r);
        int k = log2(r - l + 1);
        printf("%d\n", gcd(st[l][k], st[r - (1 << k) + 1][k]));
    }
    return 0;
}