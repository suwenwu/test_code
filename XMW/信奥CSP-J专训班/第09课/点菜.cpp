/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2024-11-08 16:43:34  星期五
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2024 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int sum = 0, a[6];

bool cmp(int x, int y)
{
    int a = x % 10, b = y % 10;
    if (a == 0 && b != 0)
        return true;
    else if (a != 0 && b == 0)
        return false;
    else
        return a > b;
}

int main()
{
    for (int i = 1; i <= 5; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 6, cmp);
    for (int i = 1; i <= 5; i++)
    {
        if (i != 5)
            sum += a[i] % 10 == 0 ? a[i] : (a[i] / 10 + 1) * 10;
        else
            sum += a[i];
    }
    printf("%d\n", sum);
    return 0;
}