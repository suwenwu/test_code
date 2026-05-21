/*
 *  @date: 2026-03-27 16:15:56  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 105
#define ll long long

using namespace std;

const double eps = 1e-8; // 防止出现精度问题
double a[N][N];
int n;
int gauss()
{
    int col = 1, row = 1;
    for (; col <= n; col++)
    {
        int t = row;
        for (int i = row; i < n; i++) // 第一步，找绝对值最大的行
            if (fabs(a[i][col]) > abs(a[t][col]))
                t = i;
        if (fabs(a[t][col]) < eps) // 代表这一列已经被处理过了
            continue;
        for (int i = col; i <= n + 1; i++) // 第二步,将这一行调到最上面
            swap(a[t][i], a[row][i]);
        for (int i = n + 1; i >= col; i--) // 第三步,要倒着算，否则会影响后面的数
            a[row][i] /= a[row][col];

        for (int i = row + 1; i <= n; i++) // 第四步
            if (fabs(a[i][col]) > eps)     // 如果是0就不用操作了
                for (int j = n + 1; j >= col; j--)
                    a[i][j] -= a[row][j] * a[i][col];
        row++;
    }
    if (row <= n) // 方程数 < n
    {
        for (int i = row; i <= n; i++)
            if (fabs(a[i][n + 1]) > eps) // 最后一列有0以外的数，说明无解
                return 2;
        return 1; // 无数解, 0=0
    }
    for (int i = n; i >= 1; i--) // 有解从下往上回代
        for (int j = i + 1; j <= n + 1; j++)
            a[i][n + 1] -= a[i][j] * a[j][n + 1];
    return 0;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &a[i][j]);
    int t = gauss();
    if (t == 0) // 有唯一解
        for (int i = 1; i <= n; i++)
        {
            if (fabs(a[i][n + 1]) < eps)
                a[i][n + 1] = 0.00; // 避免输出-0.00
            printf("%.2lf\n", a[i][n + 1]);
        }
    else if (t == 1)
        printf("Infinite group solutions"); // 无数解
    else
        printf("No solution"); // 无解
    return 0;
}