/*
 *  @date: 2026-04-01 10:27:18  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 划分.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

int n, a[N];

void Divide(int left, int right, int b[])
{
    if (left >= right)
        return;
    int mid = left + right >> 1;
    for (int i = left; i <= mid; i++)
        printf("%d ", b[i]);
    printf(", ");
    for (int i = mid + 1; i <= right; i++)
        printf("%d ", b[i]);
    printf("\n");
    Divide(left, mid, b);
    Divide(mid + 1, right, b);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    Divide(1, n, a);
    return 0;
}