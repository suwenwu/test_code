#include <bits/stdc++.h>
#define maxn 1005
using namespace std;

int fa[maxn];
int n, m, p, q;
char opt;
vector<int> ve[maxn];
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    while (m--)
    {
        scanf(" %c%d%d", &opt, &p, &q);
        if (opt == 'E')
        {
            ve[p].push_back(q);
            ve[q].push_back(p);
        }
        else
            merge(p, q);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < ve[i].size(); j++)
        {
            if (get(ve[i][j]) != get(ve[i][j - 1]))
                merge(ve[i][j], ve[i][j - 1]);
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (fa[i] == i)
            ans++;
    printf("%d", ans);
    return 0;
}