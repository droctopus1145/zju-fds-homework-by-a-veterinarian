#include <stdio.h>
#include <stdlib.h>
//stack & queue
//stack
//linked list implementation
struct node;
typedef struct node* ptrtonode;
typedef ptrtonode stack;
struct node{
    int element;
    ptrtonode next;
};

//if empty
int isempty(stack s)
{
    return s->next==NULL;
}

//create
stack createstack(void)
{
    stack s;
    s=malloc(sizeof(struct node));
    if(s->next==NULL)
        FatalError("out of space");
    s->next=NULL;
    makeempty(s);//头节点为空
    return s;
}

//clear
void makeempty(stack s)
{
    if(s=NULL)
        Error("create stack first");
    else
        while(!isempty(s))
            pop(s);
}

//push
void push(stack s,int element)
{
    stack insert=malloc(sizeof(struct node));
    if(insert==NULL)
        FatalError("out of space");
    else
    {
        insert->element=element;
        insert->next=s->next;
        s->next=insert;
    }   
}

//pop
int pop(stack s)
{
    if(s==NULL)
        Error("create stack first");
    else if(isempty(s))
        Error("empty stack");
    else
    {
        stack tmp=s->next;
        int output=tmp->element;
        s->next=s->next->next;
        free(tmp);

        return output;
    }   
}

//easy to inplement by array
#define MAX 100
char stack1[MAX];
int top=-1;//create a stack

//push
void push1(char element,int* stack)
{
    if(top>=MAX-1)
    {
        printf("stack overflow");
        exit(1);
    }   
    stack[++top]=element;
}

//pop
char pop1(int* stack)
{
    if(top<0)
    {
        printf("nothing in stack");
        exit(1);
    }
    
    return stack[top--]; 
}

//infix to postfix conversion
//if operator
int isoperator(char a)
{
    return a=='+' || a=='-' || a=='*' || a=='/' || a=='^';
}

//sort operators
int precedence(char a)
{
    switch(a){
        case '^':return 3;
        case '*':return 2;
        case '/':return 2;
        case '+':return 1;
        case '-':return 1;
        default:return 0;
    }       
}

void infix_to_postfix(char* infix,char* postfix)
{
    int i=0,j=0;//pointer point to infix & pointer point to postfix
    char c;//current char
    while(c=infix[i++]!='\0')
    {
        if(c==' ')
            continue;//ignore ' '
        else if(c>='0'&&c<='9')
            postfix[j++]=c;//directly add number to postfix
        else if(c=='(')
            push1(c,stack1);//directly add ( to postfix
        else if(c==')')
        {
            while(stack1[top]!='(')
                postfix[j++]=pop1(stack1);
            pop1(stack1);//pop until '(' is poped
        }
        else if(isoperator(c))  
        {
            while(isoperator(stack1[top]) && precedence(c)<=precedence(stack1[top]))//当出现优先级更小的运算符时，需要完成前面的所有优先级更高或相同的计算
                postfix[j++]=pop1(stack1);
            push1(stack1,c);
        }   
    }
    while(top>-1)
        postfix[j++]=pop1(stack1);   
    postfix[j]='\0';//add the ending
}

//queue
//array implementation-easy
