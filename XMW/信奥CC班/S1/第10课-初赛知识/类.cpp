/*
 *  @date: 2026-04-03 15:10:35  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 类.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

class Shapes
{
private:
    int x, y;
    double PI = 3.14159265358979323846;

public:
    Shapes() {} // 构造函数
    double calculateTriangleArea()
    {
        return 0.5 * x * y;
    }

    double calculateRectangleArea()
    {
        return x * y;
    }

    double calculateCircleArea()
    {
        return PI * x * 2;
    }

    void setXY(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

int main()
{
    int x, y;
    scanf("%d%d", &x, &y);
    Shapes shapes = Shapes();
    shapes.setXY(x, y);
    cout << shapes.calculateTriangleArea() << endl;
    cout << shapes.calculateRectangleArea() << endl;
    cout << shapes.calculateCircleArea() << endl;
    return 0;
}