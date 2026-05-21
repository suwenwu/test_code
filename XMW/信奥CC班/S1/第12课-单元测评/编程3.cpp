/*
 *  @date: 2026-04-17 14:47:23  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 编程3.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, tot, fa[N];
ll ans;

struct node
{
    int k;
    ll c;
    vector<int> s;
    friend bool operator<(node a, node b)
    {
        return a.c < b.c;
    }
} e[N];

int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void kruskal()
{
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int fx = find(e[i].s[0]);
        for (int j = 1; j <= e[i].k - 1; j++)
        {
            int fy = find(e[i].s[j]);
            if (fx == fy)
                continue;
            fa[fy] = fx;
            ans += e[i].c;
            tot++;
            if (tot == n - 1)
            {
                printf("%lld", ans);
                return;
            }
        }
    }
    printf("-1");
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%lld", &e[i].k, &e[i].c);
        for (int j = 1; j <= e[i].k; j++)
        {
            int x;
            scanf("%d", &x);
            e[i].s.push_back(x);
        }
    }
    kruskal();
    return 0;
}