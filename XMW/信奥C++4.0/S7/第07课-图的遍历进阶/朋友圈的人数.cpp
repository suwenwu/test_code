#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 9;
vector<int> ve[maxn];
bool vis[maxn];
int num;
void dfs(int x)
{
    vis[x] = 1;
    num++;
    for (int i = 0; i < ve[x].size(); i++)
    {
        int y = ve[x][i];
        if (vis[y])
            continue;
        dfs(y);
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            num = 0;
            dfs(i);
            ans.push_back(num);
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}