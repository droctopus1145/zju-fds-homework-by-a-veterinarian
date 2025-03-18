#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
typedef struct node *listptr;
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
}treenode;
struct node{
    ElementType Element;
    int index;
    Tree ptr;
};

void preorder(Tree);
Tree createtree(listptr elementtype,int num);


int main()
{
    Tree T1,T2;
    int num1,i,element,pindex;
    scanf("%d",&num1);
    listptr elementlist1=(listptr)malloc(num1*sizeof(struct node));
    for(i=0;i<num1;i++)
    {
        scanf("%d %d",&element,&pindex);
        elementlist1[i].Element=element;
        elementlist1[i].index=pindex;
    }
    T1=createtree(elementlist1,num1);
    int num2;
    scanf("%d",&num2);
    listptr elementlist2=(listptr)malloc(num2*sizeof(struct node));
    for(i=0;i<num2;i++)
    {
        scanf("%d %d",&element,&pindex);
        elementlist2[i].Element=element;
        elementlist2[i].index=pindex;
    }
    T2=createtree(elementlist2,num2);
    //完成树的重构
    int target;//目标数字
    scanf("%d",&target);
    //正常应该中序遍历后将排序后的数据录入数组，这里撒个懒，直接遍历，时间复杂度可能略高
    /*for(i=0;i<num1;i++)
    {

    }*/
    preorder(T1);
    printf("\n");
    preorder(T2);
    //printf("%d %d",T1,T2);
}

void preorder(Tree t)
{
    if(t==NULL) return;
    printf("%d ",t->Element);
    preorder(t->Left);
    preorder(t->Right);
}//先序遍历递归形式

//思路：当父节点索引为-1时为根节点，特殊处理，创建根节点并请求内存，将数据写入树的根节点，左右置空，将数据存储数组中的index+1代表现在自己的索引，并加入指向自己的指针
//当父节点不为-1时，创建节点并请求内存，利用索引在数据存储数组中找到父节点，将元素大小与父节点元素大小进行比对，如果此节点元素小于父节点元素，则存入父节点左子节点，更新索引，并加入指向自己的指针，反之存入右子节点，更新索引，并加入指向自己的指针
Tree createtree(listptr elementtype,int num)
{
    
    int i;
    Tree root=(Tree)malloc(sizeof(struct TreeNode));//创建根节点并为其申请内存
    root->Left=root->Right=NULL;//左右节点置空
    root->Element=0;
    for(i=0;i<num;i++)//一共num个节点需要添加到树中
    {
        if(elementtype[i].index==-1)//如果是根节点
        {
            root->Element=elementtype[i].Element;
            elementtype[i].index++;//索引变为根节点索引0
            elementtype[i].ptr=root;//在数据储存数组中加入根节点指针
        }
        else
        {
            Tree tmp=(Tree)malloc(sizeof(struct TreeNode));//创建当前节点并为其申请内存
            tmp->Left=tmp->Right=NULL;
            tmp->Element=elementtype[i].Element;
            int j;
            for(j=0;j<i;j++)//查找父节点
            {
                if(elementtype[j].index==elementtype[i].index)
                    break;//找到后退出循环
            }
            if(elementtype[i].Element<=elementtype[j].Element)//当前节点元素值小于等于父节点元素值
            {
                elementtype[j].ptr->Left=tmp;//父节点左子节点指向当前节点
                elementtype[i].index=i;//当前节点在数据存储
                elementtype[i].ptr=tmp;   
            }
            else
            { 
                elementtype[j].ptr->Right=tmp;
                elementtype[i].index=i;
                elementtype[i].ptr=tmp;
            }
        }
    }
    
    return root;
}