/*
 *  @date: 2026-05-21 13:07:35  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: Dimensional World's Tale.cpp
 */
#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, tmp, maxa = INT_MIN, minb = INT_MAX;

int main()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        maxa = max(maxa, tmp);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &tmp);
        minb = min(minb, tmp);
    }
    if (minb > maxa && minb > x && minb <= y)
        printf("No War\n");
    else
        printf("War\n");
    return 0;
}