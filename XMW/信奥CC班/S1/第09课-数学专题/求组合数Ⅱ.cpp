/*
 *  @date: 2026-04-02 16:43:37  星期四
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 求组合数Ⅱ.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 5005
#define ll long long

using namespace std;

int primes[N], cnt;
bool is_not_prime[N];
int sum[N]; // 存储每个质因子的指数

// 1. 线性筛法求质数
void get_primes(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!is_not_prime[i])
            primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++)
        {
            is_not_prime[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

// 2. 勒让德定理：求 n! 中质因子 p 的个数
int get_count(int n, int p)
{
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}

// 3. 高精度乘法：res = res * b
vector<int> multiply(vector<int> &a, int b)
{
    vector<int> c;
    int t = 0, len = a.size();
    for (int i = 0; i < len || t; i++)
    {
        if (i < len)
            t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    get_primes(a);
    // 计算 C(a, b) 中每个质因子的幂次
    for (int i = 0; i < cnt; i++)
    {
        int p = primes[i];
        sum[i] = get_count(a, p) - get_count(b, p) - get_count(a - b, p);
    }

    vector<int> res;
    res.push_back(1);

    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < sum[i]; j++)
            res = multiply(res, primes[i]);
    for (int i = res.size() - 1; i >= 0; i--)
        printf("%d", res[i]);
    printf("\n");

    return 0;
}