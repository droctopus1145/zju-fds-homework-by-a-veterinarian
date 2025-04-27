#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000          // 最大节点数（足够大）
#define INF 100000000      // 一个足够大的数，表示“无穷大”

// 图的邻接矩阵表示法，capacity[u][v] 是 u -> v 的容量
int capacity[MAXN][MAXN];  // 存储原始边容量
int flow[MAXN][MAXN];      // 当前边上的流量
int parent[MAXN];          // 用于 BFS，记录路径上的父节点
int visited[MAXN];         // 用于 BFS，标记是否访问过
int node_count = 0;        // 当前已添加的节点总数

char names[MAXN][4];       // 存储所有节点的名称（3位大写 + '\0'）

// 将字符串形式的节点名映射为整数 ID
int get_id(char *name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(names[i], name) == 0)
            return i;
    }
    strcpy(names[node_count], name);
    return node_count++;
}

// 使用 BFS 寻找从 s 到 t 的一条增广路径
int bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));

    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = 1;

    // 标准 BFS 遍历
    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < node_count; v++) {
            // 如果 v 还未访问，且 u->v 有剩余容量
            if (!visited[v] && capacity[u][v] > flow[u][v]) {
                parent[v] = u;       // 记录 v 的父节点是 u
                visited[v] = 1;
                if (v == t) return 1; // 找到增广路径，直接返回
                queue[rear++] = v;
            }
        }
    }
    return 0;  // 无增广路径
}

// Edmonds-Karp 算法主体
int edmonds_karp(int s, int t) {
    int max_flow = 0;

    // 每次找到一条增广路径，就进行一次增流
    while (bfs(s, t)) {
        int increment = INF;

        // 回溯路径，找到瓶颈容量（最小残余容量）
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int residual = capacity[u][v] - flow[u][v];
            if (residual < increment)
                increment = residual;
        }

        // 再次回溯路径，更新正向边与反向边的流量
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += increment;   // 正向边流量增加
            flow[v][u] -= increment;   // 反向边流量减少（用于回退）
        }

        max_flow += increment;  // 统计总流量
    }

    return max_flow;
}

int main() {
    char sname[4], tname[4];  // 源点与汇点的名称（3个字符）
    int n;

    scanf("%s %s %d", sname, tname, &n);  // 读取输入
    int s = get_id(sname);               // 将源点名称映射为整数 ID
    int t = get_id(tname);               // 同理处理终点

    // 读取每一条边的信息
    for (int i = 0; i < n; i++) {
        char a[4], b[4];
        int c;
        scanf("%s %s %d", a, b, &c);
        int u = get_id(a);
        int v = get_id(b);
        capacity[u][v] += c;   // 注意：允许存在多条边，容量相加
    }

    // 计算最大流并输出
    int ans = edmonds_karp(s, t);
    printf("%d\n", ans);
    return 0;
}

