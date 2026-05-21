/*
 *  @date: 2026-04-02 09:50:24  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 大根堆.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 100005
#define ll long long

using namespace std;

int n, x, heap[N], heap_size;

void push(int x)
{
    heap[++heap_size] = x;
    int son = heap_size;
    while (son > 1 && heap[son] > heap[son >> 1])
    {
        swap(heap[son], heap[son >> 1]);
        son >>= 1;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        push(x);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", heap[i]);
    return 0;
}