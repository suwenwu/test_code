/*
 *  @date: 2026-04-18 14:06:50  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 插入排序.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, a[N], x;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i]; // 3 4 6 8 9

    for (int i = 2; i <= n; i++)
    {
        for (int j = i; j >= 2 && a[j] < a[j - 1]; j--)
            swap(a[j], a[j - 1]);
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}