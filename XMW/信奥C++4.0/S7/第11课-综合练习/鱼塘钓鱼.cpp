/*
 *  @date: 2026-05-24 15:55:02  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 鱼塘钓鱼.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1005
#define ll long long

using namespace std;

int n, T;
int a[N], b[N], t[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 2; i <= n; i++)
        cin >> t[i];
    cin >> T;
    int ans = 0, sum = 0;                             // ans:最终答案 sum：堆中元素和
    priority_queue<int, vector<int>, greater<int>> q; // 动态维护前k大
    for (int i = 1; i <= n; i++)
    {              // 枚举在 i 池塘结束
        T -= t[i]; // 可以钓鱼的时间
        if (T < 0)
            break;
        while (q.size() > T)
        { // 钓鱼的时间变少，自然堆中元素个数也要相应减少
            sum -= q.top();
            q.pop();
        }
        for (int j = 0;; j++)
        {
            if (a[i] - b[i] * j < 0)
                break;
            if (q.size() < T)
            {
                q.push(a[i] - b[i] * j);
                sum += a[i] - b[i] * j;
            }
            else if (a[i] - b[i] * j > q.top())
            {
                sum -= q.top();
                q.pop();
                q.push(a[i] - b[i] * j);
                sum += a[i] - b[i] * j;
            }
            ans = max(ans, sum);
        }
    }
    cout << ans;
    return 0;
}