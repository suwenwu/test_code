/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-01-09 09:28:04  星期五
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

unordered_map<string, int> mp;
int n, m;
string s;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        mp[s] = 1;
    }
    cin >> m;
    while (m--)
    {
        cin >> s;
        if (mp[s] == 1)
        {
            cout << "OK\n";
            mp[s]++;
        }
        else if (mp[s] > 1)
            cout << "REPEAT\n";
        else
            cout << "WRONG\n";
    }
    return 0;
}