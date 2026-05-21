/*
 *  @date: 2026-05-21 13:05:59  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Maximize the Formula.cpp
 */
#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main()
{
    cin >> a >> b >> c;
    cout << max({a * 10 + b + c, b * 10 + a + c, c * 10 + a + b});
    return 0;
}