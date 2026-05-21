#include <bits/stdc++.h>
using namespace std;
int n, m, k;
char s[20][20];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
// 检查 (x, y) 周围是否只有⼀个 '.'，如果是则可以继续⾛
bool check(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        cnt += (s[x + dx[i]][y + dy[i]] == '.');
    }
    return cnt == 1;
}
void dfs(int x, int y, int cnt)
{
    s[x][y] = '.';
    if (x == n && y == m && cnt == k)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cout << s[i][j];
            }
            cout << "\n";
        }
        exit(0);
    }
    if (cnt < k)
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (s[nx][ny] == '#' && check(nx, ny))
            {
                dfs(nx, ny, cnt + 1);
            }
        }
    }
    s[x][y] = '#';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = '#';
    dfs(1, 1, 0);
    return 0;
}