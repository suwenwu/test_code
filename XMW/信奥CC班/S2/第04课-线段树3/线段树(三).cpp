/*
 *  @date: 2026-05-23 11:00:08  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 线段树(三).cpp
 */
#include <bits/stdc++.h>
#define lc(p) (p << 1)
#define rc(p) (p << 1 | 1)
#define N 100005
#define ll long long

using namespace std;

int n, m, a[N << 2];

void push_down(int p)
{
    if (a[p])
    {
        a[lc(p)] ^= 1;
        a[rc(p)] ^= 1;
        a[p] = 0;
    }
}

void update(int p, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
    {
        a[p] ^= 1;
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(lc(p), l, mid, x, y);
    if (y > mid)
        update(rc(p), mid + 1, r, x, y);
}

int query(int p, int l, int r, int x)
{
    if (l == r)
        return a[p];
    push_down(p);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return query(lc(p), l, mid, x);
    else
        return query(rc(p), mid + 1, r, x);
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int pos;
        scanf("%d", &pos);
        if (pos == 1)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            update(1, 1, n, l, r);
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", query(1, 1, n, x));
        }
    }
    return 0;
}