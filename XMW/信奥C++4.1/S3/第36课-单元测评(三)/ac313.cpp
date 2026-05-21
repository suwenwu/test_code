#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[100005], b[100005], x = 0, y = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 1)
            cin >> a[x++]; // 存储到奇数位数组 a
        else
            cin >> b[y++]; // 存储到偶数位数组 b
    }

    // 分别对奇数，偶数数组升序和降序排序
    sort(a + 0, a + x);                 // 请思考为什么 a + x 这里不需要再 + 1了？同样下一行也是
    sort(b + 0, b + y, greater<int>()); // 偶数是降序排序的

    for (int i = 0; i < x; i++)
    { // 奇数位一定会 大于等于 偶数位 个数的，请思考为什么
        cout << a[i] << " ";
        if (i < y)
            cout << b[i] << " "; // i < y 是为何？
    }
    return 0;
}