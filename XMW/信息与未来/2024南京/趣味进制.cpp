#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    int ans = 0;
    for (int k = 1; k <= 30; k++)
    {
        long long ones = (1LL << k) - 1; // k个1
        for (int t = 1; t <= 30; t++)
        {
            long long x = ones << t; // 左移t位
            if (x > n)
                break;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}