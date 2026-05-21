/*
 *  @date: 2026-04-17 16:28:35  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 快速幂.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

ll a, b, p;

ll quick_pow(ll a, ll b, ll p)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld^%lld mod %lld=%lld", a, b, p, quick_pow(a, b, p));
    return 0;
}