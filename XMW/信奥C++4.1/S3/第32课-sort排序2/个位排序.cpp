#include <iostream>
#include <algorithm>
using namespace std;
int arr[1000010];
int odd[1000010], even[1000010]; // 数组odd记录个位为奇数的元素值 数组even记录个位为偶数的元素值
int main()
{
    int n;
    cin >> n;
    int num_o = 0, num_e = 0; // num_o记录个位为奇数的元素数量 num_e记录个位为偶数的元素数量
    for (int i = 1; i <= n; i++)
    { // 遍历数组 处理元素
        cin >> arr[i];
        if ((arr[i] % 10) % 2 == 1)
        {
            num_o++;
            odd[num_o] = arr[i];
        }
        else
        {
            num_e++;
            even[num_e] = arr[i];
        }
    }
    sort(odd + 1, odd + num_o + 1, greater<int>()); // 将个位为奇数的元素 从大到小排列
    sort(even + 1, even + num_e + 1);               // 将个位为偶数的元素 从小到大排列
    num_o = 1, num_e = 1;                           // 从第一个元素开始按原奇偶顺序输出
    for (int i = 1; i <= n; i++)
    {
        if ((arr[i] % 10) % 2 == 1)
        {
            cout << odd[num_o] << " ";
            num_o++;
        }
        else
        {
            cout << even[num_e] << " ";
            num_e++;
        }
    }
    return 0;
}