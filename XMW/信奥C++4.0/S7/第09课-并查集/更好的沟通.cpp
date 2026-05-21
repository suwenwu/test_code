#include <bits/stdc++.h>
#define maxn 100005
using namespace std;

int fa[maxn];
int n, m, x, k;
int get(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y)
{
    if (get(x) != get(y)) // 第i个结点（猫）连上第x+n的结点（语言）
        fa[get(x)] = get(y);
}
int main()
{
    // 图中的结点数是语言的数量+猫的数量 =1e5
    // 语言的下标改为   n+1 ~ n+m
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + m; i++)
        fa[i] = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        while (k--)
        {
            scanf("%d", &x);
            merge(x + n, i);
        }
    }
    int num = 0;
    for (int i = 1; i <= n; i++)
        if (fa[i] == i)
            num++;
    printf("%d\n", num - 1);
    return 0;
}