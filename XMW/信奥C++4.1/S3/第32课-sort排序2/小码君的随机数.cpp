/*
 *  @date: 2026-04-11 14:25:38  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 小码君的随机数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1005
#define ll long long

using namespace std;

bool bucket[1005];
int n, cnt;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (bucket[x])
            continue;
        bucket[x] = true;
        cnt++;
    }
    cout << cnt << " ";
    for (int i = 1; i <= 1000; i++)
        if (bucket[i])
            cout << i << " ";
    return 0;
}