#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXM 250001

// 边结构体
typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];     // 存储所有边
int parent[MAXN];     // 并查集数组
int n, m;             // 顶点数，边数

// 并查集查找
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); // 路径压缩
    return parent[x];
}

// 并查集合并
int unite(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) return 0; // 已经在同一个集合里了
    parent[ra] = rb;
    return 1; // 合并成功
}

// 按边权升序排序函数
int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    scanf("%d %d", &n, &m);

    // 读入边
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    // 初始化并查集
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    // 按边权排序
    qsort(edges, m, sizeof(Edge), cmp);

    int mst_weight = 0;  // MST总权重
    int mst_edges = 0;   // 已加入MST的边数量
    int unique = 1;      // 标记MST是否唯一，初始为是

    // Kruskal 主过程
    for (int i = 0; i < m;) {
        int j = i;
        // 将权重相同的边分组
        while (j < m && edges[j].w == edges[i].w)
            j++;

        // 记录本轮可连接的边
        Edge temp[MAXN];
        int temp_count = 0;

        // 检查哪些边可用于连接不同集合
        for (int k = i; k < j; k++) {
            if (find(edges[k].u) != find(edges[k].v))
                temp[temp_count++] = edges[k];
        }

        // 如果有超过1条边可选，就可能存在多种构造方式
        if (temp_count > 1)
            unique = 0;

        // 选出用于构建MST的边
        for (int k = 0; k < temp_count; k++) {
            if (unite(temp[k].u, temp[k].v)) {
                mst_weight += temp[k].w;
                mst_edges++;
            }
        }

        i = j; // 继续处理下一组边权
    }

    // 判断是否构成了 MST
    if (mst_edges == n - 1) {
        printf("%d\n", mst_weight);
        printf("%s\n", unique ? "Yes" : "No");
    } else {
        // 没有构成MST，说明图不连通
        int components = 0;
        for (int i = 1; i <= n; i++) {
            if (find(i) == i)
                components++;
        }
        printf("No MST\n%d\n", components);
    }

    return 0;
}
