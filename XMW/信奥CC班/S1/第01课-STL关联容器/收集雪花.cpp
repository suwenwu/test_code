/*
 *  @date: 2026-03-20 14:35:19  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 收集雪花.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1000005
#define ll long long

using namespace std;

int n, a[N], l = 1, ans = 1;
unordered_map<int, bool> mp;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        while (mp[a[i]])
        {
            mp[a[l]] = false;
            l++;
        }
        mp[a[i]] = true;
        ans = max(ans, i - l + 1);
    }
    printf("%d\n", ans);
    return 0;
}