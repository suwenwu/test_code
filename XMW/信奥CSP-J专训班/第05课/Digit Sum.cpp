/*
 *  @date: 2026-04-04 13:09:06  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Digit Sum.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, sum;

int main()
{
    cin >> n;
    int tmp = n;
    while (tmp)
    {
        sum += tmp % 10;
        tmp /= 10;
    }
    if (n % sum)
        cout << "No";
    else
        cout << "Yes";
    return 0;
}