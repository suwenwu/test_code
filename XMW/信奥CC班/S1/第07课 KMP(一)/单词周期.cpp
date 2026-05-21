/*
 *  @date: 2026-04-09 10:47:32  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 单词周期.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 2000005
#define ll long long

using namespace std;

ll ans;
int n, nxt[N];
char s[N];

void getnxt()
{
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && s[i] != s[j + 1])
            j = nxt[j];
        if (s[i] == s[j + 1])
            j++;
        nxt[i] = j;
    }
}

int find(int x)
{
    if (nxt[nxt[x]] == 0)
        return nxt[x];
    return nxt[x] = find(nxt[x]);
}

int main()
{
    scanf("%d%s", &n, s + 1);
    getnxt();
    for (int i = 1; i <= n; i++)
        if (nxt[i] > 0)
        {
            int min_b = find(i);
            ans += (i - min_b);
        }
    printf("%lld\n", ans);
    return 0;
}