/*
 *  @date: 2026-04-19 20:03:46  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Resergd.
 *  @file: 公路查询2.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct node
{
    int v, w;
};
bool cmp(node A, node B)
{
    if (A.v != B.v)
        return A.v < B.v;
    return A.w < B.w;
}
vector<node> g[N];
int n, m, q;
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++)
    {
        int x, y, len;
        scanf("%d%d%d", &x, &y, &len);
        g[x].push_back({y, len});
    }
    for (int i = 1; i <= n; i++)
        sort(g[i].begin(), g[i].end(), cmp);
    while (q--)
    {
        int x;
        scanf("%d", &x);
        for (int i = 0; i < g[x].size(); i++)
        {
            int j = i;
            while (j < g[x].size() && g[x][j].v == g[x][i].v)
                j++;
            printf("%d %d\n", g[x][i].v, g[x][i].w);
            i = j - 1;
        }
    }
    return 0;
}