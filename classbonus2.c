#include <stdio.h>
#include <stdlib.h>

typedef struct heapstruct *ptrtoheap;
struct heapstruct{
    int size;
    int capacity;
    int* heap;
};


void percolatedown(ptrtoheap h,int pos)
{
    int tmp=h->heap[pos];
    int i;
    int child;
    for(i=pos;i*2<=h->size;i=child)//确保至少有一个子节点存在
    {
        child=(i*2+1<=h->size && h->heap[i*2]>h->heap[i*2+1]) ? i*2+1 : i*2;//当且仅当右子节点存在且右子节点值小于左节点值时选择右子节点
        if(tmp>h->heap[child])
            h->heap[i]=h->heap[child];
        else break;
    }
    h->heap[i]=tmp;
}

//使用o(n)方法建堆
ptrtoheap createheap(int* records,int size)
{
    ptrtoheap h=(ptrtoheap)malloc(sizeof(struct heapstruct));
    h->capacity=size;
    h->size=size;
    h->heap=(int*)malloc((size+1)*sizeof(int));//数组头为空
    for(int i=1;i<=size;i++)
        h->heap[i]=records[i-1];
    for(int i=size/2;i>0;i--)
        percolatedown(h,i);

    return h;
}

int deletemin(ptrtoheap h) 
{
    if (h->size==0) return;
    int min=h->heap[1];
    h->heap[1]=h->heap[h->size--];
    percolatedown(h,1);
    return min;
}

void insert(ptrtoheap h, int x)
{
    int i=++h->size;
    for (;i>1 && x<h->heap[i/2];i/=2)//上滤
        h->heap[i]=h->heap[i/2];
    h->heap[i]=x;
}

void replacementselection(int* records,int N,int M)
{
    ptrtoheap h=createheap(records,M<N?M:N);//初始建堆，取M和N较小值
    int* buffer=(int*)malloc(N*sizeof(int));//缓冲区
    int buffer_size=0;
    int input_pos=M;//输入位置指针
    int last_output=0;//记录上次输出值
    int first_in_run=1;//标记是否是run的第一个元素

    while(h->size>0)
    {
        int current=deletemin(h);//取出最小元素
        
        //输出当前元素
        if(first_in_run)
        {
            printf("%d",current);
            first_in_run=0;
        }
        else
            printf(" %d",current);
        last_output=current;

        //读取新元素
        if(input_pos<N)
        {
            int new_val=records[input_pos++];
            if(new_val>=last_output)
                insert(h,new_val);//符合条件加入堆
            else
                buffer[buffer_size++]=new_val;//否则存入缓冲区
        }

        //run结束处理
        if(h->size==0)
        {
            printf("\n");//换行表示run结束
            first_in_run=1;//重置标记
            //重新填充堆
            int fill_size=buffer_size<h->capacity ? buffer_size:h->capacity;
            for(int i=0;i<fill_size;i++)
                h->heap[++h->size]=buffer[i];
            //重建堆
            for(int i=h->size/2;i>0;i--)
                percolatedown(h,i);
            //移动剩余buffer元素
            int remaining=0;
            for(int i=fill_size;i<buffer_size;i++)
                buffer[remaining++]=buffer[i];
            buffer_size=remaining;
        }
    }
}

int main() 
{
    int N,M;
    scanf("%d %d",&N,&M);
    int *records=(int*)malloc(N*sizeof(int));
    for (int i=0;i<N;i++) 
        scanf("%d",&records[i]);

    replacementselection(records,N,M);

    return 0;
}
