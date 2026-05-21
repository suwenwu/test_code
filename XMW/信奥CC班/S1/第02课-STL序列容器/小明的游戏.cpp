/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2025-10-22 11:18:09  星期三
 *  @compiler: 2025 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define N 505
#define ll long long
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, m, sx, sy, ex, ey, g[N][N];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dis[N][N];
bool vis[N][N];
char c;

int bfs()
{
    deque<pair<int, int>> q;
    q.push_back({sx, sy});
    dis[sx][sy] = 0;

    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop_front();
        if (x == ex && y == ey)
            return dis[x][y];
        if (vis[x][y])
            continue;
        vis[x][y] = true;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dir[i][0], yy = y + dir[i][1];
            int w = (g[xx][yy] != g[x][y]);
            if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && dis[xx][yy] > dis[x][y] + w)
            {
                dis[xx][yy] = dis[x][y] + w;
                if (!w)
                    q.push_front({xx, yy});
                else
                    q.push_back({xx, yy});
            }
        }
    }
    return 0;
}

int main()
{
    while (scanf("%d%d", &n, &m) && n + m)
    {
        memset(g, 0, sizeof(g));
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> c;
                if (c == '#')
                    g[i][j] = 1;
                else
                    g[i][j] = 0;
            }
        scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
        sx++, sy++, ex++, ey++;
        printf("%d\n", bfs());
    }
    return 0;
}