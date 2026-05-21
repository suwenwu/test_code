/*
 *  @date: 2026-05-21 10:43:34  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

char mp[N][N];
int n, m, ans;
bool vis[N][N];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct node
{
    int x, y, step;
};

int bfs(int sx, int sy, int ex, int ey)
{
    memset(vis, false, sizeof(vis));
    queue<node> q;
    q.push({sx, sy, 0});
    vis[sx][sy] = true;
    while (!q.empty())
    {
        auto [x, y, step] = q.front();
        q.pop();
        if (x == ex && y == ey)
            return step;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && mp[nx][ny] != '#' && !vis[nx][ny])
            {
                vis[nx][ny] = true;
                q.push({nx, ny, step + 1});
            }
        }
    }
    return -1;
}

int sx, sy, tx1, ty1, tx2, ty2;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf(" %c", &mp[i][j]);
            if (mp[i][j] == 'S')
                sx = i, sy = j;
            if (mp[i][j] == 'T')
                tx1 = tx2, ty1 = ty2, tx2 = i, ty2 = j;
        }
    }
    int step1 = bfs(sx, sy, tx1, ty1);
    int step2 = bfs(sx, sy, tx2, ty2);
    int step3 = bfs(tx1, ty1, tx2, ty2);
    if (step1 != -1 && step2 != -1 && step3 != -1)
        printf("%d", step1 + step2 + step3);
    else
        printf("-1");
    return 0;
}