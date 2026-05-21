/*
ans = max(a,b,c,d) - min(a,b,c,d)
假设当前分割点i,j,k
ans = max(a[1-i],a[i+1,j],a[j+1,k],a[k+1,n]) - min(a[1-i],a[i+1,j],a[j+1,k],a[k+1,n])
用前缀和优化为s[]
ans= max(s[i],s[j]-s[i],s[k]-s[j],s[n]-s[k]) - max(s[i],s[j]-s[i],s[k]-s[j],s[n]-s[k])
for(int i=1;i<=n-2;i++)
    for(int j=i+1;j<=n-1;j++)
        for(int k=j+1;k<=n;k++)


s[j]-2*s[i]> s[j] - 2*s[i+1]
*/
#include <bits/stdc++.h>

using namespace std;

int n;
long long ans = LLONG_MAX, a[200005];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }

    for (int j = 2, i = 1, k = 3; j <= n - 1; j++)
    {
        while (i + 1 < j && abs(a[j] - 2 * a[i]) > abs(a[j] - 2 * a[i + 1]))
            i++;
        while (k + 1 < n && abs(a[n] - 2 * a[k] + a[j]) > abs(a[n] - 2 * a[k + 1] + a[j]))
            k++;
        ans = min(ans, max({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]}) - min({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]}));
    }
    cout << ans;
    return 0;
}