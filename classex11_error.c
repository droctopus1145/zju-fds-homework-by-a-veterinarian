//实际是一个寻找环的算法
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

//使用一个结构数组记录节点访问情况，前驱节点
//bfs遍历，如果遍历到有节点的子节点为源节点。停止遍历并逐个打印前驱节点至源节点
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
    struct info{
        int if_visit;
        Vertex father;
    };

    struct info list[G->NumOfVertices];//创建一个存储节点信息的结构数组

    for(int i=0;i<G->NumOfVertices;i++)
    {
        list[i].if_visit=0;//初始化结构数组
    }

    for(int i=0;i<G->NumOfVertices;i++)//对每个节点进行遍历
    {
        //从该节点开始进行bfs
        int queue[1000];
        int rear=0,front=0;//创建栈

        //首元素入栈
        queue[rear]=G->Array[i]->Vert;
        rear++;

        //flag标记是否找到强连通
        int flag=0;

        while(rear!=front)//当栈中还有元素
        {
            //判断栈顶元素是否为源节点
            if(queue[front]==G->Array[i]->Vert)
            {
                //如果是，开始遍历前驱节点直到源节点，并标记所有经过的节点为已经访问
                Vertex tmp=queue[front];
                while(list[tmp].father!=G->Array[i]->Vert)//如果当前节点的前驱节点不是源节点
                {
                    list[tmp].if_visit=1;//标记为已访问
                    visit(tmp);
                    tmp=list[tmp].father;
                }
                printf("\n");
                flag=1;
            }
            else
            {
                //如果不是，将其未访问的子节点加入栈
                PtrToVNode tmp=G->Array[queue[front]];
                front++;//弹栈
                while(tmp->Next!=NULL)//遍历
                {
                    if(list[tmp->Vert].if_visit=0)
                    {
                        queue[rear]=tmp->Vert;
                        rear++;
                    }//未访问的子节点入栈

                    tmp=tmp->Next;
                }
            }
        }

        if(flag==0)
            printf("%d\n",i);
        
    }
        
    
}