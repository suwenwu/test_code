#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define N 200005
using namespace std;

int n, a[N], x;
long long ans;

int main()
{
    // debug;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        a[i] = x - i;
    }
    sort(a + 1, a + 1 + n);
    int b = a[(n + 1) / 2];
    for (int i = 1; i <= n; i++)
        ans += abs(a[i] - b);
    cout << ans;
    return 0;
}