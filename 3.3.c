//栈
#include "stack_node.h"
#include "stack_array.h"
#include "queue.h"
#include <stdio.h>
int isempty(stack s)
{
    return s->next==NULL;//表头的next是否悬空
}

stack createstack(void)
{
    stack s;
    s=malloc(sizeof(struct Node));
    if(s==NULL)
        perror("out of space");//内存申请失败
    s->next=NULL;//表头下一节置空
    makeempty(s);//?
    return s;
}

void makeempty(stack s)
{
    if(s==NULL)
        perror("must create a stack first");
    else
        while(!isempty(s))
            pop(s);
}

void push(int x,stack s)
{
    stack tmpcell;

    tmpcell=(struct Node*)malloc(sizeof(struct Node));
    if(tmpcell==NULL)
        FatalError("out of space");
    else
    {
        tmpcell->element=x;
        tmpcell->next=s->next;//将新元素塞到表头与后面的链节之间
        s->next=tmpcell;
    }
}

int top(stack s)
{
    if(!isempty(s))
        return s->next->element;
    else
        perror("must push a element first");
        return 0;//return value avoid to be warned
}

void top(stack s)
{
    stack tmpcell;
    if(isempty(s))
        perror("must push a element first");
    else
    {
        tmpcell=s->next;
        s->next=s->next->next;
        free(tmpcell);
    }  
}

//队列
int isempty(queue q)
{
    return q->size==0;
}

void makeemptyq(queue q)
{
    q->size=0;
    q->rear=0;
    q->front=1;
}

int isfull(queue q)
{
    return q->size==q->capacity;
}

queue createqueue(int maxelements)
{
    queue q;
    int array1[maxelements];
    makeemptyq(q);
    q->capacity=maxelements;
    q->array=array1;
    return q;
}

void disposequeue(queue q)
{
    q->size=0;
    q->rear=0;
    q->front=1;
}

void enqueue(queue q,int x)
{
    if(isfull(q))
        perror("full queue");
    else
    {
        q->size++;
        if(q->rear+1==q->capacity)
            q->rear=0;
        else
            q->rear++;
        q->array[q->rear]=x;
    }
}

void dequeue(queue q)
{
    q->size--;
    if(++q->front==q->capacity)
        q->front=0; //妙啊
}

