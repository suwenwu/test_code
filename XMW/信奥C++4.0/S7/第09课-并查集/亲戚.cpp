#include <bits/stdc++.h>
#define maxn 5005
using namespace std;

int fa[maxn];
int n, m, p;
int get(int x)
{
    if (fa[x] == x)
        return x;
    return get(fa[x]);
}
void merge(int x, int y)
{
    if (get(x) != get(y))
        fa[get(x)] = get(y);
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (get(u) != get(v))
            merge(u, v);
    }
    while (p--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (get(x) == get(y))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}