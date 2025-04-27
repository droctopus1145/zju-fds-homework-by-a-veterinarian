#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 1000000

int graph[1000][1000];//存储初始图和接下来的残差图，矩阵元素为边权重
int parent[1000];
int visited[1000];
int nodenum=0;//记录节点数量
char names[1000][4];//记录节点名称

int get_id(char* name)
{
    for(int i=0;i<nodenum;i++)
    {
        if(strcmp(names[i],name)==0)
            return i;//如果字符串已经存在，不再为其分配id并返回其原有id
    }
    strcpy(names[nodenum],name);//将新字符串添加到列表中，赋予其id
    return nodenum++;//返回新字符串的id值
}

int bfs(int s,int t)//使用bfs确定是否连通
{
    for(int i=0;i<nodenum;i++)
    {
        parent[i]=-1;//所有节点的前驱节点都设置为无
        visited[i]=0;//所有点都是未访问状态
    }

    int queue[1000];
    int front=0;
    int rear=0;  
    queue[rear++]=s;//源节点入队
    visited[s]=1;//将源节点标记为已经访问

    while(front<rear)//当栈内还有数字就继续循环
    {
        int u=queue[front++];//首元素出队
        for(int v=0;v<nodenum;v++)
        {
            if(visited[v]==0 && graph[u][v]>0)
            {
                parent[v]=u;//设置前驱节点
                visited[v]=1;//此节点标记为已访问
                if(v==t)//找到了
                    return 1;
                queue[rear++]=v;//如果不是，该节点入队
            }    
        }
    }

    return 0;//没找到
}

int caculate(int s,int t)//最大流算法
{
    int result=0;
    while(bfs(0,1))
    {
        int increment=INF;//初始化单次增加流（方便比较）

        for(int v=t;v!=s;v=parent[v])//寻找瓶颈，从终点回溯
        {
            int u=parent[v];
            if(graph[u][v]<increment)
                increment=graph[u][v];
        }

        for(int v=t;v!=s;v=parent[v])
        {
            int u=parent[v];
            graph[u][v]-=increment;//可用流量减少
            graph[v][u]+=increment;//流量增加（反向流增加）
        }
    }

    for(int v=0;v<nodenum;v++)
        result+=graph[t][v];
    
    return result;
}

int main()
{
    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<1000;j++)
        {
            graph[i][j]=0;//初始化图，此时每个节点之间都被赋0，也就是说每个卫星间的流量为0，全部断联
        }
    }
    char s[4],t[4];
    int n;
    scanf("%s %s %d",s,t,&n);

    int sid=get_id(s);
    int tid=get_id(t);//读取起始点名称并赋id

    for(int i=0;i<n;i++)//读取交通信息
    {
        char a[4],b[4];
        int c;
        scanf("%s %s %d",a,b,&c);
        int u=get_id(a);
        int v=get_id(b);

        graph[u][v]=c;
    }

    printf("%d",caculate(sid,tid));
}