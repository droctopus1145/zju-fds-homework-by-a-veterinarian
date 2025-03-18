#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};

typedef PtrToNode Polynomial;

Polynomial Read(); /* 读取多项式的函数 */
void Print(Polynomial p); /* 打印多项式的函数 */
Polynomial Add(Polynomial a, Polynomial b); /* 多项式加法函数 */

int main() {
    Polynomial a, b, s;
    a = Read();  // 读取第一个多项式
    b = Read();  // 读取第二个多项式
    s = Add(a, b);  // 计算多项式和
    Print(s);  // 打印结果
    return 0;
}

/* Your function will be put here */
Polynomial Read()
{
    int num,i;
    Polynomial dummy=(Polynomial)malloc(sizeof(struct Node));
    dummy->Next=NULL;
    Polynomial temp=dummy;
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        int coef,exp;
        scanf("%d %d",&coef,&exp);
        Polynomial newnode=(Polynomial)malloc(sizeof(struct Node));
        newnode->Next=NULL;
        newnode->Coefficient=coef;
        newnode->Exponent=exp;  
        temp->Next=newnode;
        temp=newnode;
    }
    return dummy;
}

void Print( Polynomial p )
{
    Polynomial ptr;
    ptr=p->Next;
    while(ptr->Next!=NULL)
    {
        printf("%d %d ",ptr->Coefficient,ptr->Exponent);
        ptr=ptr->Next;
    }
    printf("%d %d",ptr->Coefficient,ptr->Exponent);
}

Polynomial Add( Polynomial a, Polynomial b )
{
    Polynomial output=(Polynomial)malloc(sizeof(struct Node));
    Polynomial temp=output;
    Polynomial ptra=a;
    Polynomial ptrb=b;
    while(ptra->Next!=NULL && ptrb->Next!=NULL)
    {
        if(ptra->Next->Exponent!=ptrb->Next->Exponent)
        {
            if(ptra->Next->Exponent>ptrb->Next->Exponent)
            {
                ptra=ptra->Next;
                Polynomial newnode=(Polynomial)malloc(sizeof(struct Node));
                newnode->Next=NULL;
                newnode->Coefficient=ptra->Coefficient;
                newnode->Exponent=ptra->Exponent;
                temp->Next=newnode;
                temp=newnode;
            }
            else
            {
                ptrb=ptrb->Next;
                Polynomial newnode=(Polynomial)malloc(sizeof(struct Node));
                newnode->Next=NULL;
                newnode->Coefficient=ptrb->Coefficient;
                newnode->Exponent=ptrb->Exponent;
                temp->Next=newnode;
                temp=newnode;
            }
        }
        else
        {
            ptra=ptra->Next;
            ptrb=ptrb->Next;
            if(ptra->Coefficient+ptrb->Coefficient!=0)
            {
                Polynomial newnode=(Polynomial)malloc(sizeof(struct Node));
                newnode->Next=NULL;
                newnode->Coefficient=ptra->Coefficient+ptrb->Coefficient;
                newnode->Exponent=ptra->Exponent;
                temp->Next=newnode;
                temp=newnode;
            }   
        }
    }
    if(ptra->Next!=NULL && ptrb->Next==NULL)
        temp->Next=ptra->Next;
    else if(ptra==NULL && ptrb!=NULL)
        temp->Next=ptrb->Next;
    return output;
}





