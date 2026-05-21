#include <iostream>
#include <algorithm>
using namespace std;
int arr[100005];
bool cmp(int x, int y)
{                                                // 前一个元素为x，后一个元素为y
    int left = x / 10 % 10, right = y / 10 % 10; // left记录x的十位值 right记录y的十位值
    if (left > right)
    { // 如果x的十位值更大，x应该在前，位置正确返回true
        return true;
    }
    else if (left == right)
    { // 如果十位值相等，按照数字值从大到小排序
        if (x > y)
        { // 如果x值更大，x应该在前，位置正确返回true
            return true;
        }
        else
        { // 如果y值更大，y应该在前，位置错误返回false
            return false;
        }
    }
    else
    { // 如果y的十位值更大，y应该在前，位置错误返回false
        return false;
    }
}
int main()
{
    int n;
    cin >> n; // 输入数字牌数量
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i]; // 输入n张数字牌数字大小
    }
    sort(arr + 1, arr + n + 1, cmp); // 调用函数洗牌
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " "; // 输出最终洗牌后的结果
    }
    return 0;
}