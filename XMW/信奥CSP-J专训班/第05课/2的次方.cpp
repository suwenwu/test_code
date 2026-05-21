/*
 *  @date: 2026-04-04 13:10:20  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 2的次方.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

ll n;

int main()
{
    scanf("%lld", &n);
    if ((n & (n - 1)) == 0)
        printf("Yes");
    else
        printf("No");
    return 0;
}