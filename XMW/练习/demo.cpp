#include <bits/stdc++.h>
using namespace std;
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
    return 0;
}