#include <stdio.h>

// 判断是否为哈密顿回路的函数
int ifham(int list[][100], int* input, int max) 
{
    int i;
    int check[100] = {0}; // 记录每个点是否被访问过

    for (i = 0; i < max; i++) {
        // 判断两点之间是否有边，并且该点未被访问过
        if (list[input[i] - 1][input[i + 1] - 1] == 1 && check[input[i] - 1] == 0)
            check[input[i] - 1] = 1;
        else
            return 0;
    }

    // 判断是否回到了起点，构成回路
    if (input[max] == input[0])
        return 1;
    else
        return 0;
}

int main() {
    int nv, ne, i, j;

    // 读取顶点数和边数
    scanf("%d %d", &nv, &ne);

    int list[100][100] = {0}; // 邻接矩阵，最大支持 100 个顶点

    // 初始化邻接矩阵
    for (i = 0; i < ne; i++) 
    {
        int a, b;
        scanf("%d %d", &a, &b);
        list[a - 1][b - 1] = 1;
        list[b - 1][a - 1] = 1; // 无向图，对称边
    }

    int num; // 要判断的路径数量
    scanf("%d", &num);

    for (i = 0; i < num; i++) 
    {
        int num1;
        scanf("%d", &num1);

        // 哈密顿回路应该包含 nv+1 个顶点（首尾相同）
        if (num1 != nv + 1) 
        
        {
            printf("NO\n");
            // 跳过后续输入，进入下一个路径判断
            for (j = 0; j < num1; j++) {
                int temp;
                scanf("%d", &temp);
            }
            continue;
        }

        int input[101]; // 存储路径，最多 nv+1 个点
        for (j = 0; j < num1; j++)
            scanf("%d", &input[j]);

        if (ifham(list, input, nv) == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
