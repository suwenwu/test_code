#include <iostream>
#include <algorithm>
using namespace std;
int arr[10005];
int main()
{
    int n, t;
    cin >> n >> t; // 输入数字牌数量和要求次数
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i]; // 输入每张数字牌的数字大小
    }
    int cnt = 0; // 记录真实的洗牌次数
    for (int i = 1; i <= t; i++)
    { // 循环t次，模拟t次要求
        char op;
        int l, r;
        cin >> op >> l >> r; // 输入洗牌规则和洗牌范围
        if (op == '+')
        {                                    // 如果洗牌规则是'+'
            cnt++;                           // 记录洗牌次数
            sort(arr + l, arr + r + 1);      // 调用函数对范围内的数值进行升序排序
            cout << "result " << cnt << ":"; // 按照格式要求输出洗牌结果
            for (int i = 1; i <= n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (op == '-')
        {                                               // 如果洗牌规则是'-'
            cnt++;                                      // 记录洗牌次数
            sort(arr + l, arr + r + 1, greater<int>()); // 调用函数对范围内的数值进行降序排序
            cout << "result " << cnt << ":";            // 按照格式要求输出洗牌结果
            for (int i = 1; i <= n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else
        { // 洗牌规则不合理，按对应要求输出
            cout << "Illegal import!";
            cout << endl;
        }
    }
    return 0;
}