/*
 *  @date: 2026-04-25 13:06:14  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
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

    for (int i = 1; i <= n - 1; i++) // 循环i轮，选择第i个数作为最小值
    {
        // 一轮要做的事情
        int min_idx = i; // 假设最小值的下标为i
        for (int j = i + 1; j <= n; j++)
            if (a[j] < a[min_idx])
                min_idx = j;
        swap(a[i], a[min_idx]); // 将最小值放到第i个位置
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}