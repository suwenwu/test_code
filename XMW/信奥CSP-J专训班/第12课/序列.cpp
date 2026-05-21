/*
 *  @date: 2026-05-21 13:12:50  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 序列.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, ans, a[N];
struct node
{
    int id, cnt;
    friend bool operator<(node a, node b)
    {
        return a.cnt > b.cnt;
    }
} b1[N], b2[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 1)
        {
            b1[a[i]].id = a[i];
            b1[a[i]].cnt++;
        }
        else
        {
            b2[a[i]].id = a[i];
            b2[a[i]].cnt++;
        }
    }
    sort(b1 + 1, b1 + 100005);
    sort(b2 + 1, b2 + 100005);
    if (b1[1].id != b2[1].id)
        ans = (n - b1[1].cnt - b2[1].cnt);
    else
        ans = min(n - b1[1].cnt - b2[2].cnt, n - b1[2].cnt - b2[1].cnt);
    printf("%d\n", ans);
    return 0;
}