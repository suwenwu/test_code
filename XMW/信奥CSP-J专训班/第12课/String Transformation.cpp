/*
 *  @date: 2026-05-21 13:09:00  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: String Transformation.cpp
 */
#include <bits/stdc++.h>

using namespace std;

string s, t;
int a[30], b[30];

int main()
{
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++)
        a[s[i] - 'a']++;
    for (int i = 0; i < t.size(); i++)
        b[t[i] - 'a']++;
    for (int i = 0; i < 26; i++)
    {
        if (a[i])
            for (int j = 0; j < 26; j++)
            {
                if (a[i] == b[j])
                {
                    a[i] = b[j] = 0;
                    break;
                }
            }
    }
    for (int i = 0; i < 26; i++)
        if (a[i])
        {
            cout << "No\n";
            return 0;
        }
    cout << "Yes\n";
    return 0;
}