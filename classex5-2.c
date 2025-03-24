#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;
}treenode;

int cmp(const void* a,const void* b) 
{
    return (*(int*)a-*(int*)b);
}


void leveltraversal(Tree root,int num);
Tree createcbt(int* list,int first,int last);

int main()
{
    int num,i;
    Tree cbt;
    scanf("%d",&num);
    int* list=(int*)malloc(num*sizeof(int));
    for(i=0;i<num;i++)
        scanf("%d",&list[i]);
    qsort(list,num,sizeof(int),cmp);
    cbt=createcbt(list,0,num-1);
    leveltraversal(cbt,num);
}

Tree createcbt(int* list,int first,int last)
{
    int elementnum=last-first+1;
    if(elementnum<1) return NULL;
    else if(elementnum==1)
    {
        Tree element=(Tree)malloc(sizeof(struct TreeNode));
        element->Element=list[first];
        element->Left=element->Right=NULL;

        return element;
    }
    else if(elementnum==2)
    {
        Tree parent=(Tree)malloc(sizeof(struct TreeNode));
        Tree child=(Tree)malloc(sizeof(struct TreeNode));
        parent->Element=list[last];
        parent->Left=child;
        parent->Right=NULL;
        child->Element=list[first];
        child->Left=child->Right=NULL;

        return parent;
    }
    else if(elementnum==3)
    {
        Tree parent1=(Tree)malloc(sizeof(struct TreeNode));
        Tree leftchild=(Tree)malloc(sizeof(struct TreeNode));
        Tree rightchild=(Tree)malloc(sizeof(struct TreeNode));
        parent1->Element=list[first+1];
        parent1->Left=leftchild;
        parent1->Right=rightchild;
        leftchild->Element=list[first];
        rightchild->Element=list[last];
        leftchild->Left=leftchild->Right=rightchild->Left=rightchild->Right=NULL;

        return parent1;
    }
    else
    {
        int i;
        for(i=2;i<12;i++)
        {
            if(elementnum>((1<<i)-1) && elementnum<(1<<(i+1)))
                break;
        }
        int rootindex;
        if((elementnum+1-(1<<i))<((1<<i)/2))
            rootindex=elementnum-(1<<(i-1));
        else
            rootindex=(1<<i)-1;
        Tree root=(Tree)malloc(sizeof(struct TreeNode)); 
        root->Element=list[rootindex];
        root->Left=createcbt(list,first,rootindex-1);
        root->Right=createcbt(list,rootindex+1,last);

        return root;
    }
}

void leveltraversal(Tree root,int num) 
{
    if (!root) return;
    Tree* queue=(Tree*)malloc(num*sizeof(Tree));
    int front=0,rear=0;
    queue[rear++]=root; 

    while(front<rear && num>1) 
    {  
        Tree current = queue[front++]; 
        printf("%d ",current->Element);
        num--;
        if (current->Left) queue[rear++]=current->Left; 
        if (current->Right) queue[rear++]=current->Right;
    }
    printf("%d",queue[front]->Element);
}