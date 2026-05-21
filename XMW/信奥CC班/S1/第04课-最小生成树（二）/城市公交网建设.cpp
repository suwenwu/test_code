/*
 *  @date: 2026-03-25 14:02:28  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 城市公交网建设.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

int n, m;
struct Edge
{
    int u, v, w;
    friend bool operator<(const Edge &a, const Edge &b)
    {
        return a.w < b.w;
    }
} e[N * N];
int fa[N];
vector<pair<int, int>> ans;

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

void kruskal()
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = find(u), fv = find(v);
        if (fu != fv)
        {
            fa[fu] = fv;
            ans.push_back({u, v});
        }
    }
    sort(ans.begin(), ans.end());
    for (auto [u, v] : ans)
        printf("%d %d\n", u, v);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        if (e[i].u > e[i].v)
            swap(e[i].u, e[i].v);
    }
    sort(e + 1, e + m + 1);
    kruskal();
    return 0;
}