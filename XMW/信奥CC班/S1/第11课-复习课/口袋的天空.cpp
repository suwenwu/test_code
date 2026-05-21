/*
 *  @date: 2026-04-09 11:18:02  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 口袋的天空.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct node
{
    int u, v, w;
    friend bool operator<(node a, node b)
    {
        return a.w < b.w;
    }
} e[N];
int n, m, k, f[N], ans;

int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}

bool kruskal()
{
    for (int i = 1; i <= n; i++)
        f[i] = i;
    int cnt = n;
    for (int i = 1; i <= m; i++)
    {
        int r1 = find(e[i].u), r2 = find(e[i].v);
        if (r1 != r2)
        {
            cnt--;
            f[r2] = r1;
            ans += e[i].w;
            if (cnt == k)
                return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + 1 + m);
    if (kruskal())
        printf("%d", ans);
    else
        printf("No Answer");
    return 0;
}