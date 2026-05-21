/*
 *  @date: 2026-05-03 19:28:40  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 杂务.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, k, a, dp[N], deg[N], times[N];
vector<int> ve[N];

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 0)
        {
            q.push(i);
            dp[i] = times[i];
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < ve[u].size(); i++)
        {
            int v = ve[u][i];
            dp[v] = max(dp[v], dp[u] + times[v]);
            if (--deg[v] == 0)
                q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d\n", ans);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &times[i], &k);
        while (k--)
        {
            scanf("%d", &a);
            ve[a].push_back(i);
            deg[i]++;
        }
    }
    toposort();
    return 0;
}