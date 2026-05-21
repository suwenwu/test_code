/*
 *  @date: 2026-05-15 14:51:06  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 线段树(一).cpp
 */
#include <bits/stdc++.h>
#define lt k << 1
#define rt k << 1 | 1
#define N 200005
#define ll long long

using namespace std;

struct node
{
    int l, r;
    ll sum, lazy;
} tree[N << 2];
int n, m, a[N];

void pushdown(int k) // 下传懒标记
{
    if (tree[k].lazy)
    {
        tree[lt].lazy += tree[k].lazy;
        tree[rt].lazy += tree[k].lazy;
        tree[lt].sum += tree[k].lazy * (tree[lt].r - tree[lt].l + 1);
        tree[rt].sum += tree[k].lazy * (tree[rt].r - tree[rt].l + 1);
        tree[k].lazy = 0;
    }
}

void build(int k, int l, int r)
{
    tree[k] = {l, r, 0, 0};
    if (l == r)
    {
        tree[k].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lt, l, mid);
    build(rt, mid + 1, r);
    tree[k].sum = tree[lt].sum + tree[rt].sum;
}

void update(int k, int l, int r, int val)
{
    if (tree[k].l >= l && tree[k].r <= r)
    {
        tree[k].lazy += val;
        tree[k].sum += val * (tree[k].r - tree[k].l + 1);
        return;
    }
    pushdown(k); // 先下传懒标记
    int mid = (tree[k].l + tree[k].r) >> 1;
    if (l <= mid)
        update(lt, l, r, val);
    if (r > mid)
        update(rt, l, r, val);
    tree[k].sum = tree[lt].sum + tree[rt].sum;
}

ll query(int k, int l, int r)
{
    if (tree[k].l >= l && tree[k].r <= r)
        return tree[k].sum;
    pushdown(k); // 先下传懒标记
    int mid = (tree[k].l + tree[k].r) >> 1;
    ll res = 0;
    if (l <= mid)
        res += query(lt, l, r);
    if (r > mid)
        res += query(rt, l, r);
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n); // 建树
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        if (x == 1)
        {
            int l, r, val;
            scanf("%d%d%d", &l, &r, &val);
            update(1, l, r, val); // 区间修改
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, l, r)); // 区间查询
        }
    }
    return 0;
}