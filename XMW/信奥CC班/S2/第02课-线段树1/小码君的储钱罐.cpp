/*
 *  @date: 2026-04-29 13:17:39  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 小码君的储钱罐.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 500005
#define lc (p << 1)
#define rc (p << 1 | 1)
#define ll long long

using namespace std;

struct node
{
    int l, r;
    ll sum;
} tree[N << 2];

int n, m, a[N];

void build(int p, int l, int r)
{
    tree[p].l = l;
    tree[p].r = r;
    if (l == r)
    {
        tree[p].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid); // 递归建树
    build(rc, mid + 1, r);
    tree[p].sum = tree[lc].sum + tree[rc].sum; // 维护区间和
}

void update(int p, int x, int y)
{
    if (tree[p].l == tree[p].r)
    {
        tree[p].sum += y;
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (x <= mid)
        update(lc, x, y); // 如果x在左子树，递归更新左子树
    else
        update(rc, x, y);                      // 否则递归更新右子树
    tree[p].sum = tree[lc].sum + tree[rc].sum; // 更新当前节点的区间和
}

ll query(int p, int l, int r)
{
    if (tree[p].l >= l && tree[p].r <= r)
        return tree[p].sum; // 如果当前节点的区间完全包含在查询区间内，直接返回当前节点的区间和
    int mid = (tree[p].l + tree[p].r) >> 1;
    ll res = 0; // 初始化结果
    if (l <= mid)
        res += query(lc, l, r); // 如果查询区间与左子树有交集，递归查询左子树
    if (r > mid)
        res += query(rc, l, r); // 如果查询区间与右子树有交集，递归查询右子树
    return res;                 // 返回结果
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            update(1, x, y); // 将x加上y
        else
            printf("%lld\n", query(1, x, y)); // 查询区间和
    }
    return 0;
}