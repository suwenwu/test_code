/*
 *  @date: 2026-05-24 15:25:04  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最短网络.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

struct Edge
{
    int u, v, w;
    friend bool operator<(Edge a, Edge b)
    {
        return a.w < b.w;
    }
};
int n, m, fa[N];
vector<Edge> edges;

int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
        fa[fx] = fy;
}

void kruskal()
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    int cnt = 0, ans = 0;
    for (auto edge : edges)
    {
        if (find(edge.u) != find(edge.v))
        {
            merge(edge.u, edge.v);
            cnt++;
            ans += edge.w;
        }
    }
    printf("%d\n", ans);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int w;
            scanf("%d", &w);
            if (j > i)
                edges.push_back({i, j, w});
        }
    }
    sort(edges.begin(), edges.end());
    kruskal();
    return 0;
}