/*
 *  @date: 2026-04-18 14:22:08  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 冒泡排序.cpp
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
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= n - i; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}