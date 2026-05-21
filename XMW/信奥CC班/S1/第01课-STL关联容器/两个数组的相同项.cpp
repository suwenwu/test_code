#include <bits/stdc++.h>
using namespace std;
set<int> a, b;
int main() {
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        a.insert(x);
    }
    for (int i = 1; i <= n; i++) {
        cin >> x;
        b.insert(x);
    }
    set<int>::iterator it;
    for (auto &item : a) {
        it = b.find(item);
        if (it != b.end()) {
            cout << item << " " << endl;
        }
    }
    return 0;
}