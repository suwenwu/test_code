#include <iostream>
using namespace std;
int a[1010];
int main()
{
    // 定义n并且输入n
    int n;
    cin >> n;
    // 将n个人的成绩输入到数组
    for (int j = 1; j <= n; j++)
    {
        cin >> a[j];
    }
    // 运用选择排序的方式将最大的数选出与第i个交换
    for (int i = 1; i <= n - 1; i++)
    {
        int k = i;
        for (int j = i; j <= n; j++)
        {
            if (a[j] > a[k])
            {
                k = j;
            }
        }
        swap(a[i], a[k]);
    }
    // 输出排序好的数组
    for (int j = 1; j <= n; j++)
    {
        cout << a[j] << " ";
    }
    return 0;
}