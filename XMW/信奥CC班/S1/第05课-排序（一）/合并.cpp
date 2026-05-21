/*
 *  @date: 2026-04-01 10:37:21  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 合并.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, a[N], b[N], c[N], cnt;

void Merge()
{
    int i = 1, j = 1;
    while (i <= n && j <= m)
    {
        if (a[i] <= b[j])
            c[++cnt] = a[i++];
        else
            c[++cnt] = b[j++];
    }
    while (i <= n)
        c[++cnt] = a[i++];
    while (j <= m)
        c[++cnt] = b[j++];
    for (int i = 1; i <= cnt; i++)
        printf("%d ", c[i]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    merge(a + 1, a + n + 1, b + 1, b + m + 1, c + 1);
    for (int i = 1; i <= n + m; i++)
        printf("%d ", c[i]);
    // Merge();
    return 0;
}