// 题解复制awa
#include <bits/stdc++.h>
using namespace std;
long long f[20];
long long C[20][20];
long long fact[20];
int main()
{
    int n;
    cin >> n;
    // 预处理组合数
    for (int i = 0; i <= n; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 0;
        for (int k = 1; k <= i; k++)
        {
            f[i] += C[i][k] * f[i - k];
        }
    }
    cout << f[n] << endl;
    return 0;
}