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
    preorder(T2);
    //printf("%d %d",T1,T2);
}

void preorder(Tree t)
{
    if(t==NULL) return;
    printf("%d",t->Element);
    preorder(t->Left);
    preorder(t->Right);
}//先序遍历递归形式

Tree createtree(listptr elementtype, int num) {
    if (num == 0) return NULL; // 如果没有元素，直接返回 NULL

    Tree root = NULL; // 初始化根节点为空

    for (int i = 0; i < num; i++) {
        // 创建新节点
        Tree newNode = (Tree)malloc(sizeof(struct TreeNode));
        newNode->Element = elementtype[i].Element;
        newNode->Left = newNode->Right = NULL;

        if (elementtype[i].index == -1) {
            // 处理根节点
            root = newNode;
            elementtype[i].ptr = root;
        } else {
            // 查找父节点
            Tree parent = NULL;
            for (int j = 0; j < i; j++) {
                if (elementtype[j].index == elementtype[i].index) {
                    parent = elementtype[j].ptr;
                    break;
                }
            }

            if (parent == NULL) {
                printf("Error: Parent node not found for element %d\n", elementtype[i].Element);
                free(newNode);
                continue;
            }

            // 插入到父节点的左/右子树
            if (newNode->Element < parent->Element) {
                parent->Left = newNode;
            } else {
                parent->Right = newNode;
            }

            elementtype[i].ptr = newNode;
        }
    }

    return root;
}