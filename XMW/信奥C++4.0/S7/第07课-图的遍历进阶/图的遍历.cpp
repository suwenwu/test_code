/*
 *  @date: 2026-04-25 19:00:58  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 图的遍历.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m;
vector<int> g[N];
int ans[N];

void bfs(int x, int fa) // x为起点，fa最大的点
{
    ans[x] = fa;
    queue<int> q;
    q.push(x);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (!ans[v])
            {
                ans[v] = fa;
                q.push(v);
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u); // 反向建边
    }
    for (int i = n; i >= 1; i--)
    {
        if (!ans[i])
            bfs(i, i);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}