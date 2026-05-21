/*
 *  @date: 2026-04-11 14:10:35  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 小码君拼数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 25
#define ll long long

using namespace std;

int n;
string s[N];

bool cmp(string a, string b)
{
    return a + b > b + a;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        cout << s[i];
    return 0;
}