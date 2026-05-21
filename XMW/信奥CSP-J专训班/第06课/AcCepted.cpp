/*
 *  @date: 2026-04-10 13:22:33  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: AcCepted.cpp
 */
#include <bits/stdc++.h>
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

string s;
int len, cnt;

int main()
{
    cin >> s;
    int len = s.size();
    if (s[0] != 'A')
    {
        cout << "WA\n";
        return 0;
    }
    for (int i = 1; i < len; i++)
    {
        if (s[i] == 'C' && i >= 2 && i < len - 1)
            cnt++;
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            cout << "WA\n";
            return 0;
        }
    }
    if (cnt == 1)
        cout << "AC\n";
    else
        cout << "WA\n";
    return 0;
}