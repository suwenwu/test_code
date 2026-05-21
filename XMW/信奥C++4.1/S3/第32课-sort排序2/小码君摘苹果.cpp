#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, h, s;
    cin >> n >> h >> s;
    int apple[10010];
    for (int i = 1; i <= n; i++)
    {
        cin >> apple[i];
    }
    h += 20;                        // 将身高增加20cm，算入椅子高度
    sort(apple + 1, apple + n + 1); // 将苹果按照高度从小到大排序
    int cnt = 0;                    // 记录可以摘到的苹果数量
    for (int i = 1; i <= n; i++)
    {
        if (apple[i] <= h && s >= i)
        { // 如果能够够到苹果 并且 还有至少i秒可以摘苹果
            cnt++;
            s -= i; // 时间减少
        }
        else
        {
            break; // 不满足条件，直接结束
        }
    }
    cout << cnt;
    return 0;
}