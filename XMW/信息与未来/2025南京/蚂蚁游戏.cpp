#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    long long L;
    int n;
    cin >> L >> n;

    long long min_time = 0, max_time = 0;
    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        long long near = min(x, L - x);
        long long far = max(x, L - x);

        if (near > min_time)
            min_time = near;
        if (far > max_time)
            max_time = far;
    }

    cout << min_time << " " << max_time << endl;
    return 0;
}