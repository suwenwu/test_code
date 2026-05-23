/*
 *  @date: 2026-05-23 14:23:03  星期六
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 奖状发放2.cpp
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
    double chinese, math, english, sum;
    int stuNo;
} s[N];

int n;

bool cmp(student a, student b)
{
    if (a.sum == b.sum)
    {
        if (a.chinese == b.chinese)
        {
            return a.stuNo < b.stuNo;
        }
        return a.chinese > b.chinese;
    }
    return a.sum > b.sum;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].name >> s[i].chinese >> s[i].math >> s[i].english;
        s[i].sum = s[i].chinese + s[i].math + s[i].english;
        s[i].stuNo = i;
    }
    sort(s + 1, s + 1 + n, cmp);
    cout << s[1].name << " " << s[1].sum << endl;
    cout << s[2].name << " " << s[2].sum << endl;
    return 0;
}