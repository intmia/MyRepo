#include <cstdio>
typedef unsigned long long ull;


void dfs(ull n, ull k) {
    if (n == 0) return;  
    
    ull x = 1llu << (n - 1);  // x = 2^(n-1)
    
    if (k >= x) {
        
        k -= x;           
        k = x - 1 - k;    
        std::putchar('1');    
        dfs(n - 1, k);    
    } else {
      
        std::putchar('0');    
        dfs(n - 1, k);    
    }
}

int main() {
    std::freopen("code.in", "r", stdin);
    std::freopen("code.out", "w", stdout);
    
    ull n, k;
    std::scanf("%llu%llu", &n, &k);
    
    dfs(n, k);
    std::putchar('\n');

    return 0;
}