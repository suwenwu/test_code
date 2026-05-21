/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2025-11-13 11:53:57  星期四
 *  @compiler: 2025 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define N 200005
#define ll long long
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, r, q;
struct node
{
    int s, w, k; // s:初始分数 w：实力  k：编号
    friend bool operator<(node x, node y)
    {
        if (x.s == y.s)
            return x.k < y.k;
        return x.s > y.s;
    }
} a[N], w[N], l[N];

int main()
{
    scanf("%d%d%d", &n, &r, &q);
    for (int i = 1; i <= 2 * n; i++)
        scanf("%d", &a[i].s), a[i].k = i;
    for (int i = 1; i <= 2 * n; i++)
        scanf("%d", &a[i].w);
    sort(a + 1, a + 1 + 2 * n); // 按初始分数排序
    while (r--)
    {
        int lose = 0, win = 0;
        for (int i = 1; i <= 2 * n; i += 2)
        {
            if (a[i].w > a[i + 1].w)
                w[++win] = a[i], l[++lose] = a[i + 1], w[win].s++;
            else
                w[++win] = a[i + 1], l[++lose] = a[i], w[win].s++;
        }
        merge(w + 1, w + 1 + win, l + 1, l + 1 + lose, a + 1);
    }
    printf("%d", a[q].k);
    return 0;
}