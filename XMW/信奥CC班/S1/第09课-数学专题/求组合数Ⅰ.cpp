/*
 *  @date: 2026-04-02 16:38:06  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 求组合数Ⅰ.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 2005
#define ll long long
#define mod 1000000007

using namespace std;

int t, n, m;
int dp[N][N];

void solve()
{
    for (int i = 0; i < N; i++)
    {
        dp[i][0] = dp[i][i] = 1;
        for (int j = 1; j < i; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
    }
}
int main()
{
    scanf("%d", &t);
    solve();
    while (t--)
    {
        scanf("%d%d", &n, &m);
        printf("%d\n", dp[n][m]);
    }
    return 0;
}