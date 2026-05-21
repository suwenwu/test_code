#include <iostream>
#include <algorithm> //头文件
using namespace std;
int arr[10005];
int main()
{
    int n, t;
    cin >> n >> t; // 输入数字牌数量和洗牌次数
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i]; // 输入每张数字牌的数字大小
    }
    for (int i = 1; i <= t; i++)
    { // 循环t次，模拟t次洗牌
        int l, r;
        cin >> l >> r;              // 输入洗牌范围
        sort(arr + l, arr + r + 1); // 调用sort函数对范围内的数值进行升序排序
        for (int j = 1; j <= n; j++)
        { // 排序后输出洗牌结果
            cout << arr[j] << " ";
        }
        cout << endl; // 记得换行
    }
    return 0;
}