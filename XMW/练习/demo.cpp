/*
 *  @date: 2026-05-24 13:42:07  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int n, m, cnt, mp[N][N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mp[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            bool flag = true; // 假设这个点是山谷
            for (int k = 0; k < 8; k++)
            {
                int x = i + dir[k][0], y = j + dir[k][1];
                if (x < 1 || x > n || y < 1 || y > m)
                    continue;
                if (mp[i][j] > mp[x][y])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}