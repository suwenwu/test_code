/*
 *  @date: 2026-04-09 11:46:43  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 魔板.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define N 500005
using namespace std;

struct node
{
    int a[9], step;
    string s = ""; // 记录路径
} st, ed;

int f[10], ans = N;
string ans_str = "Z"; // 记录答案路径
queue<node> q1;
unordered_map<int, string> mp;

void fc() // 阶乘
{
    f[1] = 1;
    for (int i = 2; i <= 8; i++)
        f[i] = f[i - 1] * i;
}

// 康拓展开，将一个排列映射为一个整数
int contor(node x)
{
    int sum = 0;
    for (int i = 1; i <= 8; i++)
    {
        int cnt = 0;
        for (int j = i + 1; j <= 8; j++)
            if (x.a[i] > x.a[j])
                cnt++;
        sum += cnt * f[8 - i];
    }
    return sum; // 返回映射后的整数
}

node changeA(node x) // A改变状态
{
    for (int i = 1; i <= 4; i++)
        swap(x.a[i], x.a[i + 4]);
    return x;
}

node changeB(node x) // B改变状态
{
    for (int i = 4; i >= 2; i--)
    {
        swap(x.a[i - 1], x.a[i]);
        swap(x.a[i + 3], x.a[i + 4]);
    }
    return x;
}

node changeC(node x) // C改变状态
{
    swap(x.a[3], x.a[2]);
    swap(x.a[6], x.a[2]);
    swap(x.a[7], x.a[6]);
    return x;
}

void bfs()
{
    st.step = 0;
    st.s = "";
    for (int i = 1; i <= 4; i++) // 初始化状态
    {
        st.a[i] = i;
        st.a[i + 4] = 9 - i;
    }
    q1.push(st);
    mp[contor(st)] = ""; // 将初始状态加入哈希表

    int end_contor = contor(ed); // 计算目标状态的康托值

    while (!q1.empty())
    {
        node x = q1.front();
        q1.pop();

        if (x.step > ans)
            break;
        int contor_x = contor(x);
        if (contor_x == end_contor)
        {
            ans = x.step;
            ans_str = min(ans_str, x.s); // 记录答案路径
            break;
        }
        for (int i = 1; i <= 3; i++)
        {
            node t; // 改变状态后
            if (i == 1)
                t = changeA(x);
            else if (i == 2)
                t = changeB(x);
            else
                t = changeC(x);
            contor_x = contor(t);   // 计算t的康托值
            if (mp.count(contor_x)) // 如果t在哈希表中 ,则跳过
                continue;
            t.step = x.step + 1;
            t.s = x.s + char(i + 'A' - 1);
            mp[contor_x] = t.s;
            q1.push(t);
        }
    }
}

int main()
{
    fc();
    for (int i = 1; i <= 4; i++)
        scanf("%d", &ed.a[i]);
    for (int i = 8; i >= 5; i--)
        scanf("%d", &ed.a[i]);
    bfs();
    cout << ans << "\n"
         << ans_str; // 输出答案
    return 0;
}