#include <stdio.h>
#include <stdlib.h>

int isinsert(int origin[],int partial[],int N,int* sortedlenptr)
{
    int i=1;
    while(i<N && partial[i] >= partial[i - 1])//找到按顺序排列的最后一个元素
        i++;
    *sortedlenptr=i;
    for(int j=i;j<N;j++)
    {
        if(origin[j]!=partial[j])
            return 0;
    }
    return 1;
}

void nextinsert(int arr[],int sortedlen)
{
    int key=arr[sortedlen];
    int i=sortedlen-1;
    while(i>=0 && arr[i]>key) 
    {
        arr[i+1]=arr[i];
        i--;
    }
    arr[i+1]=key;
}

void down(int arr[],int low,int high) //low为开始下滤的点，high为数组边界
{
    int parent=low,child=2*parent+1;
    while(child<high) //当还未下滤到数组边界
    {
        if(child+1<high && arr[child+1]>arr[child])
            child++;//如果存在右孩子且右孩子大于左孩子，转换到右孩子
        if(arr[parent]>=arr[child])
            break;//如果父节点已经大于子节点：跳出循环
        int tmp=arr[parent];
        arr[parent]=arr[child];
        arr[child]=tmp;//否则父子节点交换位置
        parent=child;//继续下滤
        child=2*parent+1;
    }
}

void nextheap(int arr[],int N) 
{
    int i=N-1;
    while(i>0 && arr[i]>=arr[i-1] && arr[i-1]>arr[0]) //gpt死了吗了，注意加上判断条件：前一个元素需要大于当前堆顶函数，否则不能安全前移（不大于的话说明前一个元素已经在堆内了，不能再前移）
        i--;
    int heapsize=i;//确定堆边界（不在堆内）
    int tmp=arr[0];
    arr[0]=arr[heapsize-1];//将堆末尾元素移动到堆顶
    arr[heapsize-1]=tmp;//将堆顶元素移动到堆末尾
    down(arr,0,heapsize-1);
}

int main()
{
    int N;
    int sortedlen;
    scanf("%d",&N);
    int origin[N],partial[N],output[N];
    for(int i=0;i<N;i++)
        scanf("%d",&origin[i]);
    for(int i=0;i<N;i++)
        scanf("%d",&partial[i]);
    
    if(isinsert(origin,partial,N,&sortedlen))
    {
        printf("Insertion Sort\n");
        for(int i=0;i<N;i++)
            output[i]=partial[i];
        nextinsert(output,sortedlen);
        for(int i=0;i<N-1;i++)
            printf("%d ",output[i]);
        printf("%d\n",output[N-1]);
    }
    else
    {
        printf("Heap Sort\n");
        for(int i=0;i<N;i++)
            output[i]=partial[i];
        nextheap(output,N);
        for(int i=0;i<N-1;i++)
            printf("%d ",output[i]);
        printf("%d\n",output[N-1]);
    }
}
