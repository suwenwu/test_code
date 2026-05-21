/*
 *  @date: 2026-03-27 12:36:05  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: String Rotation.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

string s, t;

int main()
{
    cin >> s >> t;
    s += s;
    if (s.find(t,1) == string::npos)
        printf("No");
    else
        printf("Yes");
    return 0;
}