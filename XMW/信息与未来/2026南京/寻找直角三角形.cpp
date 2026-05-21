#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n;
unordered_map<int, ll> cx, cy;
pair<int, int> pts[100005];

int main()
{

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pts[i].first, &pts[i].second);
        cx[pts[i].first]++;
        cy[pts[i].second]++;
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        pair<int, int> p = pts[i];
        ans += (cx[p.first] - 1) * (cy[p.second] - 1);
    }

    printf("%lld\n", ans);
    return 0;
}