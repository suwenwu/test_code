#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 9;
vector<int> ve[maxn];
int h[maxn], a[maxn], start;
bool vis[maxn];
int n, m;
bool check(int mid)
{
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(start);
    vis[start] = 1;
    while (q.size())
    {
        int r = q.front();
        q.pop();
        for (int i = 0; i < ve[r].size(); i++)
        {
            int y = ve[r][i];
            if (!vis[y] && abs(h[r] - h[y]) <= mid)
            {
                vis[y] = 1;
                q.push(y);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] && !vis[i])
            return false;
    }
    return true;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i])
            start = i;
    }
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    if (start == 0)
    {
        cout << 0;
        return 0;
    }
    int l = 0, r = 1e9, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans;
    return 0;
}