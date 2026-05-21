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

int n, x;
int fa[N];
struct edge
{
    int u, v, w;
    friend bool operator<(edge a, edge b)
    {
        return a.w < b.w;
    }
};
vector<edge> e;

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
    int ans = 0, len = e.size();
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < len; i++)
    {
        if (find(e[i].u) != find(e[i].v))
        {
            merge(e[i].u, e[i].v);
            ans += e[i].w;
        }
    }
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &x);
            if (x && j > i)
                e.push_back({i, j, x});
        }
    sort(e.begin(), e.end());
    printf("%d\n", kruskal());
    return 0;
}