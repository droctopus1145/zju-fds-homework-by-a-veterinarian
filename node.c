int isempty(List L)
{
    return L->Next==NULL;
}

int islast(Position P,List L)
{
    return P->Next==NULL;
}

Position Find(ElementType X,List L)
{
    Position P;

    P=L->NEXT; //链表header中不放置内容，header->next指向的才是放置第一个元素的node
    while(P!=NULL && P->Element!=X)
        P=P->Next;
    
    return P;
}

void deletebyelement(ElementType X,List L)
{
    Position P;
    P=L;
    while(P->NEXT!=NULL && P->NEXT->Element!=X)
        P=P->Next;
    P->Next=P->Next->Next;
}

Position findprevious(ElementType X,List L)
{
    Position P;
    P=L;
    while(P->NEXT!=NULL && P->NEXT->Element!=X)
        P=P->Next;
    return P;
}

void deletebyindex(List L,int index) //index计第一个储存数据的node为1
{
    Position P;
    P=L;
    int i;
    for(i=1;i<index;i++)
        P=P->Next;
//执行结束之后指针正好指向被删除node的前一个node
    P->Next=P->Next->Next;
}

void deletebypointer(List L,Position P)
{
    Position P1;
    P1=L;
    while(P1->NEXT!=P && P1->Next!=NULL)
        P1=P1->Next;
    if(P->NEXT==P)
        P->Next=P->Next->Next;
}

void delete(ElementType X,List L)
{
    Position P,TmpCell;

    P=findprevious(X,L);

    if(!islast(P,L))
    {
        TmpCell=P->Next;
        P->Next=TmpCell->Next;
        free(TmpCell); //为什么if第一行代码不直接free掉P->next--------free掉了以后P指向的内容全部未定义（访问野指针），可能导致程序崩溃
    }
}

void deletelist(list l)
{
    position p;
    p=l->next;
    l->next=NULL;
    while(p!=NULL)
    {
        free(p);
        p=p->next;
    }
}

