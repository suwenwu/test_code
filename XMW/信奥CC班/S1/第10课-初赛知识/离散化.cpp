/*
 *  @date: 2026-04-03 13:35:00  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 离散化.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, a[N], b[N];

void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    int m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}