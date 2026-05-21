/*
 *  @date: 2026-04-09 10:06:17  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: demo.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

// char s[N];

// vector<int> getNext(char *t)
// {
//     int len = strlen(t + 1);
//     vector<int> next(len + 1);
//     for (int i = 2, j = 0; i <= len; i++)
//     {
//         while (j && t[i] != t[j + 1])
//             j = next[j];
//         if (t[i] == t[j + 1])
//             j++;
//         next[i] = j;
//     }
//     return next;
// }

// int main()
// {
//     scanf("%s", s + 1);
//     int len = strlen(s + 1);
//     vector<int> res = getNext(s);
//     for (int i = 1; i <= len; i++)
//         printf("%d ", res[i]);
//     return 0;
// }

string s;

vector<int> getNext(string t)
{
    int len = t.size();
    vector<int> next(len);
    for (int i = 1, j = 0; i < len; i++)
    {
        while (j && t[i] != t[j])
            j = next[j - 1];
        if (t[i] == t[j])
            j++;
        next[i] = j;
    }
    return next;
}

int main()
{
    cin >> s;
    int len = s.size();
    vector<int> res = getNext(s);
    for (int i = 0; i < len; i++)
        printf("%d ", res[i]);
    return 0;
}
