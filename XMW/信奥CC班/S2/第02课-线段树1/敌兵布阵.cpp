/*
 *  @date: 2026-04-29 14:17:52  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 敌兵布阵.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 50005
#define ll long long
#define lc (k << 1)
#define rc (k << 1 | 1)

using namespace std;

struct Node
{
    int l, r, sum;
} tree[N << 2];
int a[N], n;

void build(int k, int l, int r)
{
    tree[k].l = l;
    tree[k].r = r;
    if (l == r)
    {
        tree[k].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

void update(int k, int x, int y)
{
    if (tree[k].l == tree[k].r)
    {
        tree[k].sum += y;
        return;
    }
    int mid = (tree[k].l + tree[k].r) >> 1;
    if (x <= mid)
        update(lc, x, y);
    else
        update(rc, x, y);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

int query(int k, int l, int r)
{
    if (l <= tree[k].l && tree[k].r <= r)
        return tree[k].sum;
    int mid = (tree[k].l + tree[k].r) >> 1;
    int res = 0;
    if (l <= mid)
        res += query(lc, l, r);
    if (r > mid)
        res += query(rc, l, r);
    return res;
}

void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    string s;
    while (cin >> s && s != "End")
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (s == "Query")
            printf("%d\n", query(1, l, r));
        else if (s == "Add")
            update(1, l, r);
        else
            update(1, l, -r);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}