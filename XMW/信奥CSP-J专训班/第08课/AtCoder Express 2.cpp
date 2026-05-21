/*
 *  @date: 2026-04-26 09:44:58  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: AtCoder Express 2.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 505
#define ll long long

using namespace std;

int n, m, q, l, r, dp[N][N];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        dp[l][r] += 1;
    }
    for (int i = n; i >= 1; i--)
        for (int j = i; j <= n; j++)
            dp[i][j] += dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
    while (q--)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", dp[l][r]);
    }
    return 0;
}