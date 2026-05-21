/*
 *  @date: 2026-04-11 14:36:05  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 可爱的猫咪.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int a[1005], b[1005];
int n, l, r, k, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
    {
        cin >> l >> r >> k;
        int idx = 0;
        for (int j = l; j <= r; j++)
            b[++idx] = a[j];
        sort(b + 1, b + idx + 1);
        cout << b[k] << endl;
    }
    return 0;
}