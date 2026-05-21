/*
 *  @date: 2026-04-19 18:38:32  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 有向图的权重.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

int n, m;
struct node
{
    int v, w;
};
vector<node> g[N];
ll ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((node){v, w});
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < g[i].size(); j++)
            ans += g[i][j].w;
    printf("%lld\n", ans);
    return 0;
}