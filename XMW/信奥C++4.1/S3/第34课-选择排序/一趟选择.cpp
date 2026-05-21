#include <bits/stdc++.h>
using namespace std;
// 定义n和数组a，并且将n和n个数输入
int n;
int a[110];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // 定义一个变量为最小值，假设最小值为第一个，然后将当前变量用for循环的方式与每一个数对比，
    int k = 1;
    for (int j = 2; j <= n; j++)
        if (a[j] < a[k])
            k = j;
    // 找出最小的与第一个交换
    swap(a[1], a[k]);
    // 输出一趟选择后的数组
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}