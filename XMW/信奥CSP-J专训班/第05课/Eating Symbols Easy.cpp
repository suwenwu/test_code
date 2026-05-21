/*
 *  @date: 2026-04-04 13:08:36  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Eating Symbols Easy.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

string s;
int cnt;

int main()
{
    cin >> s;
    for (auto i : s)
    {
        if (i == '-')
            cnt--;
        else
            cnt++;
    }
    cout << cnt;
    return 0;
}