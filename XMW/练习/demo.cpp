#include <bits/stdc++.h>
using namespace std;

// 这里的 Q 最大 10^5，线段树数组开 4 倍空间
const int MAXN = 100005;
long long tree[MAXN << 2];
int Q;
long long M;

// 向上更新：父节点等于左右子节点乘积取模
void push_up(int rt)
{
    tree[rt] = (tree[rt << 1] * tree[rt << 1 | 1]) % M;
}

// 建树：初始所有位置都是 1
void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    push_up(rt);
}

// 单点修改：将 pos 位置的值改为 val
void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt] = val % M;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(rt << 1, l, mid, pos, val);
    else
        update(rt << 1 | 1, mid + 1, r, pos, val);
    push_up(rt);
}

void solve()
{
    scanf("%d %lld", &Q, &M);
    build(1, 1, Q);

    for (int i = 1; i <= Q; i++)
    {
        int op;
        long long val;
        scanf("%d %lld", &op, &val);
        if (op == 1)
        {
            // 类型 1：在当前位置 i 乘上 val
            update(1, 1, Q, i, val);
        }
        else
        {
            // 类型 2：把第 val 次操作乘的数变回 1
            update(1, 1, Q, (int)val, 1);
        }
        // 每次操作后，根节点存的就是当前所有有效乘数的积
        printf("%lld\n", tree[1]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}