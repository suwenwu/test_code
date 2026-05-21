#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, m;
long long ans;

int main()
{
    // debug;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &m);
        while ((m & 1) != 1)
        {
            ans++;
            m >>= 1;
        }
    }
    printf("%lld", ans);
    return 0;
}