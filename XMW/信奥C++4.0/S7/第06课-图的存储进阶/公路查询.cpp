/*
 *  @date: 2026-04-19 19:29:49  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 公路查询.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, q;
struct node
{
    int v, w;
};
vector<node> g[N];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back({v, w});
    }
    while (q--)
    {
        int u;
        scanf("%d", &u);
        for (int i = g[u].size() - 1; i >= 0; i--)
            printf("%d %d\n", g[u][i].v, g[u][i].w);
    }
    return 0;
}

/*
链式前向星
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, q, head[N], cnt;
struct edge
{
    int v, next, w;
} e[N];

void add(int u, int v, int w)
{
    e[++cnt] = {v, head[u], w};
    head[u] = cnt;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    while (q--)
    {
        int u;
        scanf("%d", &u);
        for (int i = head[u]; i; i = e[i].next)
            printf("%d %d\n", e[i].v, e[i].w);
    }
    return 0;
}
*/