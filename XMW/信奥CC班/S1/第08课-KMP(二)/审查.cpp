/*
 *  @filename:~/Documents/workspace/vscode/XMW
 *  @author: Ly_boy
 *  @date: 2026-03-13 13:29:48  星期五
 *  @version: V1.0.1
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 1000005
#define ll long long

using namespace std;

char s[N], t[N];
int nxt[N];  // KMP 的 next 数组
int f[N];    // 记录 s 中每个位置匹配到 t 的长度
int st[N];   // 模拟栈，存储保留下来的字符在 s 中的下标
int top = 0; // 栈顶指针

/**
 * 预处理模式串 t 的 next 数组
 */
void getNext(int lent)
{
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= lent; i++)
    {
        while (j > 0 && t[i] != t[j + 1])
            j = nxt[j];
        if (t[i] == t[j + 1])
            j++;
        nxt[i] = j;
    }
}

/**
 * KMP 结合栈实现字符串消除
 */
void solve()
{
    scanf("%s %s", s + 1, t + 1);
    int lens = strlen(s + 1), lent = strlen(t + 1);
    getNext(lent);
    for (int i = 1, j = 0; i <= lens; i++)
    {
        // 标准 KMP 匹配过程
        while (j > 0 && s[i] != t[j + 1])
            j = nxt[j];
        if (s[i] == t[j + 1])
            j++;
        // 将当前字符入栈
        st[++top] = i;
        f[i] = j; // 记录当前下标 i 对应的匹配进度

        // 如果匹配到了完整的模式串 t
        if (j == lent)
        {
            top -= lent; // 从栈中弹出 lent 个字符，即删除了 t
            // 关键：恢复匹配进度 j
            // 如果栈空了，进度归零；否则恢复为栈顶字符当时记录的进度
            if (top == 0)
                j = 0;
            else
                j = f[st[top]];
        }
    }

    // 输出栈中剩余的字符
    for (int i = 1; i <= top; i++)
        printf("%c", s[st[i]]);
    printf("\n");
}

int main()
{
    solve();
    return 0;
}