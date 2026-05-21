/*
 *  @date: 2026-05-14 17:39:13  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n;
struct node
{
    int x, y, sum, id;
    friend bool operator<(const node &a, const node &b)
    {
        if (a.sum == b.sum)
        {
            if (a.x == b.x)
            {
                if (a.y == b.y)
                    return a.id < b.id;
                return a.y < b.y;
            }
            return a.x < b.x;
        }
        return a.sum < b.sum;
    }
} e[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &e[i].x, &e[i].y), e[i].id = i, e[i].sum = e[i].x + e[i].y;
    sort(e + 1, e + n + 1);
    for (int i = 1; i <= n; i++)
        printf("%d ", e[i].id);
    return 0;
}