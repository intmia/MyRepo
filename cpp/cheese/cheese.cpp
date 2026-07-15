#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;   // 定义长整型别名，用于存储坐标和距离平方（防止溢出）

ll x[1010], y[1010], z[1010];  // 存储每个空洞的球心坐标
int f[1010];                    // 并查集父节点数组
int n;                          // 空洞个数
ll h, r;                        // 奶酪高度和空洞半径

// 初始化并查集，每个空洞自成一个集合
void init() {
    for (int i = 0; i < n; i++)
        f[i] = i;
}

// 查找 x 所在集合的根节点（路径压缩）
int getf(int x) {
    if (f[x] == x)
        return x;
    else {
        f[x] = getf(f[x]);  // 递归查找并路径压缩
        return f[x];
    }
}

// 合并两个元素所在的集合
void merge(int x, int y) {
    int t1 = getf(x);   // 找到 x 的根
    int t2 = getf(y);   // 找到 y 的根
    if (t1 != t2)       // 如果不在同一集合，则合并
        f[t2] = t1;     // 将 t2 的根指向 t1
}

int main() {
    int T;  // 测试用例个数
    cin >> T;
    while (T--) {
        cin >> n >> h >> r;
        init();  // 初始化并查集
        
        // 读入每个空洞的球心坐标
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i] >> z[i];

        // 合并所有相交或相切的空洞
        // 两个空洞的距离 <= 2r 时相交或相切，即距离平方 <= 4r²
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                ll dx = x[i] - x[j];
                ll dy = y[i] - y[j];
                ll dz = z[i] - z[j];
                if (dx * dx + dy * dy + dz * dz <= 4 * r * r)
                    merge(i, j);  // 相交则合并
            }

        // 检查是否能从下表面走到上表面
        int ok = 0;  // 标志变量，0表示尚未连通，1表示已连通
        for (int i = 0; i < n && !ok; i++) {
            // 如果空洞与下表面相交或相切（球心 z <= r）
            if (z[i] <= r) {
                for (int j = 0; j < n && !ok; j++) {
                    // 如果空洞与上表面相交或相切（球心 z + r >= h）
                    // 并且两个空洞属于同一个连通块
                    if (z[j] + r >= h && getf(i) == getf(j))
                        ok = 1;  // 找到通路
                }
            }
        }
        // 输出结果
        cout << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}