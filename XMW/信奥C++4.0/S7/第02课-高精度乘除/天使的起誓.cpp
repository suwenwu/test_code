/*
 *  @date: 2026-03-26 10:16:15  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 天使的起誓.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1005
#define ll long long

using namespace std;

int n, ans, a[N];
string m;

int main()
{
    cin >> n >> m;
    int len = m.size();
    for (int i = 0; i < len; i++)
        a[i] = m[i] - '0';
    for (int i = 0; i < len; i++)
        ans = (ans * 10 + a[i]) % n;
    cout << (ans == 0 ? n : ans);
    return 0;
}