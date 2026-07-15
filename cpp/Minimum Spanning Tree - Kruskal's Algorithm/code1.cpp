#include<iostream>
#include<algorithm>

using namespace std;
const int maxn = 2e5 + 5;

struct edge {
    int p1, p2, d;  // 在 p1 和 p2 之间长度为 d 的边
} ed[maxn];

bool operator<(const edge &a, const edge &b) {
    return a.d < b.d;
}

int f[maxn];  // 并查集数组

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++)
        f[i] = i;
}

// 查找祖先（路径压缩）
int getf(int x) {
    if (f[x] == x)
        return x;
    else {
        f[x] = getf(f[x]);
        return f[x];
    }
}

// 合并两个元素所在的集合
void merge(int x, int y) {
    int t1 = getf(x);
    int t2 = getf(y);
    if (t1 != t2)
        f[t2] = t1;  // 将 t2 的父节点设为 t1
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= m; i++) {
        cin >> ed[i].p1 >> ed[i].p2 >> ed[i].d;
    }
    
    // 将所有边按权值从小到大排序
    sort(ed + 1, ed + m + 1);
    
    init(n);  // 初始化并查集
    
    int ans = 0, cnt = 0;  // ans: 最小生成树总权值, cnt: 已选边数
    for (int i = 1; i <= m; i++) {
        int p1 = ed[i].p1;
        int p2 = ed[i].p2;
        if (getf(p1) != getf(p2)) {  // 加入该边不会形成环
            ans += ed[i].d;
            cnt++;
            merge(p1, p2);  // 合并两个连通分量
        }
    }
    
    if (cnt == n - 1) {
        cout << ans << endl;
    } else {
        cout << "orz" << endl;
    }
    
    return 0;
}