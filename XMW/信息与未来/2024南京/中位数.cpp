/*
 *  @date: 2026-05-03 19:03:33  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 中位数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, a[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int mid = (n + 1) / 2;  // 排序后的中位数位置（1-indexed）
    int cnt1 = count_if(a + 1, a + n + 1, [&](int x)
                        { return x < a[mid]; });
    int cnt2 = count_if(a + 1, a + n + 1, [&](int x)
                        { return x > a[mid]; });
    printf("%d\n", cnt1 == cnt2 ? a[mid] : -1);
    return 0;
}