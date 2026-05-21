#include <bits/stdc++.h>
#define maxn 100005
using namespace std;

struct node
{
    int x, y, z;
    friend bool operator<(const node &a, const node &b)
    {
        return a.z < b.z;
    }
} a[maxn];
int fa[maxn], n, m, k;
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
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    sort(a, a + m);
    int ans = 0, edge = 0;
    for (int i = 0; i < m; i++)
    {
        if (get(a[i].x) == get(a[i].y))
            continue;
        merge(a[i].x, a[i].y);
        edge++;
        ans += a[i].z;
        if (edge == k)
            break;
    }
    printf("%d", ans);
    return 0;
}