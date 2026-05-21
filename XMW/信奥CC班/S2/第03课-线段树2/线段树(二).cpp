/*
 *  @date: 2026-05-15 15:34:31  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 线段树(二).cpp
 */
#include <bits/stdc++.h>
#define lt k << 1
#define rt k << 1 | 1
#define N 100005
#define ll long long

using namespace std;
struct node
{
    int l, r;
    ll sum, add_lazy, mul_lazy; // sum:区间和,add_lazy:区间加法懒标记,mul_lazy:区间乘法懒标记
} tree[N << 2];
int n, q, m, a[N];

void build(int k, int l, int r)
{
    tree[k] = {l, r, 0, 0, 1}; // 初始化乘法懒标记为1
    if (l == r)
    {
        tree[k].sum = a[l] % m;
        return;
    }
    int mid = (l + r) >> 1;
    build(lt, l, mid);
    build(rt, mid + 1, r);
    tree[k].sum = (tree[lt].sum + tree[rt].sum) % m;
}

void push_down(int k)
{
    auto &p = tree[k], &lc = tree[lt], &rc = tree[rt];
    // 1.先处理左孩子
    lc.sum = (lc.sum * p.mul_lazy + (lc.r - lc.l + 1) * p.add_lazy) % m;
    lc.mul_lazy = (lc.mul_lazy * p.mul_lazy) % m;
    lc.add_lazy = (lc.add_lazy * p.mul_lazy + p.add_lazy) % m;
    // 2.再处理右孩子
    rc.sum = (rc.sum * p.mul_lazy + (rc.r - rc.l + 1) * p.add_lazy) % m;
    rc.mul_lazy = (rc.mul_lazy * p.mul_lazy) % m;
    rc.add_lazy = (rc.add_lazy * p.mul_lazy + p.add_lazy) % m;
    // 3.清空当前节点的懒标记
    p.mul_lazy = 1;
    p.add_lazy = 0;
}

void update_mul(int k, int l, int r, int v)
{
    if (tree[k].l >= l && tree[k].r <= r)
    {
        tree[k].sum = (tree[k].sum * v) % m;
        tree[k].mul_lazy = (tree[k].mul_lazy * v) % m;
        tree[k].add_lazy = (tree[k].add_lazy * v) % m;
        return;
    }
    push_down(k);
    int mid = (tree[k].l + tree[k].r) >> 1;
    if (l <= mid)
        update_mul(lt, l, r, v);
    if (r > mid)
        update_mul(rt, l, r, v);
    tree[k].sum = (tree[lt].sum + tree[rt].sum) % m; // 更新当前节点的区间和
}

void update_add(int k, int l, int r, int v)
{
    if (tree[k].l >= l && tree[k].r <= r)
    {
        tree[k].sum = (tree[k].sum + (tree[k].r - tree[k].l + 1) * v) % m;
        tree[k].add_lazy = (tree[k].add_lazy + v) % m;
        return;
    }
    push_down(k);
    int mid = (tree[k].l + tree[k].r) >> 1;
    if (l <= mid)
        update_add(lt, l, r, v);
    if (r > mid)
        update_add(rt, l, r, v);
    tree[k].sum = (tree[lt].sum + tree[rt].sum) % m; // 更新当前节点的区间和
}

ll query(int k, int l, int r)
{
    if (tree[k].l >= l && tree[k].r <= r)
        return tree[k].sum;
    push_down(k);
    int mid = (tree[k].l + tree[k].r) >> 1;
    ll res = 0;
    if (l <= mid)
        res += query(lt, l, r);
    if (r > mid)
        res += query(rt, l, r);
    return res % m;
}

int main()
{
    scanf("%d%d%d", &n, &q, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    while (q--)
    {
        int opt, l, r, v;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
        {
            scanf("%d", &v);
            update_mul(1, l, r, v);
        }
        else if (opt == 2)
        {
            scanf("%d", &v);
            update_add(1, l, r, v);
        }
        else
            printf("%lld\n", query(1, l, r));
    }
    return 0;
}