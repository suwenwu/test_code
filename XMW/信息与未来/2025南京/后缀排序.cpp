#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
    sort(p.begin(), p.end(), [&](int a, int b)
         { return s.substr(a) < s.substr(b); });
    for (int x : p)
        cout << x + 1 << " ";
    return 0;
}