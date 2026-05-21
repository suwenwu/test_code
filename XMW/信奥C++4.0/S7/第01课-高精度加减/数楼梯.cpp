/*
 *  @date: 2026-03-19 15:23:01  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 高精度加法.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

string s1, s2;
int a[N], b[N], c[N];

string add(string s1, string s2)
{
    memset(c, 0, sizeof(c));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    int len1 = s1.size(), len2 = s2.size();
    for (int i = 1; i <= len1; i++)
        a[i] = s1[len1 - i] - '0';
    for (int i = 1; i <= len2; i++)
        b[i] = s2[len2 - i] - '0';
    int len = max(len1, len2);
    for (int i = 1; i <= len; i++)
    {
        c[i] += a[i] + b[i];
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    if (c[len + 1] != 0)
        len++;
    string ans = "";
    for (int i = len; i >= 1; i--)
        ans += c[i] + '0';
    return ans;
}

int n;

int main()
{
    scanf("%d", &n);
    s1 = "1", s2 = "2";
    if (n == 1)
        cout << s1;
    else if (n == 2)
        cout << s2;
    else
    {
        string s;
        for (int i = 3; i <= n; i++)
        {
            s = add(s1, s2);
            s1 = s2;
            s2 = s;
        }
        cout << s;
    }
    return 0;
}