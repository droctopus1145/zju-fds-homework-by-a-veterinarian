#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef struct queuenode* ptrtonode;
struct queuenode{
    int item;
    int picks;
};

typedef struct queue* ptrtoqueue;
struct queue{
    int cap;
    int front;
    int rear;
    ptrtonode head;
};

ptrtoqueue initializequeue(int capacity)
{
    ptrtoqueue h=(ptrtoqueue)malloc(sizeof(struct queue));
    h->front=0;
    h->rear=0;
    h->cap=capacity;
    h->head=(ptrtonode)malloc(MAXSIZE*sizeof(struct queuenode));
    for(int i=0;i<MAXSIZE;i++) h->head[i].picks=0;

    return h;
}

void queuein(ptrtoqueue h,int x,int* hash)
{
    if((h->rear>h->front && h->rear-h->front==h->cap) || (h->rear<h->front && h->rear+MAXSIZE-h->front==h->cap)) //当队列已满，出队一个
    {
        hash[h->head[h->front].item]=-1;
        if(h->front==MAXSIZE-1) h->front=0;
        else h->front++;
    }

    h->head[h->rear].item=x;
    if(h->rear==MAXSIZE-1)
        h->rear=0;
    else
        h->rear++;//循环队列
    hash[x]=(h->rear-1+MAXSIZE)%MAXSIZE;
}

/*int queueout(ptrtoqueue h,int* hash)
{
    if(h->front==h->rear) return -1;//队列为空

    if(h->front==MAXSIZE-1) 
    {
        h->front=0;
        hash[h->head[MAXSIZE-1].item]=-1;
        return h->head[MAXSIZE-1].item;
    }
    else
    {
        h->front++;
        hash[h->head[h->front-1].item]=-1;
        return h->head[h->front-1].item;
    }
}*/

int if_in(int* hash,int x)
{
    return hash[x];
}

void move(ptrtoqueue h,int index,int* hash)
{
    int tmp=h->head[index].item;
    int tmppicks=h->head[index].picks;
    for(int i=index;i!=(MAXSIZE+h->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE)// 
    {
        hash[h->head[(i+1)%MAXSIZE].item]=i;
        h->head[i].item=h->head[(i+1)%MAXSIZE].item;
        h->head[i].picks=h->head[(i+1)%MAXSIZE].picks;
    }   
    h->head[(MAXSIZE+h->rear-1)%MAXSIZE].item=tmp;
    h->head[(MAXSIZE+h->rear-1)%MAXSIZE].picks=tmppicks;
    hash[tmp]=(MAXSIZE+h->rear-1)%MAXSIZE;
}

int move1(ptrtoqueue h,int index,int* hash)
{
    int tmp=h->head[index].item;
    for(int i=index;i!=(MAXSIZE+h->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE)// 
    {
        hash[h->head[(i+1)%MAXSIZE].item]=i;
        h->head[i].item=h->head[(i+1)%MAXSIZE].item;
        h->head[i].picks=h->head[(i+1)%MAXSIZE].picks;
    }
    h->rear=(MAXSIZE+h->rear-1)%MAXSIZE;
    hash[tmp]=-1;

    return tmp;
}

void print(ptrtoqueue access,ptrtoqueue cache)
{
    if(access->front==access->rear)
        printf("-\n");
    else
    {
        if(access->rear>1) for(int i=access->front;i!=(MAXSIZE+access->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE) printf("%d ",access->head[i].item);//
        printf("%d\n",access->head[(MAXSIZE+access->rear-1)%MAXSIZE].item);
    }
    if(cache->front==cache->rear)
        printf("-\n");
    else
    {
        if(cache->rear>1) for(int i=cache->front;i!=(MAXSIZE+cache->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE) printf("%d ",cache->head[i].item);//
        printf("%d\n",cache->head[(MAXSIZE+cache->rear-1)%MAXSIZE].item);
    }
}

int main()
{
    int K,N,M,temp;
    scanf("%d %d %d",&K,&N,&M);//K为最大kick数，N为队列容量，M为总元素个数
    ptrtoqueue access=initializequeue(N);
    ptrtoqueue cache=initializequeue(N);
    int hasha[MAXSIZE];
    int hashc[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++) hasha[i]=hashc[i]=-1;

    for(int i=0;i<M;i++)
    {
        scanf("%d",&temp);
        int index;
        if(if_in(hashc,temp)>=0)
        {
            index=if_in(hashc,temp);
            move(cache,index,hashc);
            //printf("1) ");
            //print(access,cache);
        }   
        else
        {
            if(if_in(hasha,temp)>=0)
            {
                index=if_in(hasha,temp);
                if(++access->head[index].picks==K)
                {
                    queuein(cache,move1(access,index,hasha),hashc);
                    //printf("2) ");
                }
                else
                {
                    move(access,index,hasha);
                    //printf("3) ");
                }
            }
            else
            {
                queuein(access,temp,hasha);
                access->head[(MAXSIZE+access->rear-1)%MAXSIZE].picks=1;
                //printf("4) ");
            }
            //print(access,cache);
        }
    }
    if(access->front==access->rear)
        printf("-\n");
    else
    {
        if(access->rear>1) for(int i=access->front;i!=(MAXSIZE+access->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE) printf("%d ",access->head[i].item);//
        printf("%d\n",access->head[(MAXSIZE+access->rear-1)%MAXSIZE].item);
    }
    if(cache->front==cache->rear)
        printf("-\n");
    else
    {
        if(cache->rear>1) for(int i=cache->front;i!=(MAXSIZE+cache->rear-1)%MAXSIZE;i=(i+1)%MAXSIZE) printf("%d ",cache->head[i].item);//
        printf("%d",cache->head[(MAXSIZE+cache->rear-1)%MAXSIZE].item);
    }
}
