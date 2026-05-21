/*
 *  @date: 2026-03-25 13:46:22  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 最小生成树.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, cnt;
vector<pair<int, int>> g[N];
bool vis[N];
int dis[N];
ll ans;

void prim()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.push({dis[1] = 0, 1});
    while (!q.empty())
    {
        auto [w, u] = q.top();
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        ans += w; // 累加边权
        cnt++;    // 顶点数量
        for (auto [v, w] : g[u])
        {
            if (dis[v] > w)
            {
                dis[v] = w;
                q.push({w, v});
            }
        }
    }
    if (cnt == n)
        printf("%lld\n", ans);
    else
        printf("orz\n");
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    prim();
    return 0;
}
/*
#include <bits/stdc++.h>

#define endl "\n"
#define N 200005
#define ll long long
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, m, head[N], cnt, dis[N];
ll ans, sum;
bool vis[N];
struct edge
{

    int to, nxt, w;
} e[N << 1];

void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

void prim()
{
    memset(dis, 0x3f, sizeof(dis));
    q.push({dis[1] = 0, 1});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        ans += dis[u];
        sum++; // 统计点数
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (!vis[v] && dis[v] > e[i].w)
            {
                dis[v] = e[i].w;
                q.push({dis[v], v});
            }
        }
    }
    if (sum != n)
        printf("orz\n");
    else
        printf("%lld\n", ans);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    prim();
    return 0;
}
*/