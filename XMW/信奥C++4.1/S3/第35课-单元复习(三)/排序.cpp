#include <bits/stdc++.h>
using namespace std;

int a[1000005];
bool cmp(int x, int y)
{
    return x > y;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int s;
    cin >> s;
    if (s == 0)
        sort(a + 1, a + n + 1);
    else
        sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}