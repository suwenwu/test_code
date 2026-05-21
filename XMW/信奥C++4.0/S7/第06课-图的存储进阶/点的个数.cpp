/*
 *  @date: 2026-04-19 19:51:41  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 点的个数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

vector<int> g[N];
int n, m, ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (g[i].size() <= 3)
            ans++;
    printf("%d\n", ans);
    return 0;
}