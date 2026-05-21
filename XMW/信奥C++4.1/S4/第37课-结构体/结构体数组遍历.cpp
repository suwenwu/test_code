/*
 *  @date: 2026-05-16 13:28:14  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 结构体数组遍历.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct student // 自定义类型 int double
{
    string name;
    double score;
    int age;
} a[105];

int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].name >> a[i].score >> a[i].age;
    for (int i = 1; i <= n; i++)
    {
        cout << a[i].name << " ";
        printf("%.1lf ", a[i].score);
        cout << a[i].age << endl;
    }
    return 0;
}