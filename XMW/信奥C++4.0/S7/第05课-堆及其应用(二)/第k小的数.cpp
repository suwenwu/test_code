/*
 *  @date: 2026-04-18 18:13:39  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 第k小的数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m, k, a, opt;
priority_queue<int> q;

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        if (q.size() < k)
            q.push(a);
        else
        {
            if (q.top() > a)
            {
                q.pop();
                q.push(a);
            }
        }
    }
    while (m--)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d", &a);
            if (q.size() < k)
                q.push(a);
            else
            {
                if (q.top() > a)
                {
                    q.pop();
                    q.push(a);
                }
            }
        }
        else
        {
            if (q.size() >= k)
                printf("%d\n", q.top());
            else
                printf("-1\n");
        }
    }
    return 0;
}