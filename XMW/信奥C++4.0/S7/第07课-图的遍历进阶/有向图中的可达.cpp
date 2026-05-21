/*
 *  @date: 2026-05-04 16:11:46  星期一
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, a, b;
vector<int> g[N];
bool vis[N];

void dfs(int u)
{
    vis[u] = true;
    // for (int i = 0; i < g[u].size(); i++)
    // {
    //     int v = g[u][i];
    //     if (!vis[v])
    //         dfs(v);
    // }
    for (auto v : g[u])
        if (!vis[v])
            dfs(v);
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v); // g[v].push_back(u);
    }
    dfs(a);
    printf("%s", vis[b] ? "Yes" : "No");
    return 0;
}