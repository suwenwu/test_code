#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e3 + 5;

int n;
pair<string, int> p[N];

int main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << p[i].first << "->" << p[i].second << endl;
    }
    return 0;
}