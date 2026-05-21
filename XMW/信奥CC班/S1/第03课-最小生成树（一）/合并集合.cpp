/*
 *  @date: 2026-03-18 10:51:08  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, m, x, y;
int fa[N];
char c;

void init()
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
}

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
        fa[fx] = fy;
}

int main()
{
    scanf("%d%d", &n, &m);
    init();
    while (m--)
    {
        scanf(" %c%d%d", &c, &x, &y);
        if (c == 'Q')
        {
            if (find(x) == find(y))
                printf("Yes\n");
            else
                printf("No\n");
        }
        else
            merge(x, y);
    }
    return 0;
}