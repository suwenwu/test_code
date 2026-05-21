/*
 *  @date: 2026-04-09 11:06:13  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 电路维修.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 505
#define ll long long

using namespace std;

deque<pair<int, int>> q; // pair<x, y>
int n, m, dis[N][N], t;
char g[N][N];

bool check(int x, int y)
{
    return x >= 0 && x <= n && y >= 0 && y <= m; // 判断是否越界
}

void push(int x, int y, int d) // 双向队列
{
    if (dis[x][y] == -1 || d < dis[x][y])
    {
        dis[x][y] = d;
        if (q.empty() || d > dis[q.front().first][q.front().second]) // 如果队列为空或者d大于队首元素，则将(x,y)入队
            q.push_back({x, y});
        else
            q.push_front({x, y}); // 否则将(x,y)入队
    }
}

void bfs()
{
    memset(dis, -1, sizeof(dis)); // 初始化距离数组
    dis[0][0] = 0;                // 起点距离为0
    q.push_back({0, 0});          // 起点入队
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop_front();
        if (check(x - 1, y - 1))
        {
            if (g[x - 1][y - 1] == '\\')
                push(x - 1, y - 1, dis[x][y]); // 如果是'\'，则将(x-1,y-1)入队
            else
                push(x - 1, y - 1, dis[x][y] + 1); // 否则将(x-1,y-1)入队，并将d+1
        }
        if (check(x - 1, y + 1))
        {
            if (g[x - 1][y] == '/')
                push(x - 1, y + 1, dis[x][y]);
            else
                push(x - 1, y + 1, dis[x][y] + 1);
        }
        if (check(x + 1, y - 1))
        {
            if (g[x][y - 1] == '/')
                push(x + 1, y - 1, dis[x][y]);
            else
                push(x + 1, y - 1, dis[x][y] + 1);
        }
        if (check(x + 1, y + 1))
        {
            if (g[x][y] == '\\')
                push(x + 1, y + 1, dis[x][y]);
            else
                push(x + 1, y + 1, dis[x][y] + 1);
        }
    }
    printf("%d\n", dis[n][m]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", g[i]);
    /*
    结论：沿对角线走的时候，坐标的和/差是不变的
    这里我们延伸一下：沿对角线走的时候，坐标之和的奇偶性是不变的
    知道了这个结论，那就很好办了，由于这里是固定从（0，0）出发，横纵坐标和是偶数，所以只要终点的横纵坐标和是奇数，那必定 NO SOLUTION.
    */
    if ((n + m) % 2)
    {
        printf("NO SOLUTION\n");
        return 0;
    }
    bfs();
    return 0;
}