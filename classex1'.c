#include <stdio.h>
#include <stdlib.h>

void sort(int* list,int* output,int n)
{
    int i,j,temp;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        {
            if(output[j]>output[i])
            {
                temp=output[j];
                output[j]=output[i];
                output[i]=temp;
                temp=list[j];
                list[j]=list[i];
                list[i]=temp;
            }
        }
}

int main()
{
    int i,j,n,length,temp;
    scanf("%d %d",&n,&length);
    int list[n];
    for(i=0;i<n;i++)
        scanf("%d",list+i);
    int output[list[n-1]-list[0]+1];
    int list1[list[n-1]-list[0]+1];
    for(i=list[0];i<=list[n-1];i++)
    {
        list1[i-list[0]]=i;
        int flag=0;
        temp=i+length;
        for(j=0;j<n;j++)
            if(list[j]>=i && list[j]<=temp)
                flag++;
        output[i-list[0]]=flag;
    }
    sort(list1,output,list[n-1]-list[0]+1);
    printf("%d %d",list1[0],output[0]);
}