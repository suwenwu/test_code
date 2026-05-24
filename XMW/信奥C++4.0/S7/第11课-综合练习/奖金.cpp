/*
 *  @date: 2026-05-24 15:21:03  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 奖金.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

vector<int> g[N];
int n, m, indeg[N], ans[N], cnt, res;

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i), ans[i] = 100;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cnt++;
        res += ans[u];
        for (int v : g[u])
        {
            ans[v] = max(ans[v], ans[u] + 1);
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }
    if (cnt == n)
        printf("%d\n", res);
    else
        printf("Poor Xed\n");
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        indeg[u]++;
    }
    toposort();
    return 0;
}