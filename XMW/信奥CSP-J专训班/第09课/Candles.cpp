/*
 *  @filename:demo.cpp
 *  @author: Ly_boy
 *  @date: 2024-06-12 08:21:55 星期三
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2023 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

using namespace std;

int n, k;
long long ans = LLONG_MAX, x[100005]; // 注意ans的初始值为极大值

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &x[i]);
    for (int i = 1; i <= n - k + 1; ++i)
        ans = min(ans, x[i + k - 1] - x[i] + min(abs(x[i]), abs(x[i + k - 1]))); // 式子
    printf("%lld\n", ans);
    return 0;
}