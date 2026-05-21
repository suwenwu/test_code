#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e3 + 5;

int n, cnt;
pair<int, string> p[N];

bool cmp(pair<int, string> x, pair<int, string> y)
{
    return x.first < y.first;
}

int main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].first >> p[i].second;
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        cout << p[i].second << endl;
    return 0;
}