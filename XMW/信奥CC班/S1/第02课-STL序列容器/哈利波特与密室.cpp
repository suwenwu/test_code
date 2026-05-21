/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2025-10-22 14:52:35  星期三
 *  @compiler: 2025 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define N 2005
#define ll long long
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, m, cnt, dis[N];
vector<int> g[N];
char mp[N][N];
bool vis[N];
queue<int> q;

void bfs()
{
    q.push(1);
    dis[1] = 0;
    vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (!vis[v] && dis[v] > dis[u] + 1)
            {
                dis[v] = dis[u] + 1;
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '#')
                g[i].push_back(j + n), g[j + n].push_back(i); // 1-5. 5-1 1,1
    }
    memset(dis, 0x3f, sizeof(dis));
    bfs();
    if (dis[n] == dis[0])
        printf("-1\n");
    else
        printf("%d\n", dis[n]);
    return 0;
}
