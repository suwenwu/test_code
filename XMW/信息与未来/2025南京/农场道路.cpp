#include <iostream>
#include <queue>
using namespace std;

typedef long long ll; // 适配n≤1e9的范围

int main()
{
    ll n, k;
    cin >> n >> k;

    queue<ll> q;
    q.push(n);
    ll ans = 0; // 最终群数

    while (!q.empty())
    {
        ll x = q.front();
        q.pop();

        // 判断是否能分裂
        if (x > k && (x + k) % 2 == 0)
        {
            ll a = (x + k) / 2;
            ll b = (x - k) / 2;
            q.push(a);
            q.push(b);
        }
        else
        {
            ans++; // 不能分裂，群数+1
        }
    }

    cout << ans << endl;
    return 0;
}