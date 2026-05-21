/*
 *  @date: 2026-03-25 14:29:27  星期三
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 阶乘之和.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

string mul(string s1, int s2) // 高精度乘法
{
    int a[N] = {0};
    vector<int> c;
    int len1 = s1.size();
    for (int i = 0; i < len1; i++)
        a[i] = s1[len1 - i - 1] - '0';
    int jinwei = 0;
    for (int i = 0; i < len1 || jinwei; i++)
    {
        if (i >= 0)
            jinwei += a[i] * s2;
        c.push_back(jinwei % 10);
        jinwei /= 10;
    }
    string s = "";
    for (int i = c.size() - 1; i >= 0; i--)
        s += c[i] + '0';
    return s;
}

string add(string s1, string s2) // 高精度加法
{
    int a[N] = {0}, b[N] = {0}, c[N] = {0};
    int lena = s1.size(), lenb = s2.size();
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

int n;

int main()
{
    scanf("%d", &n);
    string ans = "0";
    string tmp = "1";// 阶乘
    for (int i = 1; i <= n; i++)
    {
        tmp = mul(tmp, i);
        ans = add(ans, tmp);
    }
    cout << ans << endl;
    return 0;
}