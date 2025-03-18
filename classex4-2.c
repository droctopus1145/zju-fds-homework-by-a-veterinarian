#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
}treenode;
void zprint(Tree tree,int num);
Tree remaketree(int* inorder,int* postorder,int indexleft,int indexright,int index);
    
int main()
{
    //先重构树，再之字形打印
    int num,i;
    scanf("%d",&num);
    int inorder[num];//中序
    int postorder[num];//后序
    for(i=0;i<num;i++)
        scanf("%d",&inorder[i]);
    for(i=0;i<num;i++)
        scanf("%d",&postorder[i]);
    zprint(remaketree(inorder,postorder,0,num-1,num-1),num);
}

void zprint(Tree tree,int num)
{
    int count =num;
    Tree queue[1000];//广度优先搜索
    int front = 0;
    int rear = 0;
    queue[rear]=tree;//处理第一层（root）的特殊情况
    rear++;
    
    int flag=0;//控制打印方向，0表示反向

    while(front < rear)
    {
        //后一层元素入队，前一层元素（入栈）打印，前一层元素出队
        if(flag==0)//如果此层需要反向打印
        {
            Tree stack[1000];//创建栈（反向层父节点进栈，后出栈实现反向打印）
            int top=-1; 
            int size=rear-front;
            int i;
            for(i=0;i<size;i++)
            {
                if(queue[front]->Left)
                {
                    queue[rear]=queue[front]->Left;
                    rear++;
                }

                if(queue[front]->Right)
                {
                    queue[rear]=queue[front]->Right;
                    rear++;
                }
                top++;
                stack[top]=queue[front];
                front++;
            }//完成入队、出队与入栈
            //准备依序出栈
            for(i=0;i<size;i++)
            {
                if(count>1)
                    printf("%d ",stack[top]->Element);
                else
                    printf("%d",stack[top]->Element);
                count--;
                top--;
            }
            flag=1;//反转打印方向  
        }
        else
        {
            int size=rear-front;
            int i;
            for(i=0;i<size;i++)
            {
                if(queue[front]->Left)//检查是否为空指针，防止程序崩溃
                {
                    queue[rear]=queue[front]->Left;
                    rear++;
                }

                if(queue[front]->Right)//检查是否为空指针，防止程序崩溃
                {
                    queue[rear]=queue[front]->Right;
                    rear++;
                }
                if(count>1)
                    printf("%d ",queue[front]->Element);
                else
                    printf("%d",queue[front]->Element);
                count--;
                front++;
            }//完成入队、出队打印
            flag=0;//反转打印方向
        }
    }
}

Tree remaketree(int* inorder,int* postorder,int indexleft,int indexright,int index)
{
    if (index < 0 || indexleft > indexright) return NULL;
    Tree root = (Tree)malloc(sizeof(struct TreeNode));

    root->Element=postorder[index];
    int i;
    for(i=indexleft;i<=indexright;i++)
    {
        if(inorder[i]==postorder[index])
            break;
    }
    root->Right = remaketree(inorder, postorder, i + 1, indexright, index - 1);
    root->Left = remaketree(inorder, postorder, indexleft, i - 1, index-(indexright-i)-1);

    return root;
}
    