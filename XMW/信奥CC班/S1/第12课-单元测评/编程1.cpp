/*
 *  @date: 2026-04-09 15:56:14  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 编程1.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

priority_queue<int> q;
priority_queue<int, vector<int>, greater<int>> q1;
int n, x;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        q.push(x);
        q1.push(x);
    }
    while (q.size() != 1)
    {
        x = q.top();
        q.pop();
        x = x * q.top() + 1;
        q.pop();
        q.push(x);

        x = q1.top();
        q1.pop();
        x = x * q1.top() + 1;
        q1.pop();
        q1.push(x);
    }
    printf("%d\n", q1.top() - q.top());
    return 0;
}