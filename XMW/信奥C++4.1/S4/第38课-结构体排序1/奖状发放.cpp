/*
 *  @date: 2026-05-23 13:36:04  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 奖状发放.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

struct student
{
    string name;
    int id;
    double sum;
} a[105];

bool cmp(student a, student b)
{
    return a.sum > b.sum;
}
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].name >> a[i].id >> a[i].sum;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        cout << a[i].name << " " << a[i].id << " " << a[i].sum << endl;
    return 0;
}