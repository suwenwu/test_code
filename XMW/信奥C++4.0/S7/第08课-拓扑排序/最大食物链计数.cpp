/*
 *  @date: 2026-05-03 19:31:29  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最大食物链计数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 2005
#define ll long long
#define MOD 80112002

using namespace std;

int n, m, dp[N], deg[N];
vector<int> ve[N];
bool vis[N];

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 0)
        {
            dp[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < ve[u].size(); i++)
        {
            int v = ve[u][i];
            dp[v] += dp[u];
            dp[v] %= MOD;
            if (--deg[v] == 0)
                q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            ans = (ans + dp[i]) % MOD;

    printf("%d\n", ans);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int A, B;
        scanf("%d%d", &A, &B);
        ve[A].push_back(B);
        deg[B]++;
        vis[A] = 1;
    }
    toposort();

    return 0;
}