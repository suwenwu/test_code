/*
 *  @date: 2026-03-19 15:43:23  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 回文数.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

string add(string s1, string s2)
{
    int a[N] = {0}, b[N] = {0}, c[N] = {0};
    int lena = s1.size(), lenb = s2.size(); // 长度（位数）
    for (int i = 0; i < lena; i++)
        a[i] = s1[lena - i - 1] - '0';
    for (int i = 0; i < lenb; i++)
        b[i] = s2[lenb - i - 1] - '0';
    int lenc = max(lena, lenb);
    for (int i = 0; i < lenc; i++)
    {
        c[i] += a[i] + b[i];
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    if (c[lenc] > 0)
        lenc++;
    string s3 = "";
    for (int i = lenc - 1; i >= 0; i--)
        s3 += c[i] + '0';
    return s3;
}

string s1, s2;

int main()
{
    cin >> s1 >> s2;
    cout << add(s1, s2) << endl;
    return 0;
}