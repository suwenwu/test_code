/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2024-06-29 13:42:47  星期六
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2024 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, a[35], cnt;

int main()
{
    cin >> n;
    if (n == 0)
    {
        printf("0");
        return 0;
    }
    while (n)
    {
        a[++cnt] = abs(n % (-2));
        n = (n - a[cnt]) / (-2);
    }
    for (int i = cnt; i >= 1; i--)
        printf("%d", a[i]);
    return 0;
}