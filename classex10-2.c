#include <stdio.h>

#define INF 100000000



//如果只有单个mst就输出其权值和，如果有多个mst就返回-n,其中n为已经连接的节点数量,如果不连通，返回0
int if_connect(int** graph,int nodenum,int s)//读入二维数组指针，和节点数
{
    //检查连通性
    
    int visited[nodenum];
    for(int i=0;i<nodenum;i++)
        visited[i]=0;//全部初始化为0，未访问

    int queue[500];//设置队列，使用bst检验连通性
    int front=0;
    int rear=0;
    queue[rear++]=s;//s入队
    visited[s]=1;

    int connectnum=1;

    while(front<rear)
    {
        int u=queue[front++];//首元素出队
        for(int v=0;v<nodenum;v++)
        {
            if(graph[u][v]>0 && !visited[v])//如果连接存在且节点未被访问
            {
                queue[rear++]=v;//将子节点入队
                graph[u][v]=graph[u][v];//标记为已访问
                graph[v][u]=graph[v][u];//反向也要处理
                visited[v]=1;
                printf("%d %d\n",u,v);
                connectnum++;//入队数加一
            }
        }
    }
    
    if(connectnum<nodenum)
    {

    }
    else
        return 1;
}

int main()
{
    int nodenum,edgenum;
    scanf("%d %d",&nodenum,&edgenum);
    int** graph =(int **)malloc(1000 * sizeof(int*));
    for (int i = 0; i < 1000; i++)
        graph[i] = malloc(1000 * sizeof(int));//使用邻接矩阵表示图
    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<1000;j++)
        {
            graph[i][j]=0;
        }
    }
    int lestweight=INF;
    int first=0;
    for(int i=0;i<edgenum;i++)//读入边的信息
    {
        int s,t,n;
        scanf("%d %d %d",&s,&t,&n);
        graph[s][t]=n;//注意是无向图，不想后面再比较大小所以这里两条边都存上
        graph[t][s]=n;//置为负数，方便后面判断是否被访问
        if(n < lestweight)
        {
            lestweight=n;
            first=s;
        }    
    }//完成读入

    int connect=if_connect(graph,nodenum,first);
    if(connect<0)
    {
        printf("No MST\n");
        printf("%d",-connect);
    }

}