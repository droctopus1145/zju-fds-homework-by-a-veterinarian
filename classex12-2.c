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

void down(int arr[],int low,int high) 
{
    int parent=low,child=2*parent+1;
    while(child<high) 
    {
        if(child+1<high && arr[child+1]>arr[child])
            child++;
        if(arr[parent]>=arr[child])
            break;
        int tmp=arr[parent];
        arr[parent]=arr[child];
        arr[child]=tmp;
        parent=child;
        child=2*parent+1;
    }
}

void nextheap(int arr[],int N) 
{
    int i=N-1;
    while(i>0 && arr[i]>=arr[i-1] && arr[i]>arr[0]) //gpt死了吗了
        i--;
    int heapsize=i;
    int tmp=arr[0];
    arr[0]=arr[heapsize-1];
    arr[heapsize-1]=tmp;
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
