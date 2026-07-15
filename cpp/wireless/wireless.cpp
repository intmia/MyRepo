#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    int x, y, k;
} p[25];

int main() {
    int d, n;
    cin >> d >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y >> p[i].k;
    }
    
    long long max_sum = -1;
    int cnt = 0;
    
    for (int cx = 0; cx <= 128; ++cx) {
        for (int cy = 0; cy <= 128; ++cy) {
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                if (abs(p[i].x - cx) <= d && abs(p[i].y - cy) <= d) {
                    sum += p[i].k;
                }
            }
            if (sum > max_sum) {
                max_sum = sum;
                cnt = 1;
            } else if (sum == max_sum) {
                ++cnt;
            }
        }
    }
    
    cout << cnt << " " << max_sum << endl;
    return 0;
}
