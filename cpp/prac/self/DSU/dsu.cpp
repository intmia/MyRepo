#include <iostream>
using namespace std;

const int MAXN = 200005; // 最大元素个数，视题目约束可调整

// 并查集结构体
struct DSU {
    int n;
    int parent[MAXN]; // parent[i] 表示 i 的父节点
    int rankv[MAXN];  // rankv[i] 表示以 i 为根的树的近似高度

    DSU(int size) : n(size) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; // 初始时每个节点的父节点是自己
            rankv[i] = 0; // 初始时秩为 0
        }
    }

    // 查找操作：返回 x 所属集合的代表元，并进行路径压缩
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并操作：将 x 和 y 所在集合合并
    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            return false; // 已经在同一个集合中，无需合并
        }
        // 按秩合并：将高度低的树挂到高度高的树下面
        if (rankv[rx] < rankv[ry]) {
            parent[rx] = ry;
        } else if (rankv[rx] > rankv[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rankv[rx] += 1;
        }
        return true;
    }

    // 判断 x 和 y 是否属于同一个集合
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    // 输入格式：n q，表示元素个数和操作数
    // 接下来 q 行，每行包含 3 个整数：type x y
    // type = 1 表示合并 x y，type = 2 表示查询 x y 是否在同一集合
    if (!(cin >> n >> q)) {
        return 0;
    }

    DSU dsu(n);
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            dsu.unite(x, y);
        } else if (type == 2) {
            cout << (dsu.same(x, y) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
