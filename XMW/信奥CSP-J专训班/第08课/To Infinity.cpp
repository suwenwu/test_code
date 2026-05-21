/*
 *  @date: 2026-04-26 09:46:22  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: To Infinity.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

string s;
long long k;

int main()
{
    cin >> s >> k;
    for (int i = 0; i < k && i < s.size(); i++)
    {
        if (s[i] != '1')
        {
            cout << s[i] << endl;
            return 0;
        }
    }
    cout << 1 << endl;
    return 0;
}