/*
 *  @date: 2026-04-01 13:05:02  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 基数排序（升序）.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, a[N], maxNum;
int cnt[10], b[N];

void RadixSort(int n, int arr[], int exp)
{
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++)
    {
        int digit = (arr[i] / exp) % 10;
        cnt[digit]++;
    }
    for (int i = 1; i <= 9; i++)
        cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--)
    {
        int digit = (arr[i] / exp) % 10;
        b[cnt[digit]] = arr[i];
        cnt[digit]--;
    }
    for (int i = 1; i <= n; i++)
        arr[i] = b[i];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        maxNum = max(maxNum, a[i]);
    }
    for (int i = 1; i <= maxNum; i *= 10)
    {
        RadixSort(n, a, i);
        for (int j = 1; j <= n; j++)
            printf("%d ", a[j]);
        printf("\n");
    }
    return 0;
}