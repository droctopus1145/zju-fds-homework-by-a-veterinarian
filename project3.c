#include <stdio.h>
#define INF 100000000
struct nodeinfo{
    int visit;//是否被访问过
    int dis;//节点到源的距离
};

//分析传入的邻接矩阵和数组，判断是否为dijkstra序列，是的话返回1，不是返回0
int if_dijkstra(int nodenum,int** graph,int* sequence)
{
    struct nodeinfo info[nodenum];//用于储存节点信息
    for(int i=1;i<nodenum;i++)
    {

    }
}

int main()
{
    int nodenum;//节点数
    int edgenum;//边数
    scanf("%d %d",&nodenum,&edgenum);
    int** graph =(int **)malloc(nodenum*sizeof(int*));
    for (int i = 0; i < 1000; i++)
        graph[i] = malloc(nodenum*sizeof(int));//创建邻接矩阵
    for(int i=0;i<edgenum;i++)
    {
        int s;//起点
        int t;//止点
        int n;//边权重
        scanf("%d %d %d",&s,&t,&n);
        graph[s-1][t-1]=n;
    }
    int seqnum;//需要判断的序列数量
    scanf("%d",&seqnum);
    for(int i=0;i<seqnum;i++)
    {
        int sequence[nodenum];//创建数组
        for(int j=0;j<nodenum;j++)
            scanf("%d",&sequence[j]);//逐个输入
        //判断是否为dijkstra序列
        if(if_dijkstra(nodenum,graph,sequence))//判断是否为dijkstra序列，是的话输出Yes，不是的话输出No
            printf("Yes");
        else
            printf("No");

    }
}