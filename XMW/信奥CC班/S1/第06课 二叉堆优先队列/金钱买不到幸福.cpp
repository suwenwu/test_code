/*
 *  @date: 2026-04-02 10:13:21  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 金钱买不到幸福.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int t, m, x, c;

void solve()
{
    priority_queue<int> q; // 优先队列
    int sum = 0;
    scanf("%d%d", &m, &x);
    while (m--)
    {
        scanf("%d", &c);
        q.push(c);
        sum -= c;
        if (sum < 0)
        {
            sum += q.top();
            q.pop();
        }
        sum += x;
    }
    printf("%d\n", int(q.size()));
}

int main()
{
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}