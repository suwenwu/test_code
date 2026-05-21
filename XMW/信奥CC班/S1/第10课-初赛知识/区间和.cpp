/*
 *  @date: 2026-04-03 14:20:28  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 区间和.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 300005
#define ll long long

using namespace std;

int a[N], s[N], n, m;
vector<int> all_coords;         // 存储所有涉及到的坐标，用于离散化
vector<pair<int, int>> add_ops; // 存储加法操作pair<x,c> 在x位置➕c
vector<pair<int, int>> queries; // 存储查询操作 pair<l,r> 查询区间[l,r]的和

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int x, c;
        scanf("%d%d", &x, &c);
        add_ops.push_back({x, c});
        all_coords.push_back(x);
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        queries.push_back({l, r});
        all_coords.push_back(l);
        all_coords.push_back(r);
    }

    sort(all_coords.begin(), all_coords.end());
    all_coords.erase(unique(all_coords.begin(), all_coords.end()), all_coords.end()); // 去重

    for (auto &op : add_ops) // 离散化坐标到a中，并且给对应坐标加上c
    {
        int x = lower_bound(all_coords.begin(), all_coords.end(), op.first) - all_coords.begin() + 1;
        a[x] += op.second;
    }

    int len = all_coords.size();
    for (int i = 1; i <= len; i++) // 前缀和
        s[i] = s[i - 1] + a[i];

    for (auto &q : queries) // 查询区间和
    {
        int l = lower_bound(all_coords.begin(), all_coords.end(), q.first) - all_coords.begin() + 1;
        int r = lower_bound(all_coords.begin(), all_coords.end(), q.second) - all_coords.begin() + 1;
        printf("%d\n", s[r] - s[l - 1]);
    }
    return 0;
}