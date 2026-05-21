/*
 *  @date: 2026-04-29 13:47:22  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最大值.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define lc (p << 1)
#define rc (p << 1 | 1)
#define ll long long

using namespace std;

struct node
{
    int l, r, maxn;
} tree[N << 2];
int n, m;
int a[N];

void build(int p, int l, int r)
{
    tree[p].l = l;
    tree[p].r = r;
    if (l == r)
    {
        tree[p].maxn = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[p].maxn = max(tree[lc].maxn, tree[rc].maxn);
}

void update(int p, int x, int k)
{
    if (tree[p].l == tree[p].r)
    {
        tree[p].maxn = max(tree[p].maxn, k);
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (x <= mid)
        update(lc, x, k);
    if (x > mid)
        update(rc, x, k);
    tree[p].maxn = max(tree[lc].maxn, tree[rc].maxn);
}

int query(int p, int l, int r)
{
    if (tree[p].l >= l && tree[p].r <= r)
        return tree[p].maxn;
    int mid = (tree[p].l + tree[p].r) >> 1;
    int ans = INT_MIN;
    if (l <= mid)
        ans = max(ans, query(lc, l, r));
    if (r > mid)
        ans = max(ans, query(rc, l, r));
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--)
    {
        char c;
        int x, y;
        scanf(" %c%d%d", &c, &x, &y);
        if (c == 'Q')
            printf("%d\n", query(1, x, y));
        else
            update(1, x, y);
    }
    return 0;
}