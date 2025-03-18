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
    int list1[n];
    int output[n];
    for(i=0;i<n;i++)
    {
        int flag=0;
        temp=list[i]-length;
        list1[i]=temp;
        for(j=0;list[j]<=list[i];j++)
        {
            if(list[j]>=temp)
                flag++;
        }
        output[i]=flag;
    }
    sort(list1,output,n);
    printf("%d %d",list1[0],output[0]);
}