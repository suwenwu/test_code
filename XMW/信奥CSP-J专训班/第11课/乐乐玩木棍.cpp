#include <bits/stdc++.h>

using namespace std;

int a[10]; // a[i] 表示组成数字i需要的木棍数量
int n;
string s;

int main()
{
    for (int i = 0; i <= 9; i++)
        scanf("%d", &a[i]);
    scanf("%d", &n); // n个木棍

    int min_stick = *min_element(a, a + 10); // 找到最小的木棍数量

    int max_len = 0;
    for (int i = 1; i <= 9; i++) //枚举从1到9的数字，找到能组成的最长长度
        if (n >= a[i])
        {
            int len = 1 + (n - a[i]) / min_stick; // 以a[i]为第一位数，能获得的最长长度
            max_len = max(max_len, len);
        }

    for (int i = 1; i <= max_len; i++) // 从第1位数开始枚举
        for (int j = 9; j >= 0; j--)   // 枚举数字j
        {
            if (i == 1 && j == 0) // 如果是第一位数，不能为0
                continue;
            if (n >= a[j])
            {
                int tmp_stick = n - a[j];  // 剩余的木棍数量
                int tmp_len = max_len - i; // 剩余的长度

                if (tmp_stick >= tmp_len * min_stick) // 如果剩余的木棍数量>=剩余长度*最小数字的木棍数量
                {
                    s += to_string(j);
                    n -= a[j];
                    break;
                }
            }
        }
    cout << s;
    return 0;
}