#include <bits/stdc++.h>
#define maxn 10005
using namespace std;

int fa[maxn], n, m;
int get(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y)
{
    if (get(x) != get(y))
        fa[get(x)] = get(y);
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            fa[i] = i;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            merge(x, y);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (fa[i] == i)
                ans++;
        printf("%d\n", ans - 1);
    }
    return 0;
}