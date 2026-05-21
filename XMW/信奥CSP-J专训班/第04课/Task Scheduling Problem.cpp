/*
 *  @date: 2026-03-27 12:34:34  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Task Scheduling Problem.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    cout << max({a, b, c}) - min({a, b, c});
    return 0;
}