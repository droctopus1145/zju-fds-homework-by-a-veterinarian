#include <stdio.h>

//graph algorithms
typedef struct graphnode* ptrtonode;//定义指向图节点的指针
struct graphnode{
    int vertex;
    int weight;
    ptrtonode next;
};//定义图节点

typedef struct{
    int size;
    ptrtonode* h;//储存邻接表的数组
}*graph;

graph initialize(int vertexnum)
{
    graph g;
    //将连接节点置空
    g->size=vertexnum;
    g->h=(ptrtonode*)malloc(vertexnum*sizeof(ptrtonode));
    for(int i=0;i<vertexnum;i++) g->h[i]=NULL;

    return g;
}

//topological sort
//被指向的顶点优先级更低，依赖指向它的顶点，所以要逐个删去入度为0的顶点，因为已经没有节点指向他们，也即他们已经没有依赖
//思路 扫描图后维护一个数组，记录每个顶点的入度。扫描该数组，当找到一个入度为0的点时，将其入度赋-1，输出并将其指向的顶点的入度均-1，继续扫描。
int find0(int* indegree,int size)
{
    for(int i=0;i<size;i++)
    {
        if(indegree[i]==0)
        {
            indegree[i]=-1;
            return i;//返回入度为0的节点值
        }
    }

    return -1;
}

void topsort(graph g)
{
    int indegree[g->size];
    //初始化indegree
    for(int i=0;i<g->size;i++) indegree[i]=0;
    for(int i=0;i<g->size;i++)
    {
        ptrtonode tmp=g->h[i];
        while(tmp!=NULL)
        {
            indegree[tmp->vertex]++;
            tmp=tmp->next;
        }
    }//完成扫描

    int count=g->size;
    while(count!=0)
    {
        int output;
        if((output=find0(indegree,g->size))>=0)
        {
            printf("%d ",output);
            count--;
            //更新邻接节点信息
            ptrtonode tmp1=g->h[output];
            while(tmp1!=NULL)
            {
                indegree[tmp1->vertex]--;
                tmp1=tmp1->next;
            }
        }   
        else//图中有环
        {
            printf("cycle\n");
            return;
        }
    }

}