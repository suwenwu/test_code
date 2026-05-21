/*
 *  @date: 2026-04-09 11:22:04  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Out of Hay S.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 20005
#define ll long long

using namespace std;

int n, m, ans;
struct edge
{
    int u, v, w;
    friend bool operator<(edge a, edge b)
    {
        return a.w < b.w;
    }
} e[N];
int fa[N];

int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void kruskal()
{
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = find(u), fv = find(v);
        if (fu != fv)
        {
            fa[fu] = fv;
            cnt++;
            if (cnt == n - 1)
            {
                ans = w;
                break;
            }
        }
    }
    printf("%d\n", ans);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m + 1);
    kruskal();
    return 0;
}