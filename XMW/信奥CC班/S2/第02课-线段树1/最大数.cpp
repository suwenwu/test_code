/*
 *  @date: 2026-05-08 14:57:51  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最大数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define lc (p << 1)
#define rc ((p << 1) | 1)
#define ll long long

using namespace std;

struct Node
{
    int l, r;
    ll w;
} tree[N];
int a[N];

void build(int p, int l, int r)
{
    tree[p].l = l;
    tree[p].r = r;
    if (l == r)
    {
        tree[p].w = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[p].w = max(tree[lc].w, tree[rc].w);
}

int query(int p, int l, int r)
{
    if (l <= tree[p].l && tree[p].r <= r)
        return tree[p].w;
    int mid = (tree[p].l + tree[p].r) >> 1;
    int res = 0;
    if (l <= mid)
        res = max(res, query(lc, l, r));
    if (r > mid)
        res = max(res, query(rc, l, r));
    return res;
}

void update(int p, int x, int v)
{
    if (tree[p].l == tree[p].r)
    {
        tree[p].w += v;
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (x <= mid)
        update(lc, x, v);
    else
        update(rc, x, v);
    tree[p].w = max(tree[lc].w, tree[rc].w);
}

int m, d, n;

int main()
{
    scanf("%d%d", &m, &d);
    build(1, 1, 200000);
    ll t = 0;
    while (m--)
    {
        char c;
        ll x;
        cin >> c >> x;
        if (c == 'A')
        {
            a[++n] = (x + t) % d;
            update(1, n, a[n]);
        }
        else
        {
            t = query(1, n - x + 1, n);
            cout << t << endl;
        }
    }
    return 0;
}