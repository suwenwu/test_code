/*
 *  @date: 2026-05-24 15:13:47  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最小函数值.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m;
priority_queue<int> q; // 优先队列，默认大顶堆
vector<int> ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        for (int j = 1; j <= m; j++)
        {
            int y = a * j * j + b * j + c;
            if (q.size() < m)
                q.push(y);
            else if (q.top() > y)
            {
                q.pop();
                q.push(y);
            }
            else
                break;
        }
    }
    while (!q.empty())
    {
        ans.push_back(q.top());
        q.pop();
    }
    for (int i = ans.size() - 1; i >= 0; i--)
        printf("%d ", ans[i]);
    return 0;
}