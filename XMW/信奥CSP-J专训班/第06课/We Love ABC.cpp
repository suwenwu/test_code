/*
 *  @date: 2026-04-10 13:25:44  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: We Love ABC.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define mod 1000000007
#define N 100005
#define ll long long

using namespace std;

/* 解法1，计数
char s[N];
int n;
long long ans, numa[N], numc[N], totw, numw[N], _numw[N]; // 前缀a,后缀c,总数？,前后缀？

long long binpow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res % mod;
}

void init()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) // 计算前缀'A'和'?'的数量，和总'?'的数量
    {
        numa[i] = numa[i - 1];
        numw[i] = numw[i - 1];
        if (s[i] == '?')
        {
            totw++;
            numw[i]++;
        }
        else if (s[i] == 'A')
            numa[i]++;
    }
    for (int i = n; i >= 1; i--) // 计算后缀'C'和'?'的数量
    {
        _numw[i] = _numw[i + 1];
        numc[i] = numc[i + 1];
        if (s[i] == '?')
            _numw[i]++;
        if (s[i] == 'C')
            numc[i]++;
    }
}

int main()
{
    init();
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'B')
        {
            // numa[i] * numc[i]  * binpow(3, totw) 前A后C
            ans = (ans + numa[i] % mod * numc[i] % mod * binpow(3, totw) % mod) % mod;
            // 前A后?，将?看成C,结果就会多1*numa[i]*binpow(3, totw - 1),当前B的后面有_numw[i]个问号，所以
            ans = (ans + numa[i] % mod * _numw[i] % mod * binpow(3, max(totw - 1, 0ll)) % mod) % mod;
            // 前?后C
            ans = (ans + numc[i] % mod * numw[i] % mod * binpow(3, max(totw - 1, 0ll)) % mod) % mod;
            //前?后?如果第个B前面的某个"?"变为A,然后后边的某个"?"变为C，产生的贡献就是1*binpow(3,totw-2),那前面有numw[i]个'?'，后面有_numw[i]个'?'
            //所以是numw[i]*_numw[i]*binpow(3,totw-2)
            ans = (ans + _numw[i] % mod * numw[i] % mod * binpow(3, max(totw - 2, 0ll)) % mod) % mod;
        }
        else if (s[i] == '?')
        {
            // 前A,后C
            ans = (ans + numa[i] % mod * numc[i] % mod * binpow(3, max(totw - 1, 0ll)) % mod) % mod;
            // 前A后?
            ans = (ans + numa[i] % mod * _numw[i + 1] % mod * binpow(3, max(0ll, totw - 2)) % mod) % mod;
            // 前?后C
            ans = (ans + numw[i - 1] % mod * numc[i] % mod * binpow(3, max(0ll, totw - 2)) % mod) % mod;
            // 前?后?
            ans = (ans + numw[i - 1] % mod * _numw[i + 1] % mod * binpow(3, max(0ll, totw - 3)) % mod) % mod;
        }
    }
    cout << ans;
    return 0;
}
*/
/*
 * @param dp[0]: ""的数量 dp[1]: "A"的数量 dp[2]: "AB"的数量 dp[3]: "ABC"的数量
 */
ll dp[4];
char s[N];

int main()
{
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    dp[0] = 1;
    for (int i = 1; i <= len; i++)
    {
        if (s[i] == 'A')
            dp[1] = (dp[0] + dp[1]) % mod;
        else if (s[i] == 'B')
            dp[2] = (dp[1] + dp[2]) % mod;
        else if (s[i] == 'C')
            dp[3] = (dp[2] + dp[3]) % mod;
        else // ?
        {
            // 1. 形成 "ABC" 的总数：
            // 之前的每个 "ABC" 方案在当前位置填 A, B, C 都会保留 (3 * dp[3])
            // 加上当前位置填 'C' 时，由之前的 "AB" 贡献的新方案 (dp[2])
            dp[3] = (3 * dp[3] + dp[2]) % mod;
            // 2. 形成 "AB" 的总数：
            // 之前的每个 "AB" 方案在当前位置填 A, B, C 都会保留 (3 * dp[2])
            // 加上当前位置填 'B' 时，由之前的 "A" 贡献的新方案 (dp[1])
            dp[2] = (3 * dp[2] + dp[1]) % mod;
            // 3. 形成 "A" 的总数：
            // 之前的每个 "A" 方案在当前位置填 A, B, C 都会保留 (3 * dp[1])
            // 加上当前位置填 'A' 时，由之前的 "" 贡献的新方案 (dp[0])
            dp[1] = (3 * dp[1] + dp[0]) % mod;
            // 4. 形成的 "" 的总数：
            // 之前的每个 "" 方案在当前位置填 A, B, C 都会保留 (3 * dp[0])
            dp[0] = 3 * dp[0] % mod;
        }
    }
    printf("%lld", dp[3]);
    return 0;
}