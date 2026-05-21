#include <bits/stdc++.h>
using namespace std;
map<string, int> mp;
int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        mp[s]++;
    }
    int ans = 0;
    string flag;
    for (auto &item : mp) {
        string key = item.first;
        int val = item.second;
        if (val > ans) {
        	ans = val;
            flag = key;
        }
    }
    cout << flag << " " << ans << endl;
    return 0;
}