/*
 *  @date: 2026-03-18 10:51:08  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, fa[N], sum;
struct edge
{
    int u, v, w;
    friend bool operator<(edge a, edge b)
    {
        return a.w < b.w;
    }
} e[N];

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
        fa[fx] = fy;
}

int kruskal()
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        if (find(e[i].u) != find(e[i].v))
        {
            merge(e[i].u, e[i].v);
            ans += e[i].w;
        }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), sum += e[i].w;
    sort(e + 1, e + 1 + m);
    printf("%d\n", sum - kruskal());
    return 0;
}