/*
 *  @date: 2026-04-06 18:09:30  星期一
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 小根堆.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n, x, heap[N], heap_size;

void push(int x)
{
    heap[++heap_size] = x;
    int son = heap_size;
    while (son > 1 && heap[son] < heap[son / 2])
    {
        swap(heap[son], heap[son / 2]);
        son /= 2;
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