#include <bits/stdc++.h>
#define maxn 200005
using namespace std;

struct node
{
    int x, y, z;
    friend bool operator<(const node &a, const node &b)
    {
        return a.z < b.z;
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
    for (int i = 0; i < m; i++)
    {
        int ok;
        scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].z, &ok);
        if (ok)
            a[i].z = 0;
    }
    sort(a, a + m);
    int ans = 0, edge = 0;
    for (int i = 0; i < m; i++)
    {
        if (get(a[i].x) == get(a[i].y))
            continue;
        merge(a[i].x, a[i].y);
        edge++;
        ans += a[i].z;
    }
    if (edge == n - 1)
        printf("%d", ans);
    else
        printf("orz");
    return 0;
}