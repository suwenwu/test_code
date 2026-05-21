/*
 *  @date: 2026-04-12 19:48:28  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 动态最大值.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, opt, x;
priority_queue<int> q;
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d", &x);
            q.push(x);
            printf("%d\n", q.top());
        }
        else
        {
            if (q.empty())
                printf("impossible\n");
            else
            {
                q.pop();
                if (q.empty())
                    printf("impossible\n");
                else
                    printf("%d\n", q.top());
            }
        }
    }
    return 0;
}