/*
 *  @filename:~/Documents/workspace/vscode_space
 *  @author: Ly_boy
 *  @date: 2025-11-14 13:09:07  星期五
 *  @compiler: 2025 by Ly_boy, All Rights Reserved.
 */
#include <bits/stdc++.h>

#define endl "\n"
#define N 500005
#define ll long long
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, a[N], cnt[15], b[N], maxNum;

void RadixSort(int n, int arr[], int exp)
{
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++)
    {
        int digit = (arr[i] / exp) % 10; // 获取当前位的数字
        cnt[digit]++;                    // 统计当前位的数字出现的次数
    }
    for (int i = 8; i >= 0; i--) // 计算当前位数字的累积次数
        cnt[i] += cnt[i + 1];
    for (int i = n; i >= 1; i--)
    {
        int digit = (arr[i] / exp) % 10; // 获取当前位的数字
        b[cnt[digit]] = arr[i];          // 将当前位的数字按照累积次数放入结果数组
        cnt[digit]--;                    // 更新当前位的数字的累积次数
    }
    for (int i = 1; i <= n; i++)
        arr[i] = b[i]; // 将结果数组复制回原数组
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        maxNum = max(maxNum, a[i]);
    }
    for (int exp = 1; exp <= maxNum; exp *= 10) // exp表示当前处理的位数
    {
        RadixSort(n, a, exp);
        for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}