#include <stdio.h>
#define MaxVertexNum 100
//graph algorithms
typedef struct graphnode* ptrtonode;//定义指向图节点的指针
struct graphnode{
    int vertex;
    int weight;
    ptrtonode next;
};//定义图节点

typedef struct{
    int size;
    ptrtonode* h;//储存邻接表的数组(数组储存的是指向邻接节点的指针)
}*graph;
//shortest path algorithm
//unweighted-bfs
typedef struct TableEntry {
    int Known;     // 标记顶点是否已被处理（true/false）
    int Dist;       // 顶点到起点的最短距离（初始为 Infinity/-1）
    int Path;    // 最短路径上的前驱顶点（通常用顶点编号表示）
} TableEntry;

//表在使用前先初始化，将所有顶点设为未访问，初始距离设为无限大，前驱节点设为-1（无效值），再将起点距离设为0

typedef TableEntry Table[MaxVertexNum]; // Table 是 TableEntry 的数组
//使用遍历搜索当前层级的节点，搜索复杂度为O（n），要在搜索到节点后更新邻接节点的部分信息，以供下一次检索
void unweighted(Table t,graph g)
{
    int currentdist;//当前节点距离源节点的距离

    //按照距离从大到小逐层处理
    for(currentdist=0;currentdist<g->size;currentdist++)
    {
        for(int i=0;i<g->size;i++)//遍历每一个节点以寻找在当前距离的节点
        {
            if(t[i].Known==0 && t[i].Dist==currentdist)
            {
                t[i].Known=1;//将节点标记为已访问，其实无必要（前驱节点和路径长度已标记（由于第一个节点无需标记前驱节点，且路径长度已标记，所以将这两个部分挪到后面操作））
                ptrtonode tmp=g->h[i];
                while(tmp!=NULL)
                {
                    //将所有邻接节点标记前驱节点和路径长度
                    if(t[tmp->vertex].Dist>currentdist+1)//如果从前驱节点到这个节点的路径长度小于已记录的路径长度
                    {
                        t[tmp->vertex].Dist=currentdist+1;
                        t[tmp->vertex].Path=i;
                        tmp=tmp->next;//移动指针到下一个
                    }
                }
            }
        }
    }
}

//更精炼的算法--使用队列
void unweighted(Table t,graph g)
{
    int queue[MaxVertexNum];
    int rear=0;
    int front=0;

    //让源节点入队，开始循环：将元素出队，并标记为已访问，再将所有邻接的未访问的节点入队
    for(int i=0;i<g->size;i++)
    {
        if(t[i].Dist==0)
        {
           queue[rear]=i;
           rear++;
        }
    }

    while(rear!=front)
    {
        int tmp=queue[front];
        t[tmp].Known=1;//其实无必要
        front++;//出队

        //开始处理邻接节点
        ptrtonode tmpptr=g->h[tmp];
        while(tmpptr!=NULL)
        {
            if(t[tmpptr->vertex].Dist<t[tmp].Dist)
                continue;
            queue[rear]=tmpptr->vertex;
            rear++;
            t[tmpptr->vertex].Dist=t[tmp].Dist+1;
            t[tmpptr->vertex].Path=tmp;
            tmpptr=tmpptr->next;
        }
    }
}

//Dijkstra--有权图（权为正）
void dijskstra(Table t,graph g)
{
    int startvertex;
    for(int i=0;i<g->size;i++)
    {
        if(t[i].Dist==0)
        {
            startvertex==i;
            break;
        }
    }//找到起始节点
    for(int count=0;count<g->size;count++)
    {
        int mindist=MaxVertexNum;
        int v=-1;
        for(int i=0;i<g->size;i++)
        {
            if(!t[i].Known && t[i].Dist<mindist)
            {
                mindist=t[i].Dist;
                v=i;
            }
        }//遍历所有顶点寻找未处理的最小距离节点
        if(v==-1) break;//剩余顶点不可达，可以提前结束

        t[v].Known=1;//当前节点标记为已处理
        //准备更新当前节点邻接节点的距离
        ptrtonode tmp=g->h[v];
        while(tmp!=NULL)
        {
            if(!t[tmp->vertex].Known)//当且仅当该节点是未被操作过时尝试更新距离
            {
                if(t[tmp->vertex].Dist>mindist+tmp->weight)//当原来存在的距离大于从当前节点出发的路径时，更新距离
                {
                    t[tmp->vertex].Dist=mindist+tmp->weight;
                    t[tmp->vertex].Path=v;
                }
            }
            tmp=tmp->next;//移到下一个邻接节点
        }
    }   
}//也可以使用队列实现

//存在负权的图
void nagetiveweighted(Table t,graph g)
{
    int queue[MaxVertexNum];
    int front=0;
    int rear=0;//完成队列的初始化
    int startvertex;
    for(int i=0;i<g->size;i++)
    {
        if(t[i].Dist==0)
        {
            startvertex=i;
            break;
        }
    }//找到起始节点
    queue[rear++]=startvertex;
    while(rear!=front)
    {
        //出队当前的节点，将所有邻接节点更新距离和前驱节点后加入队列
        ptrtonode tmp=g->h[queue[front]];
        while(tmp!=NULL)
        {
            if(t[tmp->vertex].Dist>t[queue[front]].Dist+tmp->weight)
            {
                t[tmp->vertex].Dist=t[queue[front]].Dist+tmp->weight;
                t[tmp->vertex].Path=queue[front];
            }
            int flag=0;
            for(int i=front+1;i<rear;i++)//为不造成过多资源浪费，已在队列内的元素不再入队
            {
                if(queue[i]==tmp->vertex)
                {
                    flag=1;
                    break;
                }
            } 
            if(!flag) queue[rear++]=tmp->vertex;
            tmp=tmp->next;
        }
        front++;//当前节点出队
    }
}//这里使用了线性扫描来确定队列中是否已存在某元素，也可以用数组记录元素是否在队列中，复杂度更低
//当出现原点可达的负权环时，会由于不断循环负权环（使最小距离不断减小）而使程序崩溃
//增加入队计数器，当某节点入队次数超过节点数时可以判定图中有负权环

//network flow problems--求最大流
//minimum spanning tree--最小生成树
//prim's algorithm--similar to dijkstra
//kruskal's algorithm
//DFS--寻找割点--按dfs顺序标记



