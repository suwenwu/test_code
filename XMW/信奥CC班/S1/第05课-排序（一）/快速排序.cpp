/*
 *  @date: 2026-04-01 12:52:04  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 快速排序.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, a[N];

int partition(int a[], int l, int r)
{
    int k = a[l]; // 枢轴
    while (l < r)
    {
        while (l < r && a[r] >= k)
            r--;
        a[l] = a[r];
        while (l < r && a[l] <= k)
            l++;
        a[r] = a[l];
    }
    a[l] = k;
    return l;
}

void QuickSort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int pos = partition(a, l, r);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    QuickSort(a, l, pos - 1);
    QuickSort(a, pos + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    QuickSort(a, 1, n);
    return 0;
}