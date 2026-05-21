/*
 *  @date: 2026-05-03 18:23:53  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 摄像头.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 505
#define ll long long

using namespace std;

bool vis[N];
int n, x, y, m, deg[N];
vector<int> ve[N];

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 0)
        {
            vis[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < ve[u].size(); i++)
        {
            int v = ve[u][i];
            if (--deg[v] == 0)
            {
                q.push(v);
                vis[v] = 1;
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &m);
        while (m--)
        {
            scanf("%d", &y);
            ve[x].push_back(y);
            deg[y]++;
        }
    }
    toposort();
    int num = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            num++;
    if (num)
        printf("%d", num);
    else
        printf("YES");
    return 0;
}