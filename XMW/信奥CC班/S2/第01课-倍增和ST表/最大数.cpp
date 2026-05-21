/*
 *  @date: 2026-04-29 11:00:18  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最大数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

ll a[N], st[N][21], t, d, x;
int n, m;
char c;

void change(int n)
{
    st[n][0] = a[n];
    for (int i = 1; n - (1 << i) >= 0; i++)
        st[n][i] = max(st[n][i - 1], st[n - (1 << i - 1)][i - 1]);
}

ll find(int l, int r)
{
    int k = log2(r - l + 1);
    return max(st[r][k], st[l + (1 << k) - 1][k]);
}

int main()
{
    scanf("%d%lld", &m, &d);
    for (int i = 1; i <= m; i++)
    {
        scanf(" %c%lld", &c, &x);
        if (c == 'A')
        {
            a[++n] = (x + t) % d;
            change(n);
        }
        else
        {
            if (x == 1)
                printf("%lld\n", t = a[n]);
            else
            {
                ll ans = find(n - x + 1, n);
                printf("%lld\n", t = ans);
            }
        }
    }
    return 0;
}