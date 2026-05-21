/*
 *  @date: 2026-05-14 17:10:50  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

string s;
string s1, s2;

int main()
{
    cin >> s;
    if (s[0] == '-')
    {
        cout << "-";
        s.erase(0, 1);
    }
    reverse(s.begin(), s.end());
    int st = 0, ed = s.size() - 1;
    for (int i = 1;; i++)
    {
        if (s[st] == '0' && s[st + 1] != '.')
            st++;
        else
            break;
    }
    for (int i = ed; s[ed] != '.'; i++)
    {
        if (s[ed] == '0')
            ed--;
        else
            break;
    }
    if (s[ed] == '.')
        ed--;
    for (int i = st; i <= ed; i++)
        cout << s[i];
    return 0;
}