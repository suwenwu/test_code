/*
 *  @date: 2026-04-01 10:52:37  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 升序.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, a[N], c[N];

void Merge(int l, int mid, int r)
{
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            c[k++] = a[i++];
        else
            c[k++] = a[j++];
    }
    while (i <= mid)
        c[k++] = a[i++];
    while (j <= r)
        c[k++] = a[j++];
    for (int i = l; i <= r; i++)
        a[i] = c[i];
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void merge_sort(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    Merge(l, mid, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    merge_sort(1, n);
    return 0;
}