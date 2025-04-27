#include <stdio.h>

#define INF 100000000


void bfs(int* visited,int nodenum,int** graph,int s)
{
    int queue[500];//设置队列，使用bst检验连通性
    int front=0;
    int rear=0;
    queue[rear++]=s;//s入队
    visited[s]=1;

    while(front<rear)
    {
        int u=queue[front++];//首元素出队
        for(int v=1;v<nodenum+1;v++)
        {
            if(graph[u][v]>0 && !visited[v])//如果连接存在且节点未被访问
            {
                queue[rear++]=v;//将子节点入队
                graph[u][v]=graph[u][v];
                graph[v][u]=graph[v][u];//反向也要处理
                visited[v]=1;//标记为已访问
                //printf("%d %d\n",u,v);
            }
        }
    }
}

//如果只有单个mst就输出其权值和，如果有多个mst就返回-n,其中n为已经连接的节点数量,如果不连通，返回0
int if_connect(int** graph,int nodenum,int s)//读入二维数组指针，和节点数
{
    //检查连通性
    
    int visited[nodenum+1];
    for(int i=1;i<=nodenum;i++)
        visited[i]=0;//全部初始化为0，未访问

    bfs(visited,nodenum,graph,s);
    int componentsnum=1;
    for(int i=1;i<=nodenum;i++)
    {
        if(visited[i]==0)
        {
            bfs(visited,nodenum,graph,i);
            componentsnum++;
        }
    }
    //printf("%d",componentsnum);
    
    return componentsnum;   
}

//当只有唯一的最小生成树时，返回正值的权值和，当有多个最小生成树时，返回负值的权值和
int caculate(int** graph,int nodenum) 
{
    int visited[501]={0};
    int low[501];
    int count_same[501]; // 用于检测同一权重边的个数
    int total_weight=0;
    int is_unique=1;

    for(int i=1;i<=nodenum;i++) 
    {
        low[i]=INF;
        count_same[i]=0;
    }
    low[1]=0; // 从1号点开始

    for(int i=1;i<=nodenum;i++) {
        int u=-1;
        int min=INF;
        for(int j=1; j<=nodenum;j++) 
        {
            if(!visited[j] && low[j]<min) 
            {
                min=low[j];
                u=j;
            }
        }

        if(u==-1) break;

        visited[u] = 1;
        total_weight+=low[u];

        // 检查是否有多个等价边
        if(count_same[u]>1)
            is_unique=0;

        for(int v=1;v<=nodenum;v++) 
        {
            if(!visited[v] && graph[u][v]>0) 
            {
                if(graph[u][v]<low[v]) 
                {
                    low[v]=graph[u][v];
                    count_same[v]=1;
                }else if(graph[u][v]==low[v]) 
                {
                    count_same[v]++;
                }
            }
        }
    }

    return is_unique?total_weight:-total_weight;
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
    int sum=caculate(graph,nodenum);
    if(connect>1)
    {
        printf("No MST\n");
        printf("%d",connect);
    }
    else
    {
        if(sum>0)
        {
            printf("%d\n",sum);
            printf("Yes");
        } 
        else
        {
            printf("%d\n",-sum);
            printf("No");
        }   
    }

}