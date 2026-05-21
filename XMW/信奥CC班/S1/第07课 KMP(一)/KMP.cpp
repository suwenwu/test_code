/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-01-08 14:31:54  星期四
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1005
#define ll long long

using namespace std;

vector<int> getNext(char *t)
{
    int len = strlen(t + 1);
    vector<int> Next(len + 1, 0);
    for (int i = 2, j = 0; i <= len; i++)
    {
        while (j && t[i] != t[j + 1])
            j = Next[j];
        if (t[i] == t[j + 1])
            j++;
        Next[i] = j;
    }
    return Next;
}

void KMP(char *s, char *t)
{
    vector<int> Next = getNext(t);
    int lens = strlen(s + 1), lent = strlen(t + 1);
    for (int i = 1, j = 0; i <= lens; i++)
    {
        while (j && s[i] != t[j + 1])
            j = Next[j];
        if (s[i] == t[j + 1])
            j++;
        if (j == lent)
            printf("%d\n", i - lent + 1);
    }
    for (int i = 1; i <= lent; i++)
        printf("%d ", Next[i]);
}

char s[N], t[N];

int main()
{
    scanf("%s%s", s + 1, t + 1);
    KMP(s, t);
    return 0;
}
