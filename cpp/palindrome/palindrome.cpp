
#include <iostream>


bool is_binary_palindrome(int x) {

    int msb = 31;
    while (msb > 0 && ((x >> msb) & 1) == 0) {
        msb--;
    }
    

    int l = msb, r = 0;
    while (l > r) {
        if (((x >> l) & 1) != ((x >> r) & 1)) {
            return false;
        }
        l--; r++;
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (is_binary_palindrome(i)) {
            ++count;
        }
    }
    std::cout << count << std::endl;
    return 0;
}