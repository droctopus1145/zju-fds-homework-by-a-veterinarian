#ifndef __STACK_NODE_H
#define __STAC_NODE_H

struct Node
{
    int element;
    ptrtonode next;
};
typedef struct Node *ptrtonode;
typedef ptrtonode stack;
//typedef struct Node *stack;

int isempty(stack s);
stack createstack(void);
void disposestack(stack s);
void makeempty(stack s);
void push(int x,stack s);
void pop(stack s);
int top(stack s);

#endif