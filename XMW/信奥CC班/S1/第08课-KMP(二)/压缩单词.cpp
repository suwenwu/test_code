/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-03-12 14:08:38  星期四
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1000005
#define ll long long

using namespace std;

int n, top;
char s[N], ans[N];

vector<int> getNext(char *t)
{
    int len = strlen(t + 1);
    vector<int> next(len + 1, 0);
    for (int i = 2, j = 0; i <= len; i++)
    {
        while (j && t[i] != t[j + 1])
            j = next[j];
        if (t[i] == t[j + 1])
            j++;
        next[i] = j;
    }
    return next;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        if (i == 1)
        {
            int len = strlen(s + 1);
            for (int i = 1; i <= len; i++) // 将第一个字符串的所有字符放入ans中
                ans[++top] = s[i];
            continue;
        }
        int lena = top, lenb = strlen(s + 1);
        int len = min(lena, lenb), cnt = lenb;
        s[++cnt] = '@';                // 添加一个特殊字符，区分前后字符串
        for (int j = 1; j <= len; ++j) // 将ans的后len个字符放入s中
            s[++cnt] = ans[lena - len + j];
        vector<int> next = getNext(s);
        for (int j = next[cnt] + 1; j <= lenb; j++)
            ans[++top] = s[j];
    }
    ans[++top] = '\0';
    printf("%s\n", ans + 1);
    return 0;
}