#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define N 5009
using namespace std;

int a[N][N], d[N], vis[N];
int n, m;
bool prim()
{
    memset(d, 0x3f, sizeof(d));
    memset(vis, 0, sizeof(vis));
    d[1] = 0;
    for (int i = 1; i <= n; i++) // 每次向集合T中加入一个点
    {
        int x = 0;
        for (int j = 1; j <= n; j++) // 找到离T集合最近的点
            if (!vis[j] && d[j] < d[x])
                x = j;
        if (x == 0)
            return false;            // 没有找到点，说明其他点都与T集合不连通
        vis[x] = 1;                  // 标记，相当于把点x加入T集合
        for (int y = 1; y <= n; y++) // 去更新S集合的点到T集合的距离
            if (!vis[y])
                d[y] = min(d[y], a[x][y]);
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
        a[x][y] = min(a[x][y], z);
        a[y][x] = min(a[y][x], z);
    }
    if (prim())
    {
        int ans = 0;
        for (int i = 2; i <= n; i++)
            ans += d[i];
        printf("%d", ans);
    }
    else
        printf("orz");
    return 0;
}