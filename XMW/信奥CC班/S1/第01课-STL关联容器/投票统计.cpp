#include <bits/stdc++.h>
using namespace std;
int t, n;
map<int, int> mp;

int main() {
    cin >> t;
    while (t--) {
        mp.clear();  // 多组样例，对于map清空
        cin >> n;
        int ans = 0;                    // 统计最大的票
        for (int i = 1; i <= n; ++i) {  // 输入n个人的投票情况并统计
            int num;
            cin >> num;
            mp[num]++;            // 票数+1
            if (mp[num] > ans) {  // 当前这个题目的票数大于最大值
                ans = mp[num];
            }
        }
        // 遍历map统计有多少个数和最大值一样
        int cnt = 0;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (ans == (it->second)) {
                cnt++;
            }
        }
        // 如果所有人的票数一样，则输出-1
        if (mp.size() == cnt) {
            cout << -1 << endl;
        } else {
            // 输出最多的票数的的人数
            cout << cnt << endl;
            bool flag = 1;
            // 并且将这几个人的编号输出
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                if (ans == (it->second)) {
                    if (flag) {
                        cout << it->first;
                        flag = 0;
                    } else {
                        cout << " " << it->first;
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}
