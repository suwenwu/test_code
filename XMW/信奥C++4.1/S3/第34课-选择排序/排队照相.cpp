#include <iostream>
#include <algorithm>
using namespace std;
int a[110];
int main()
{
    // 输入n和n个数的数组
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // 将数组升序排序
    sort(a, a + n);
    // 输出正数，为男生的升高排序
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
            cout << a[i] << " ";
    }
    // 输出负数，为女生的升高排序
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
            cout << a[i] << " ";
    }
    return 0;
}