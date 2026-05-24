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
<<<<<<< HEAD

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
=======
int a[5009][5009], d[5009], vis[5009];
int n, m;
bool prim()
{
    memset(d, 0x3f, sizeof(d));
    memset(vis, 0, sizeof(vis));
    d[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = 0;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && d[j] < d[x])
            {
                x = j;
            }
            if (x == 0)
            {
                return false;
            }
            vis[x] = true;
            for (int y = 1; y <= n; y++)
            {
                if (!vis[y])
                {
                    d[y] = min(d[y], a[x][y]);
                }
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    memset(a, 0x3f, sizeof(a));
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        a[x][y] = a[y][x] = min(a[x][y], z);
    }
    if (prim())
    {
        int ans = 0;
        for (int i = 2; i <= n; i++)
        {
            ans += d[i];
        }
        printf("%d", ans);
    }
    else
    {
        printf("orz");
    }
>>>>>>> 48856ca8526da55bddbf49cf77ef635c688ea545
    return 0;
}