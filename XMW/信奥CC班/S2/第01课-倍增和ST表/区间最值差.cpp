/*
 *  @date: 2026-04-17 16:03:12  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 区间最值差.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 50005
#define ll long long

using namespace std;

int n, m, l, r;
int st_max[N][20], st_min[N][20];

int qmax(int l, int r)
{
    int k = log2(r - l + 1);
    int maxn = max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
    int minn = min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
    return maxn - minn;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &st_max[i][0]);
        st_min[i][0] = st_max[i][0];
    }
    for (int j = 1; j <= 19; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
            st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
        }
    while (m--)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", qmax(l, r));
    }
    return 0;
}