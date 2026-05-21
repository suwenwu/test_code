#include <bits/stdc++.h>
#define maxn 200005
using namespace std;

int fa[maxn], n, m, u, v;
int get(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y)
{
    int fx = get(x), fy = get(y);
    if (fx != fy)
        fa[fx] = fy;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        merge(u, v);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (fa[i] == i)
            ans++;

    printf("%d\n", ans);
    return 0;
}