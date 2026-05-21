#include <bits/stdc++.h>
#define maxn 200005
using namespace std;

struct Edge
{
    int u, v, w;
} e[maxn];
int fa[5009], n, m;

// 并查集
int get(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y)
{
    fa[get(x)] = get(y);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m + 1, [](const Edge &a, const Edge &b)
         { return a.w < b.w; });
    int ans = 0, edge = 0; // ans为最小生成树的权值和，edge为已选边数
    for (int i = 1; i <= m; i++)
    {
        if (get(e[i].u) == get(e[i].v))
            continue;
        merge(e[i].u, e[i].v);
        edge++;
        ans += e[i].w;
    }
    printf("%s", edge == n - 1 ? to_string(ans).c_str() : "orz");
    return 0;
}