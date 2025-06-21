#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//tree
//using binary tree to inplement any tree
typedef struct treenode *ptrtonode;
struct treenode{
    int element;
    ptrtonode firstnode;
    ptrtonode nextsibling;
};

//tree traversal

//binary search tree
//find-recursion
ptrtonode rfind(int x,ptrtonode t)
{
    if(t==NULL)
        return NULL;//finish the recursion
    if(x<t->element && t->firstnode!=NULL)
        return find(x,t->firstnode);
    else if(x>t->element && t->nextsibling!=NULL)
        return find(x,t->nextsibling);
    else
        return t;
}
//find-interation
ptrtonode ifind(int x,ptrtonode t)
{
    ptrtonode tmp=t;
    while(tmp!=NULL)
    {
        if(x>tmp->element)
            tmp=tmp->firstnode;
        else if(x<tmp->element)
            tmp=tmp->nextsibling;
        else
            return tmp;
    }

    return tmp;
}
//findmin-recursion
ptrtonode findmin(ptrtonode t)
{
    if(t==NULL)
        return NULL;
    else if(t->firstnode==NULL)
        return t;
    else
        return findmin(t->firstnode);
}

//findmax-interation
ptrtonode findmax(ptrtonode t)
{
    if(t!=NULL)
    {
        while(t->nextsibling!=NULL)
            t=t->nextsibling;
    }

    return t;
}

//insert-recursion
ptrtonode insert(int x,ptrtonode t)
{
    if(t==NULL)//create a tree
    {
        t=malloc(sizeof(*t));//attention
        if(t==NULL)
            FatalError('outofspace');
        else
        {
            t->element=x;
            t->firstnode=t->nextsibling=NULL;
        }
    }//when nothing in the tree or meet a leaf node
    else
    {
        if(x<t->element)
            insert(x,t->firstnode);
        else if(x>t->element)    
            insert(x,t->nextsibling);
        //if x already in the tree,do nothing 
    }

    return t;
}

//delete
void delete(int x,ptrtonode t)
{
    ptrtonode tmp;
    if(t==NULL)
        Error("element not found");
    else if(x<t->element)
        delete(x,t->firstnode);
    else if(x>t->element)
        delete(x,t->nextsibling);
    else//found the element
    {
        if(t->firstnode && t->nextsibling)//have two children
        {
            tmp=findmin(t->nextsibling);
            t->element=tmp->element;
            delete(t->element,t->nextsibling);
        }//find the smallest one in right subtree
        else
        {
            tmp=t;
            if(t->firstnode==NULL)
                t=t->nextsibling;
            else if(t->nextsibling==NULL)
                t=t->firstnode;//接头霸王
            free(tmp);//store the original pointer to free it
        }
    }
}
//可行性--右子树的最小值小于右子树其他所有元素，同时右子树所有元素一定大于左子树元素（经过被替换元素分拣）

//二叉树遍历
//level-order traversal
typedef struct btreenode *ptrtobnode;
struct btreenode{
    int val;
    ptrtobnode left;
    ptrtobnode right;
};

void levelorder(ptrtobnode h)
{
    ptrtobnode queue[MAX];
    int rear=1;
    int front=0;
    queue[rear-1]=h;
    while(rear!=front)
    {
        ptrtobnode tmp=queue[front];
        printf("%d",queue[front++]->val);
        if(tmp->left)
        {
            queue[rear]=tmp->left;
            rear++;
        }    
        if(tmp->right)
        {
            queue[rear]=tmp->right;   
            rear++;
        }             
    }
}

//dfs-recursion
//preorder
void preorder(ptrtobnode h)
{
    if(h=NULL)  return;
    printf("%d ",h->val);
    preorder(h->left);
    preorder(h->right);
}

//inorder
void inorder(ptrtobnode h)
{
    if(h=NULL)  return;
    inorder(h->left);
    printf(h->val);
    inorder(h->right);
}

//postorder
void postorder(ptrtobnode h)
{
    if(h=NULL)  return;
    postorder(h->left);
    postorder(h->right);
    printf("%d",h->val);
}

//dfs-inplement by stack
//inorder


void stack_inorder(ptrtobnode h)
{
    ptrtobnode stack[MAX];
    int top=-1;
    ptrtobnode tmp=h;
    while(tmp!=NULL || top!=-1)//当栈不为空（需要出栈并输出）和tmp不为空（还需要处理入栈）时进入循环
    {
        if(tmp!=NULL)//处理入栈
        {
            stack[++top]=tmp;
            tmp=tmp->left;
        }
        else//处理出栈输出
        {
            tmp=stack[top--];
            printf("%d ",tmp->val);
            tmp=tmp->right;
        }
    }
}