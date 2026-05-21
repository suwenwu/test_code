/*
 *  @date: 2026-04-09 16:10:54  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 编程2.cpp
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
int n;

int main()
{
    scanf("%d%s", &n, s + 1);
    vector<int> Next = getNext(s);
    printf("%d\n", n - Next[n]);
    return 0;
}