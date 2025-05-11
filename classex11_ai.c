#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */

//将图逆向
//先进行一波先序遍历版的dfs，对每个子树，将元素存入队列；出队后在该子树内进行先序遍历版的dfs
void StronglyConnectedComponents(Graph G,void (*visit)(Vertex V))
{
    //构建逆向图
    Graph G_reverse=(Graph)malloc(sizeof(struct GNode));
    G_reverse->Array=(PtrToVNode *)malloc(G->NumOfVertices * sizeof(PtrToVNode));
    for(int i=0;i<G->NumOfVertices;i++)
    {
        G_reverse->Array[i]=(PtrToVNode)malloc(sizeof(struct VNode));
        G_reverse->Array[i]->Vert=i;              
        G_reverse->Array[i]->Next=NULL;
    }
    G_reverse->NumOfEdges=G->NumOfEdges;
    G_reverse->NumOfVertices=G->NumOfVertices;

    for(int i=0;i<G->NumOfVertices;i++)
    {
        PtrToVNode tmp1=G->Array[i]->Next;        
        while(tmp1!=NULL)
        {
            // 将边tmp1->Vert->z加入逆向图
            PtrToVNode newNode=(PtrToVNode)malloc(sizeof(struct VNode));
            newNode->Vert=i;
            newNode->Next=G_reverse->Array[tmp1->Vert]->Next;
            G_reverse->Array[tmp1->Vert]->Next=newNode;
            tmp1=tmp1->Next;
        }
    }

    //初始化访问数组
    int visited[G->NumOfVertices];
    int visited_reverse[G->NumOfVertices];
    for(int i=0;i<G->NumOfVertices;i++)
    {
        visited[i]=0;
        visited_reverse[i]=0;
    }

    //拓扑序栈
    Vertex stack_out[G->NumOfVertices];
    int out_top=0;

    //正向 DFS，获得后序序列（非递归）
    int stack[G->NumOfVertices];
    int top=0;
    for(int i=0;i<G->NumOfVertices;i++)
    {
        if(visited[i]==0)
        {
            stack[top++]=i;
            while(top>0)
            {
                int v=stack[--top];
                if(visited[v])
                    continue;
                visited[v]=1;
                stack_out[out_top++]=v;  

                PtrToVNode tmp=G->Array[v]->Next;
                while(tmp!=NULL)
                {
                    if(!visited[tmp->Vert])
                        stack[top++]=tmp->Vert;
                    tmp=tmp->Next;
                }
            }
        }
    }

    //第二次DFS按stack_out的逆序遍历
    for(int i=out_top-1;i>=0;i--)
    {
        int v=stack_out[i];
        if(visited_reverse[v]==0)
        {
            //对当前强连通分量执行DFS
            int stack2[G->NumOfVertices];
            int top2 = 0;
            stack2[top2++]=v;

            while(top2>0)
            {
                int u=stack2[--top2];
                if(visited_reverse[u])
                    continue;
                visited_reverse[u]=1;
                visit(u);

                PtrToVNode tmp=G_reverse->Array[u]->Next;
                while(tmp!=NULL)
                {
                    if(!visited_reverse[tmp->Vert])
                        stack2[top2++] = tmp->Vert;
                    tmp=tmp->Next;
                }
            }
            printf("\n"); 
        }
    }
}
