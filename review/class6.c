#include <stdio.h>
//priority queues--heaps
//complete binary tree--implement by array
//实现最小堆
#define MAX 100
struct heapstruct;
typedef struct heapstruct *priorityqueue;

struct heapstruct{
    int capacity;
    int size;
    int* elements;
};

//为结构和存储优先队列的数组申请内存
priorityqueue initialize(int maxelements)
{
    priorityqueue h=malloc(sizeof(struct heapstruct));//为优先数组结构申请内存
    h->elements=malloc((maxelements+1)*sizeof(int));
    h->capacity=maxelements;
    h->size=0;
    h->elements[0]=-1;//sentinel

    return h;
}

void insert(int x,priorityqueue h)
{
    int i;
    if(isfull(h))
        return;//如果数组已满，直接返回
    for(i=++h->size;h->elements[i/2]>x;i=i/2)
        h->elements[i]=h->elements[i/2];//将父节点元素下移
    h->elements[i]=x;
}

int deletemin_mine(priorityqueue h)
{
    int minelement=h->elements[1];
    int i=1;
    while(i<=h->size)
    {
        if(h->elements[h->size]>h->elements[i*2] || h->elements[h->size]>h->elements[i*2+1])
        {
            if(h->elements[i*2]>h->elements[i*2+1])
            {
                h->elements[i]=h->elements[i*2+1];
                i=i*2+1;
            }
            else
            {
                h->elements[i]=h->elements[i*2];
                i=i*2;
            }
        }
        else
            break;
    }
    h->elements[i]=h->elements[h->size];
    h->size--;

    return minelement;
}

int deletemin(priorityqueue h)
{
    int i,child;
    int minelement,lastelement;

    if(isempty(h))//如果只剩哨兵节点
        return;//直接返回
    minelement=h->elements[1];//要返回的最小节点存储为minelement
    lastelement=h->elements[h->size--];//将最后一个叶子节点重新放置，以维持完全二叉树的性质
    for(i=1;i*2<=h->size;i=child)//下滤操作（对lastelement）
    {
        child=i*2;
        if(child!=h->size && h->elements[child+1]<h->elements[child])//complete binary tree只有最后一个节点的父节点可能存在单个子节点
            child++;
        
        if(lastelement>h->elements[child])
            h->elements[i]=h->elements[child];//父节点赋最小子节点的值
        else break;
    }
    h->elements[i]=lastelement;//将lastelement填到合适的位置上去

    return minelement;
}

void decreasekey(int p,int delta,priorityqueue h)
{
    int element=h->elements[p]-delta;
    int i;
    for(i=p;i>1;i=i/2)
    {
        if(h->elements[i/2]>element)
            h->elements[i]=h->elements[i/2];
        else break;
    }
    h->elements[i]=element;
}

void delete(int x,priorityqueue h)
{
    int i;
    int lastelement=h->elements[h->size];//为了维持完全二叉树的性质必须使用最后一个元素下滤
    if(h->size==0) return;
    for(i=1;i<=h->size;i++)
    {
        if(h->elements[i]==x) //找到要删除的元素
        {
            int child=i*2;//设置一个child以储存值更小的子节点
            for(i;child<h->size;i=child)
            {
                if(i*2+1<=h->size && h->elements[child]>h->elements[child+1])
                    child=i*2+1;//如果右节点更小，转到右节点
                else
                    child=i*2;

                if(h->elements[child]<lastelement)
                    h->elements[i]=h->elements[child];
                else
                {
                    h->elements[i]=lastelement;
                    h->size--;
                    break;
                }    
            }
            break;
        }
    }      
}

void deleteElement(struct heapstruct* heap, int value) {
    if (heap == NULL || heap->size == 0) {
        return; // 堆为空，直接返回
    }

    // 1. 查找元素位置
    int pos = 0;
    for (int i = 1; i <= heap->size; i++) {
        if (heap->elements[i] == value) {
            pos = i;
            break;
        }
    }
    if (pos == 0) return; // 未找到元素

    // 2. 用最后一个元素替换被删除元素
    heap->elements[pos] = heap->elements[heap->size];
    heap->size--;

    // 3. 堆调整（同时处理上滤和下滤情况）
    int current = pos;
    while (1) {
        int parent = current / 2;
        int leftChild = 2 * current;
        int rightChild = 2 * current + 1;
        int smallest = current;

        // 检查是否需要上滤
        if (parent >= 1 && heap->elements[current] < heap->elements[parent]) {
            // 交换父子节点
            int temp = heap->elements[current];
            heap->elements[current] = heap->elements[parent];
            heap->elements[parent] = temp;
            current = parent;
            continue;
        }

        // 检查是否需要下滤
        if (leftChild <= heap->size && heap->elements[leftChild] < heap->elements[smallest]) {
            smallest = leftChild;
        }
        if (rightChild <= heap->size && heap->elements[rightChild] < heap->elements[smallest]) {
            smallest = rightChild;
        }

        if (smallest != current) {
            // 交换当前节点与较小子节点
            int temp = heap->elements[current];
            heap->elements[current] = heap->elements[smallest];
            heap->elements[smallest] = temp;
            current = smallest;
        } else {
            break; // 堆性质已满足
        }
    }
}

void parcolatedown(int position,priorityqueue h)
{
    int tmp=h->elements[position];
    int i;
    int child;
    for(i=position;i*2<=h->size;i=child)//确保至少有一个子节点存在
    {
        child=(i*2+1<=h->size && h->elements[i*2]>h->elements[i*2+1]) ? i*2+1 : i*2;
        if(tmp>h->elements[child])
            h->elements[i]=h->elements[child];
        else break;
    }
    h->elements[i]=tmp;
}

void buildheap(priorityqueue h)
{
    for(int i=h->size/2;i>0;i--)//从最后一个非叶子节点开始下滤
        parcolatedown(i,h);
}
//最坏的情况--完全反序，每次都需要下滤且滤到叶子节点
//节点深度求和（完美二叉树情况下）--2**（h+1）-1-(h+1)，其中h=log2(n+1)-1，所以时间复杂度为O(n)
//递推求解-s(h)=h+2*s(h-1)