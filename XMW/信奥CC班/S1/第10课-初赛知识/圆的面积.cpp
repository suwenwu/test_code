/*
 *  @date: 2026-04-03 12:56:40  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 圆的面积.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

class Circle
{
private:
    double radius;

public:
    // 构造函数
    Circle(double r)
    {
        this->radius = r;
    }
    // 计算面积
    double getArea()
    {
        return 3.14 * radius * radius;
    }
    // 设置半径
    void setRadius(double r)
    {
        this->radius = r;
    }
};
int main()
{
    Circle c(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        double x;
        cin >> x;
        c.setRadius(x);
        cout << c.getArea() << endl;
    }
    return 0;
}