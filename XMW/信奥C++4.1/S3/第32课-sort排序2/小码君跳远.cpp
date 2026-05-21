#include <iostream>
#include <algorithm>
using namespace std;
int arr[1010], brr[1010]; // 使用数组brr存储相邻跳远结果差的绝对值
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i <= n - 1; i++)
    {
        brr[i] = abs(arr[i + 1] - arr[i]); // 计算差 注意下标范围
    }
    sort(brr + 1, brr + n); // 对差的绝对值从小到大排序
    bool flag = true;
    for (int i = 1; i < n; i++)
    {
        if (brr[i] != i)
        { // 如果第i个绝对值不是i，则说明不是完美跳远
            flag = false;
            break;
        }
    }
    if (flag)
    { // 根据标记结果判断
        cout << "Jump!";
    }
    else
    {
        cout << "Don't jump!";
    }
    return 0;
}