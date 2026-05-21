/*
 *  @date: 2026-04-01 13:10:11  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 第k小的数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 5000005
#define ll long long

using namespace std;

int n, a[N], k;

int partition(int a[], int l, int r)
{
    int i = l, j = r, x = a[l];
    while (i < j)
    {
        while (i < j && a[j] >= x)
            j--;
        a[i] = a[j];
        while (i < j && a[i] <= x)
            i++;
        a[j] = a[i];
    }
    a[i] = x;
    return i;
}

void Quicksort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int pos = partition(a, l, r);
    Quicksort(a, l, pos - 1);
    Quicksort(a, pos + 1, r);
    if (pos >= k)
    {
        printf("%d", a[k]);
        exit(0);
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    k += 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    Quicksort(a, 1, n);
    return 0;
}