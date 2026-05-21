/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2025-10-22 14:22:13  星期三
 *  @compiler: 2025 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define N 2005
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, m, sx, sy, x, y;
bool vis[N][N];
char mp[N][N];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int lnum[N][N], rnum[N][N]; // 向左向右移动次数
struct node
{
    int x, y, l, r;
}; // l向左移动次数 r向右移动次数
queue<node> q;

int bfs()
{
    memset(lnum, 0x3f, sizeof(lnum));
    memset(rnum, 0x3f, sizeof(rnum));
    lnum[sx][sy] = rnum[sx][sy] = 0;
    int cnt = 0;
    q.push({sx, sy, 0, 0});
    while (!q.empty())
    {
        node t = q.front();
        q.pop();
        if (vis[t.x][t.y])
            continue;
        vis[t.x][t.y] = true;
        cnt++;
        for (int i = 0; i < 4; i++)
        {
            int nx = t.x + dir[i][0], ny = t.y + dir[i][1];
            int ll = t.l + (i == 1), rr = t.r + (i == 0);
            if (nx < 1 || nx > n || ny < 1 || ny > m || mp[nx][ny] == '*' || ll > x || rr > y)
                continue;
            if (lnum[nx][ny] > ll || rnum[nx][ny] > rr)
            {
                lnum[nx][ny] = ll;
                rnum[nx][ny] = rr;
                q.push({nx, ny, ll, rr});
            }
        }
    }
    return cnt;
}

int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &x, &y);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    printf("%d\n", bfs());
    return 0;
}