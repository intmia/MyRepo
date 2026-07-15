#include <iostream>
#include <string>
#include <vector>

int main() {
    freopen("toy.in", "r", stdin);
    freopen("toy.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> dir(n);
    std::vector<std::string> job(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> dir[i] >> job[i];
    }

    int cur = 0; 
    for (int i = 0; i < m; ++i) {
        int a, s;
        std::cin >> a >> s;
        
        if ((dir[cur] == 0 && a == 0) || (dir[cur] == 1 && a == 1)) {
            
            cur = (cur - s) % n;
        } else {
            
            cur = (cur + s) % n;
        }
        if (cur < 0) cur += n;
    }

    std::cout << job[cur] << std::endl;
    return 0;
}