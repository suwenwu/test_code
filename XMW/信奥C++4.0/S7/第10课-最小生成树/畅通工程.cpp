#include <bits/stdc++.h>
#define maxn 200005
using namespace std;

struct node
{
    int u, v, w;
    friend bool operator<(const node &a, const node &b)
    {
        return a.w < b.w;
    }
} a[maxn];
int fa[5009], n, m;
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
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1);
    int ans = 0, edge = 0;
    for (int i = 1; i <= m; i++)
    {
        if (get(a[i].u) == get(a[i].v))
            continue;
        merge(a[i].u, a[i].v);
        edge++;
        ans += a[i].w;
    }
    if (edge == n - 1)
        printf("%d", ans);
    else
        printf("no");
    return 0;
}