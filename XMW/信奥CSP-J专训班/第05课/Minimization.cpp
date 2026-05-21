/*
 *  @date: 2026-04-04 13:09:36  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Minimization.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    printf("%d", int(ceil((n - 1) * 1.0 / (k - 1))));
    return 0;
}