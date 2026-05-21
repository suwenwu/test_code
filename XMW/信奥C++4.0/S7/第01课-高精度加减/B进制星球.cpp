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

int n; // n进制
string s1, s2;
int a[N], b[N], c[N];

string add(string s1, string s2)
{
    memset(c, 0, sizeof(c));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    int len1 = s1.size(), len2 = s2.size();
    for (int i = 1; i <= len1; i++)
    {
        if (s1[len1 - i] >= '0' && s1[len1 - i] <= '9')
            a[i] = s1[len1 - i] - '0';
        else
            a[i] = s1[len1 - i] - 'A' + 10;
    }
    for (int i = 1; i <= len2; i++)
    {
        if (s2[len2 - i] >= '0' && s2[len2 - i] <= '9')
            b[i] = s2[len2 - i] - '0';
        else
            b[i] = s2[len2 - i] - 'A' + 10;
    }
    int len = max(len1, len2);
    for (int i = 1; i <= len; i++)
    {
        c[i] += a[i] + b[i];
        c[i + 1] += c[i] / n;
        c[i] %= n;
    }
    if (c[len + 1] != 0)
        len++;
    string ans = "";
    for (int i = len; i >= 1; i--)
    {
        if (c[i] >= 0 && c[i] <= 9)
            ans += c[i] + '0';
        else
            ans += c[i] - 10 + 'A';
    }
    return ans;
}

int n;

int main()
{
    scanf("%d", &n);
    cin >> s1 >> s2;
    cout << add(s1, s2) << endl;
    return 0;
}