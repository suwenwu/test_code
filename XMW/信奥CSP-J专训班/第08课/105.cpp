/*
 *  @date: 2026-04-26 09:44:37  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 105.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long
using namespace std;

int n, ans;

int main()
{
    cin >> n;
    if (n < 105)
        cout << 0;
    else if (n >= 105 && n < 135)
        cout << 1;
    else if (n >= 135 && n < 165)
        cout << 2;
    else if (n >= 165 && n < 189)
        cout << 3;
    else if (n >= 189 && n < 195)
        cout << 4;
    else
        cout << 5;
    return 0;
}