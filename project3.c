#include <stdio.h>
#define INF 100000000
struct nodeinfo{
    int visit;//是否被访问过，0为未访问，1为访问过
    int dis;//节点到源的距离
};

//分析传入的邻接矩阵和数组，判断是否为dijkstra序列，是的话返回1，不是返回0
int if_dijkstra(int nodenum,int** graph,int* sequence)
{
    struct nodeinfo info[nodenum];//用于储存节点信息
    for(int i=0;i<nodenum;i++)//初始化节点信息数组-dis全部设置为INF，visit全部设置为0
    {
        info[i].dis=INF;
        info[i].visit=0;
    }
    //第一个节点单独处理
    info[sequence[0]-1].dis=0;
    for(int i=0;i<nodenum;i++)
    {
        int least=info[sequence[i]-1].dis;//到源最小距离预设为序列中节点到源的距离
        int leastnode=sequence[i];
        for(int j=0;j<nodenum;j++)
        {
            //第一遍扫描，找到距离源最近的点
            if(info[j].dis<least && !info[j].visit)
            {
                //printf("%d",j);
                return 0;//如果在该步骤有节点到源距离小于序列中节点的，直接返回不是
            }
                
        }
        info[leastnode-1].visit=1;
        for(int j=0;j<nodenum;j++)
        {
            //第二次扫描，更新连接的节点到源的距离
            if(!info[j].visit && info[leastnode-1].dis+graph[leastnode-1][j]<info[j].dis)//如果该节点未被访问且前一节点到源的距离加上两节点之间的距离小于该节点之前储存的到源的距离
                info[j].dis=info[leastnode-1].dis+graph[leastnode-1][j];
        }
    }

    return 1;
}

int main()
{
    int nodenum;//节点数
    int edgenum;//边数
    scanf("%d %d",&nodenum,&edgenum);
    int** graph =(int **)malloc(nodenum*sizeof(int*));
    for (int i = 0; i < nodenum; i++)
        graph[i] = malloc(nodenum*sizeof(int));//创建邻接矩阵
    for (int i = 0; i < nodenum; i++) {
        graph[i] = (int *)malloc(nodenum * sizeof(int));
        for (int j = 0; j < nodenum; j++)
            graph[i][j] = INF; // 初始化所有边为INF
    }
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
            printf("Yes\n");
        else
            printf("No\n");

    }
}