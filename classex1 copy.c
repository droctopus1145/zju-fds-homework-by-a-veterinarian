#include <stdio.h>
#include <stdlib.h>

struct node{
    int start;
    int output;
};

typedef struct node list1;


int compare(const void* a,const void* b) 
{
    if(((list1*)b)->output!=((list1*)a)->output)
        return ((list1*)b)->output - ((list1*)a)->output;
    return ((list1*)a)->start - ((list1*)b)->start;
}

int main()
{
    int i,j,n,length,temp;
    scanf("%d %d",&n,&length);
    list1 list[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&list[i].start);
        list[i].output=0;
    }
    for(i=0;i<n;i++)
    {
        int flag=0;
        temp=list[i].start-length;
        for(j=i;list[j].start>=temp && j>=0;j--)
        {
                flag++;
        }
        list[i].output=flag;
    }
    qsort(list, n, sizeof(list1),compare);

    printf("%d %d",list[0].start-length,list[0].output);
}