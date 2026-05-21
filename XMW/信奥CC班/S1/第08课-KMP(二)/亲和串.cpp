/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-03-13 16:36:56  星期五
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

string s, t;

int main()
{
    cin >> s >> t;
    if (s.size() < t.size())
    {
        cout << "no";
        return 0;
    }
    s += s;
    if (s.find(t) != string::npos)
        cout << "yes";
    else
        cout << "no";
    return 0;
}