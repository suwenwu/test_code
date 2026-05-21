/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-03-13 15:18:26  星期五
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1000005
#define ll long long

using namespace std;

vector<int> getNext(char *t)
{
    int len = strlen(t + 1);
    vector<int> Next(len + 1, 0);
    for (int i = 2, j = 0; i <= len; i++)
    {
        while (j > 0 && t[i] != t[j + 1])
            j = Next[j];
        if (t[i] == t[j + 1])
            j++;
        Next[i] = j;
    }
    return Next;
}

char s[N];

int main()
{
    while (scanf("%s", s + 1) && s[1] != '.')
    {
        int sum = 0;
        int len = strlen(s + 1);
        vector<int> Next = getNext(s);
        if (len % (len - Next[len]) == 0)
            sum = len / (len - Next[len]);
        else
            sum = 1;
        printf("%d\n", sum);
    }
    return 0;
}