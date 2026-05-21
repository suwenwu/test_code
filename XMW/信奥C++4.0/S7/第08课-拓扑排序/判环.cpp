/*
 *  @date: 2026-05-03 18:29:13  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 判环.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

vector<int> ve[N];
int n, m, deg[N];

void toposort()
{
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    vector<int> ans;
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        ans.push_back(u);
        for (int i = 0; i < ve[u].size(); i++)
        {
            int v = ve[u][i];
            if (--deg[v] == 0)
                q.push(v);
        }
    }
    if (ans.size() != n)
        printf("has circle");
    else
        for (int i = 0; i < ans.size(); i++)
            printf("%d ", ans[i]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ve[u].push_back(v);
        deg[v]++;
    }
    toposort();
    return 0;
}