#include <iostream>
#include <algorithm>

struct Node {
    int a, b, c;
} p[100005];

int f[40005]; // 并查集数组，大小为2*N
int n, m;

// 初始化并查集
void init() {
    for (int i = 1; i <= 2 * n; i++) {
        f[i] = i;
    }
}
// 查找根节点（路径压缩）
int getf(int x) {
    if (f[x] == x)
        return x;
    else {
        f[x] = getf(f[x]);
        return f[x];
    }
}
// 合并两个集合
void merge(int x, int y) {
    int t1 = getf(x);
    int t2 = getf(y);
    if (t1 != t2) {
        f[t2] = t1;
    }
}
// 比较函数，按怨气值从大到小排序
bool cmp(Node x, Node y) {
    return x.c > y.c;
}
int main() {
    std::cin >> n >> m;    
    // 读入数据
    for (int i = 1; i <= m; i++) {
        std::cin >> p[i].a >> p[i].b >> p[i].c;
    }    
    // 初始化并查集
    init();    
    // 按怨气值从大到小排序
    std::sort(p + 1, p + m + 1, cmp);    
    // 贪心处理
    for (int i = 1; i <= m; i++) {
        int a = p[i].a, b = p[i].b, c = p[i].c;        
        // 如果a和b已经在同一集合，则这个冲突无法避免，输出答案
        if (getf(a) == getf(b)) {
            std::cout << c << std::endl;
            return 0;
        }        
        // 否则，将a和b的敌人合并，b和a的敌人合并
        merge(a, b + n);  // a 与 b 的敌人放在一起
        merge(b, a + n);  // b 与 a 的敌人放在一起
    }    
    // 如果没有发生任何冲突
    std::cout << 0 << std::endl;
    return 0;
}