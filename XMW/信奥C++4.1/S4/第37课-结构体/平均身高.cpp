/*
 *  @date: 2026-05-16 14:45:15  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 平均身高.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

struct student
{
    string name;
    double height;
} s[N];

int n;
double sum;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].name >> s[i].height;
        sum += s[i].height;
    }
    double avg_height = sum / n;
    for (int i = 1; i <= n; i++)
    {
        if (s[i].height > avg_height)
            cout << s[i].name << " " << s[i].height << endl;
    }
    return 0;
}