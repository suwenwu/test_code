/*
 *  @date: 2026-03-25 14:45:26  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: A➗B Problem.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int a[N], c[N];

// 高精度除以低精度
string divide(string s1, ll b)
{
    int len = s1.size(); // 获取字符串长度
    memset(a, 0, sizeof(a));
    memset(c, 0, sizeof(c));
    for (int i = 0; i < len; i++)
        a[i] = s1[i] - '0';
    ll r = 0;
    for (int i = 0; i < len; i++)
    {
        r = a[i] + r * 10;
        c[i] = r / b;
        r %= b;
    }
    int len1 = 0;
    while (!c[len1] && len1 < len - 1)
        len1++;
    string ans = "";
    for (int i = len1; i < len; i++)
        ans += c[i] + '0';
    cout << ans << "\n"
         << r;
    return ans;
}

string s;
ll b;

int main()
{
    cin >> s >> b;
    divide(s, b);
    return 0;
}