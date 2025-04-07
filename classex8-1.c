#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */

//先扫描一遍图，创建一个新的结构体数组记录每个节点的入度
//遍历输入数组：看看是不是入度为0，如果是，将下游节点的入度-1；如果不是，说明该数组不是拓扑排序
bool IsTopSeq( LGraph Graph, Vertex Seq[])
{
    int indegree[MaxVertexNum];
    int i;
    for(i=0;i<MaxVertexNum;i++)
        indegree[i]=0;
    for(i=0;i<Graph->Nv;i++)
    {
        PtrToAdjVNode tmp=Graph->G[i].FirstEdge;//tmp为指向首节点的邻接节点的指针
        while(tmp!=NULL)
        {
            indegree[tmp->AdjV-1]++;//将被指向节点的indegree+1
            tmp=tmp->Next;
        }
    }//完成对每个节点入度的存储

    for(i=0;i<Graph->Nv;i++)//开始遍历输入数组
    {
        if(indegree[Seq[i]-1]==0)//如果输入对应的indegree为0
        {
            PtrToAdjVNode ptr=Graph->G[Seq[i]-1].FirstEdge;
            while(ptr!=NULL)
            {
                indegree[ptr->AdjV-1]--;//将下游节点的入度-1
                ptr=ptr->Next;
            }
        }
        else//如果不是0，输出false
            return false;
    }
    return true;
}