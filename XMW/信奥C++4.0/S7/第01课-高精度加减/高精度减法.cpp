/*
 *  @date: 2026-03-19 15:23:01  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 高精度加法.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

char s1[N], s2[N];
int a[N], b[N], c[N];

int main()
{
    scanf("%s%s", s1 + 1, s2 + 1);
    int len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
    if (len1 < len2 || (len1 == len2 && strcmp(s1 + 1, s2 + 1) < 0))
    {
        printf("-");
        swap(s1, s2);
        swap(len1, len2);
    }
    for (int i = 1; i <= len1; i++)
        a[i] = s1[len1 - i + 1] - '0';
    for (int i = 1; i <= len2; i++)
        b[i] = s2[len2 - i + 1] - '0';
    for (int i = 1; i <= len1; i++)
    {
        c[i] += a[i] - b[i];
        if (c[i] < 0)
        {
            c[i + 1]--;
            c[i] += 10;
        }
    }
    while (!c[len1] && len1 > 1)
        len1--;
    for (int i = len1; i >= 1; i--)
        printf("%d", c[i]);
    return 0;
}