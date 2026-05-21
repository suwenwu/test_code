/*
 *  @date: 2026-05-21 16:20:46  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 数学计算.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

ll tree[N << 2];
int q, mod;

void build(int k, int l, int r)
{
    if (l == r)
    {
        tree[k] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree[k] = (tree[k << 1] * tree[k << 1 | 1]) % mod;
}

void update(int k, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[k] = val % mod;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(k << 1, l, mid, pos, val);
    else
        update(k << 1 | 1, mid + 1, r, pos, val);
    tree[k] = (tree[k << 1] * tree[k << 1 | 1]) % mod;
}

void solve()
{
    scanf("%d%d", &q, &mod);
    build(1, 1, q);
    for (int i = 1; i <= q; i++)
    {
        int opt, val;
        scanf("%d%d", &opt, &val);
        if (opt == 1)
            update(1, 1, q, i, val);
        else
            update(1, 1, q, val, 1);
        printf("%d\n", tree[1]);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}