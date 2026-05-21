/*
 *  @date: 2026-04-12 18:45:29  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 超市.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct node
{
    int p, d;
} a[N];
bool cmp(node x, node y)
{
    return x.d < y.d;
}

int n;
ll ans;
priority_queue<int, vector<int>, greater<int>> q; // 小根堆

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].p, &a[i].d);
    sort(a + 1, a + n + 1, cmp);

    for (int i = 1; i <= n; i++)
    {
        if (a[i].d == q.size())
        {
            if (a[i].p > q.top())
            {
                q.pop();
                q.push(a[i].p);
            }
        }
        else
            q.push(a[i].p);
    }
    while (!q.empty())
    {
        ans += q.top();
        q.pop();
    }
    printf("%lld\n", ans);
    return 0;
}