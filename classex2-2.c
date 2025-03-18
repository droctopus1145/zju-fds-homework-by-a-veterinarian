#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */
Position Read()
{
    int num,i;
    Position dummy=(Position)malloc(sizeof(struct Node));
    dummy->Next=NULL;
    Position temp=dummy;
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        int coef;
        scanf("%d",&coef);
        Position newnode=(Position)malloc(sizeof(struct Node));
        newnode->Next=NULL;
        newnode->Element=coef;
        temp->Next=newnode;
        temp=newnode;
    }
    return dummy;
}

void Print( Position p )
{
    Position ptr;
    ptr=p->Next;
    while(ptr->Next!=NULL)
    {
        printf("%d",ptr->Element);
        ptr=ptr->Next;
    }
    printf("%d",ptr->Element);
}

List Reverse( List L )
{
    Position next,ptr,front;
    front=NULL;
    ptr=L->Next;
    while(ptr!=NULL)
    {
        next=ptr->Next;
        ptr->Next=front;
        front=ptr;
        ptr=next;
    }
    L->Next=front;

    return L;
}