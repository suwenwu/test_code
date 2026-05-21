// LUOGU_RID: 166648750
/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2024-06-29 13:42:47  星期六
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2024 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

long long n, m, x, sum, ans;
map<long long, int> mp;

int main()
{
    cin >> n >> m;
    mp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        sum = (sum + x) % m;
        ans += mp[sum];
        mp[sum]++;
    }
    cout << ans;
    return 0;
}