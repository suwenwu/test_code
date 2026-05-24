/*
 *  @date: 2026-05-24 15:32:28  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 奶牛计划.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, t[N], ans[N], indeg[N], res;
vector<int> g[N];

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!indeg[i])
            q.push(i), ans[i] = t[i];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        res = max(res, ans[u]);
        for (int v : g[u])
        {
            ans[v] = max(ans[v], ans[u] + t[v]);
            indeg[v]--;
            if (!indeg[v])
                q.push(v);
        }
    }
    printf("%d\n", res);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        indeg[v]++;
    }
    toposort();
    return 0;
}