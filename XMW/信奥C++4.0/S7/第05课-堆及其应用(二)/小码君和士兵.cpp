/*
 *  @date: 2026-04-18 18:15:49  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 小码君和士兵.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct node
{
    int v, s;
} a[N];
bool cmp(node A, node B)
{
    return A.s > B.s;
}
priority_queue<int, vector<int>, greater<int>> q;
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].v, &a[i].s);
    sort(a + 1, a + 1 + n, cmp);
    long long sum = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (q.size() >= a[i].s)
        {
            sum -= q.top();
            q.pop();
        }
        q.push(a[i].v);
        sum += a[i].v;
        ans = max(ans, sum);
    }
    printf("%lld\n", ans);
    return 0;
}