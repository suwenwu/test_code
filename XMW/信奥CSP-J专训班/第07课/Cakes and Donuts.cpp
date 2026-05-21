// LUOGU_RID: 161414444
/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2024-06-06 15:19:00  星期四
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2024 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i <= n; i += 4)
    {
        if ((n - i) % 7 == 0)
        {
            printf("Yes");
            return 0;
        }
    }
    printf("No");
    return 0;
}