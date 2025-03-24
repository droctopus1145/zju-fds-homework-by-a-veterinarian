#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

void PercolateUp( int p, PriorityQueue H )
{
    int i=p;
    int parent;
    int temp=H->Elements[p];
    while(i>1)
    {
        parent=i/2;
        if(H->Elements[parent]>temp)
        {
            H->Elements[i]=H->Elements[parent];
            i=parent;
        }
        else
            break;
    }
    H->Elements[i]=temp;
}

void PercolateDown( int p, PriorityQueue H )
{
    int i=p;
    int child;
    int temp=H->Elements[p];
    while(i*2<=H->Size)
    {
        child=i*2;
        if(i*2+1>H->Size);
        else if(H->Elements[i*2]>H->Elements[i*2+1])
            child++;
        if(temp>H->Elements[child])
        {
            H->Elements[i]=H->Elements[child];
            i=child;
        }
        else
            break;
    }
    H->Elements[i]=temp;
}