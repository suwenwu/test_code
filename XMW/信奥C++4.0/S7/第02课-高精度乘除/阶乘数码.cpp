/*
 *  @date: 2026-03-26 10:18:11  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 阶乘数码.cpp
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

int t, n, a;

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &a);
        string ans = "1";
        for (int i = 1; i <= n; i++)
            ans = mul(ans, i);
        cout << count(ans.begin(), ans.end(), char(a + '0')) << endl;
    }
    return 0;
}