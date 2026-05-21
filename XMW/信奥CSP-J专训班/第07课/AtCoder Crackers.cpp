/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2024-06-06 14:00:39  星期四
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2024 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    printf("%d", (n % k) ? 1 : 0);
    return 0;
}