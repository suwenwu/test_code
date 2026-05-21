#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;

int n, m, T;
deque<int> q;

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        if (n == 1)
        {
            cin >> m;
            q.push_front(m);
        }
        else if (n == 2)
        {
            cin >> m;
            q.push_back(m);
        }
        else if (n == 3)
        {
            if (!q.size())
                cout << "impossible" << endl;
            else
                q.pop_front();
        }
        else if (n == 4)
        {
            if (!q.size())
                cout << "impossible" << endl;
            else
                q.pop_back();
        }
        else if (n == 5)
        {
            if (!q.size())
                cout << "impossible" << endl;
            else
                cout << q.front() << endl;
        }
        else if (n == 6)
        {
            if (!q.size())
                cout << "impossible" << endl;
            else
                cout << q.back() << endl;
        }
        else if (n == 7)
        {
            cout << q.size() << endl;
        }
        else if (n == 8)
        {
            if (q.empty())
            {
                cout << "true" << endl;
            }
            else
            {
                cout << "false" << endl;
            }
        }
        else if (n == 9)
        {
            q.clear();
        }
    }

    return 0;
}