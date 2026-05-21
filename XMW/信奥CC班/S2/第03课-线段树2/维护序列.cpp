/*
 *  @date: 2026-05-21 14:20:14  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 维护序列.cpp
 */
#include <bits/stdc++.h>
#define ll long long
#define lt k << 1
#define rt k << 1 | 1
#define N 100005

using namespace std;

struct node
{
    int l, r;
    ll sum, add_lazy, mul_lazy; // sum:区间和,add_lazy:区间加法懒标记,mul_lazy:区间乘法懒标记
} tree[N << 2];
int n, m;
ll mod, a[N];

void push_down(int k)
{
    auto &p = tree[k], &lc = tree[lt], &rc = tree[rt];
    // 1.先处理左孩子
    lc.sum = (lc.sum * p.mul_lazy + (lc.r - lc.l + 1) * p.add_lazy) % mod;
    lc.mul_lazy = (lc.mul_lazy * p.mul_lazy) % mod;
    lc.add_lazy = (lc.add_lazy * p.mul_lazy + p.add_lazy) % mod;
    // 2.再处理右孩子
    rc.sum = (rc.sum * p.mul_lazy + (rc.r - rc.l + 1) * p.add_lazy) % mod;
    rc.mul_lazy = (rc.mul_lazy * p.mul_lazy) % mod;
    rc.add_lazy = (rc.add_lazy * p.mul_lazy + p.add_lazy) % mod;
    // 3.清空当前节点的懒标记
    p.mul_lazy = 1;
    p.add_lazy = 0;
}

void build(int k, int l, int r)
{
    tree[k] = {l, r, 0, 0, 1};
    if (l == r)
    {
        tree[k].sum = a[l] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(lt, l, mid);
    build(rt, mid + 1, r);
    tree[k].sum = (tree[lt].sum + tree[rt].sum) % mod;
}

void update_add(int k, int l, int r, ll x)
{
    auto &p = tree[k];
    if (p.l >= l && p.r <= r)
    {
        p.sum = (p.sum + x * (p.r - p.l + 1)) % mod;
        p.add_lazy = (p.add_lazy + x) % mod;
        return;
    }
    push_down(k); // 下传懒标记
    int mid = (p.l + p.r) >> 1;
    if (l <= mid)
        update_add(lt, l, r, x);
    if (r > mid)
        update_add(rt, l, r, x);
    p.sum = (tree[lt].sum + tree[rt].sum) % mod;
}

void update_mul(int k, int l, int r, ll x)
{
    auto &p = tree[k];
    if (p.l >= l && p.r <= r)
    {
        p.sum = (p.sum * x) % mod;
        p.add_lazy = (p.add_lazy * x) % mod;
        p.mul_lazy = (p.mul_lazy * x) % mod;
        return;
    }
    push_down(k); // 下传懒标记
    int mid = (p.l + p.r) >> 1;
    if (l <= mid)
        update_mul(lt, l, r, x);
    if (r > mid)
        update_mul(rt, l, r, x);
    p.sum = (tree[lt].sum + tree[rt].sum) % mod;
}

ll query(int k, int l, int r)
{
    auto &p = tree[k];
    if (p.l >= l && p.r <= r)
        return p.sum;
    push_down(k); // 下传懒标记
    int mid = (p.l + p.r) >> 1;
    ll res = 0;
    if (l <= mid)
        res += query(lt, l, r);
    if (r > mid)
        res += query(rt, l, r);
    return res % mod;
}

int main()
{
    scanf("%d%lld", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--)
    {
        int opt, l, r;
        ll x;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
        {
            scanf("%lld", &x);
            update_mul(1, l, r, x);
        }
        else if (opt == 2)
        {
            scanf("%lld", &x);
            update_add(1, l, r, x);
        }
        else
            printf("%lld\n", query(1, l, r));
    }
    return 0;
}