/*
 *  @date: 2026-05-15 15:34:31  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 线段树(二).cpp
 */
#include <bits/stdc++.h>
#define N 500005
#define ll long long

using namespace std;
struct node
{
    int l, r;
    ll sum, add_lazy, mul_lazy; // sum:区间和,add_lazy:区间加法懒标记,mul_lazy:区间乘法懒标记
} tree[N << 2];
int n, m, mod, a[N];

void build(int pos, int l, int r)
{
    tree[pos].l = l;
    tree[pos].r = r;
    tree[pos].mul_lazy = 1;

    if (l == r)
    {
        tree[pos].sum = a[l] % mod;
        return;
    }

    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
    tree[pos].sum = (tree[pos << 1].sum + tree[pos << 1 | 1].sum) % mod;
    return;
}

void push_down(int pos)
{
    tree[pos << 1].sum = (tree[pos << 1].sum * tree[pos].mul_lazy + tree[pos].add_lazy * (tree[pos << 1].r - tree[pos << 1].l + 1)) % mod;
    tree[pos << 1 | 1].sum = (tree[pos << 1 | 1].sum * tree[pos].mul_lazy + tree[pos].add_lazy * (tree[pos << 1 | 1].r - tree[pos << 1 | 1].l + 1)) % mod;

    tree[pos << 1].mul_lazy = (tree[pos << 1].mul_lazy * tree[pos].mul_lazy) % mod;
    tree[pos << 1 | 1].mul_lazy = (tree[pos << 1 | 1].mul_lazy * tree[pos].mul_lazy) % mod;

    tree[pos << 1].add_lazy = (tree[pos << 1].add_lazy * tree[pos].mul_lazy + tree[pos].add_lazy) % mod;
    tree[pos << 1 | 1].add_lazy = (tree[pos << 1 | 1].add_lazy * tree[pos].mul_lazy + tree[pos].add_lazy) % mod;

    tree[pos].add_lazy = 0;
    tree[pos].mul_lazy = 1;
    return;
}

void update_mul(int pos, int x, int y, int k) // 区间乘法
{
    if (x <= tree[pos].l && tree[pos].r <= y)
    {
        tree[pos].add_lazy = (tree[pos].add_lazy * k) % mod;
        tree[pos].mul_lazy = (tree[pos].mul_lazy * k) % mod;
        tree[pos].sum = (tree[pos].sum * k) % mod;
        return;
    }

    push_down(pos);
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (x <= mid)
        update_mul(pos << 1, x, y, k);
    if (y > mid)
        update_mul(pos << 1 | 1, x, y, k);
    tree[pos].sum = (tree[pos << 1].sum + tree[pos << 1 | 1].sum) % mod; // 更新当前节点的区间和
    return;
}

void update_add(int pos, int x, int y, int k)
{
    if (x <= tree[pos].l && tree[pos].r <= y)
    {
        tree[pos].add_lazy = (tree[pos].add_lazy + k) % mod;
        tree[pos].sum = (tree[pos].sum + k * (tree[pos].r - tree[pos].l + 1)) % mod;
        return;
    }

    push_down(pos);
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (x <= mid)
        update_add(pos << 1, x, y, k);
    if (y > mid)
        update_add(pos << 1 | 1, x, y, k);
    tree[pos].sum = (tree[pos << 1].sum + tree[pos << 1 | 1].sum) % mod; // 更新当前节点的区间和
    return;
}

ll query(int pos, int x, int y)
{
    if (x <= tree[pos].l && tree[pos].r <= y)
    {
        return tree[pos].sum;
    }

    push_down(pos);
    ll val = 0;
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (x <= mid)
        val = (val + query(pos << 1, x, y)) % mod;
    if (y > mid)
        val = (val + query(pos << 1 | 1, x, y)) % mod;
    return val;
}

int main()
{
    scanf("%d%d%d", &n, &m, &mod);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
        {
            int k;
            scanf("%d", &k);
            update_mul(1, x, y, k);
        }
        if (opt == 2)
        {
            int k;
            scanf("%d", &k);
            update_add(1, x, y, k);
        }
        if (opt == 3)
        {
            printf("%lld\n", (query(1, x, y) % mod + mod) % mod);
        }
    }
    return 0;
}