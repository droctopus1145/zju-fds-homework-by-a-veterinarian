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
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
    //构建逆向图
    Graph G_reverse=(Graph)malloc(sizeof(struct GNode));
    G_reverse->Array=(PtrToVNode*)malloc(G->NumOfVertices*sizeof(PtrToVNode));
    for(int i=0;i<G->NumOfVertices;i++)
    {
        G_reverse->Array[i]=(PtrToVNode)malloc(sizeof(struct VNode));
        G_reverse->Array[i]->Next=NULL;//初始化邻接表，其中头节点为空
    }
    G_reverse->NumOfEdges=G->NumOfEdges;
    G_reverse->NumOfVertices=G->NumOfVertices;//初始化参数

    //开始转移边信息
    for(int i=0;i<G->NumOfVertices;i++)//遍历原表中每一个节点
    {
        PtrToVNode tmp1=G->Array[i];
        while(tmp1->Next!=NULL)//遍历完所有连接在这个节点上的节点
        {
            PtrToVNode tmp2=G_reverse->Array[tmp1->Next->Vert];//用于在逆向图中构建节点
            while(tmp2->Next!=NULL)
                tmp2=tmp2->Next;//遍历直到最后一个节点
            tmp2->Next=(PtrToVNode)malloc(sizeof(struct VNode));//为逆向图中的下一个节点分配内存
            tmp2->Next->Vert=G->Array[i]->Vert;
            tmp2->Next->Next=NULL;//完成逆向
            tmp1=tmp1->Next;//下一个连接在该节点上的节点
        }
    }

    //维护两个数组，一个用于记录正向图中节点的访问情况，一个用于记录逆向图中的节点访问情况
    int visited[G->NumOfVertices];
    int visited_reverse[G->NumOfVertices];
    for(int i=0;i<G->NumOfVertices;i++)
    {
        visited[i]=0;
        visited_reverse[i]=0;
    }//初始化

    //进行第一次dfs,将元素依次入队
    Vertex queue[100];
    int rear=0,front=0;//队列初始化

    //循环实现dfs-使用栈    
    int stack[100];
    int top=0;
    for(int i=0;i<G->NumOfVertices;i++)
    {
        if(visited[i]==0)//如果节点未访问--入栈
        {
            stack[top]=i;
            top++;
            while(top>0)
            {
                queue[rear]=stack[top-1];
                rear++;//栈顶元素入队列
                visited[stack[top-1]]=1;//将栈顶元素标记为已访问
                top--;//弹栈
                //将子节点加入栈
                PtrToVNode tmp=G->Array[stack[top]];
                while(tmp->Next!=NULL)
                {
                    stack[top]=tmp->Next->Vert;
                    top++;//子节点入栈
                    tmp=tmp->Next;//下一个子节点
                }
            }//完成第一次dfs，此时队列里应该已经存储了子生成树的顺序
            //在该子生成树中进行dfs，得到强连通分量
            int stack1[G->NumOfVertices+1];
            int top1=0;
            while(rear!=front)//逐一取出队列中的元素
            {
                if(visited_reverse[queue[front]]==0)
                {
                    stack1[top1]=queue[front];
                    top1++;
                    while(top1>0)
                    {
                        visit(stack1[top1-1]);//打印栈顶元素
                        visited_reverse[stack1[top1-1]]=1;//将栈顶元素标记为已访问
                        top1--;//弹栈
                        //将子节点加入栈
                        PtrToVNode tmp=G_reverse->Array[stack1[top1]];
                        while(tmp->Next!=NULL && visited[tmp->Next->Vert]==1)//判断visited是为了防止误入其他子树
                        {
                            stack1[top1]=tmp->Next->Vert;
                            top1++;//子节点入栈
                            tmp=tmp->Next;//下一个子节点
                        }
                    }
                    printf("\n");//换行
                }
                front++;//下一个队列元素
            }
        }
    }
}