/*
 *  @date: 2026-05-03 19:34:36  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 时间线.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, c, S[N], deg[N];
struct node
{
    int v, w;
};
vector<node> ve[N];
int dp[N];

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = S[i];
        if (deg[i] == 0)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < ve[u].size(); i++)
        {
            int v = ve[u][i].v, w = ve[u][i].w;
            dp[v] = max(dp[v], dp[u] + w);
            if (--deg[v] == 0)
                q.push(v);
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", dp[i]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    for (int i = 1; i <= c; i++)
    {
        int a, b, x;
        scanf("%d%d%d", &a, &b, &x);
        ve[a].push_back({b, x});
        deg[b]++;
    }
    toposort();
    return 0;
}
