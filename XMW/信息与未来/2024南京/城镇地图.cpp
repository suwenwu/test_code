#include <bits/stdc++.h>
using namespace std;
int n, m, X, Y;
char f(int i, int j)
{
    int dx = i - X;
    int dy = j - Y;
    if (dx == 0 && dy == 0)
        return '+';
    if (dx == 0)
        return '-';
    if (dy == 0)
        return '|';
    if (dx == dy)
        return '\\';
    if (dx == -dy)
        return '/';
    // 上
    if (dx < 0 && dy > 0)
    {
        if (dx < -dy)
            return 'A';
        else
            return 'B';
    }
    // 右下
    if (dx > 0 && dy > 0)
    {
        if (dx > dy)
            return 'D';
        else
            return 'C';
    }
    // 左下
    if (dx > 0 && dy < 0)
    {
        if (dx > -dy)
            return 'E';
        else
            return 'F';
    }
    // 左上
    if (dx < 0 && dy < 0)
    {
        if (dx < dy)
            return 'H';
        else
            return 'G';
    }
    return '?';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> X >> Y;
    int Q;
    cin >> Q;
    while (Q--)
    {
        int x, y;
        cin >> x >> y;
        for (int i = x - 2; i <= x + 2; i++)
        {
            for (int j = y - 2; j <= y + 2; j++)
            {
                if (i < 1 || i > n || j < 1 || j > m)
                {
                    cout << '#';
                }
                else
                {
                    cout << f(i, j);
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}