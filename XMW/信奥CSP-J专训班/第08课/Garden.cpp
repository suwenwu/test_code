/*
 *  @date: 2026-04-26 09:46:11  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Garden.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int a, b;

int main()
{
    scanf("%d%d", &a, &b);
    printf("%d", a * b - a - b + 1);
    return 0;
}