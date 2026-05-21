/*
 *  @date: 2026-03-27 12:41:21  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Islands War.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, ans = 1;
pair<int, int> p[N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &p[i].first, &p[i].second);
    sort(p + 1, p + 1 + m);
    int r = p[1].second;
    for (int i = 2; i <= m; i++)
    {
        if (p[i].first >= r)
            ans++, r = p[i].second;
        else
            r = min(r, p[i].second);
    }
    printf("%d\n", ans);
    return 0;
}