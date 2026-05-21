#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e3 + 5;

int n, cnt;
pair<string, string> p[N];

int main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string name, s;
        int gender;
        cin >> name >> gender >> s;
        if (gender)
        {
            p[++cnt].first = name;
            p[cnt].second = s;
        }
    }
    for (int i = 1; i <= cnt; i++)
        cout << p[i].first << " " << p[i].second << endl;
    return 0;
}