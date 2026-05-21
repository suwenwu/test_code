/*
 *  @date: 2026-05-16 13:28:14  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 结构体输入输出.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct student
{
    string name; // 姓名
    int age;     // 年龄
};
int main()
{
    // 2、定义结构体变量，输入信息
    student a, b, c;
    cin >> a.name >> a.age;
    cin >> b.name >> b.age;
    cin >> c.name >> c.age;
    // 3、按照输入顺序，依次输出每位同学的信息
    cout << a.name << " " << a.age << '\n';
    cout << b.name << " " << b.age << '\n';
    cout << c.name << " " << c.age << '\n';
    return 0;
}