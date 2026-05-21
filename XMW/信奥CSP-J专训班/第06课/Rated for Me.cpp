/*
 *  @date: 2026-04-10 13:21:50  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Rated for Me.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n < 1200)
        cout << "ABC\n";
    else if (n < 2800)
        cout << "ARC\n";
    else
        cout << "AGC\n";
    return 0;
}