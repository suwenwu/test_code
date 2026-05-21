/*
 *  @date: 2026-04-02 10:20:59  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 黑匣子.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, m;
int a[N], u[N];
priority_queue<int> q;                             // 大根堆存小数
priority_queue<int, vector<int>, greater<int>> q1; // 小根堆存大数

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &u[i]);

    int k = 1;
    for (int i = 1, j = 1; i <= n; i++)
    {
        if (q.size() && a[i] > q.top())
            q1.push(a[i]);
        else
            q.push(a[i]);

        while (j <= m && u[j] == i)
        {
            while (q.size() > k)
            {
                q1.push(q.top());
                q.pop();
            }
            while (q.size() < k)
            {
                q.push(q1.top());
                q1.pop();
            }
            printf("%d\n", q.top());
            j++, k++;
        }
    }
    return 0;
}