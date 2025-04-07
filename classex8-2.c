#include <stdio.h>

int ifham(int list[][500],int* input,int max)//需提前确定数组中元素个数与图中元素个数相同
{
    int i;
    int check[500];
    for(i=0;i<max;i++)
        check[i]=0;
    for(i=0;i<max;i++)
    {
        if(list[input[i]-1][input[i+1]-1]==1 && check[input[i]-1]==0)
            check[input[i]-1]=1;
        else
            return 0;
    }
    if(input[max]==input[0])
        return 1;
    else
        return 0;
}

int main()
{
    int nv,ne,i,j;
    scanf("%d %d",&nv,&ne);
    int list[500][500];//邻接矩阵实现
    for(i=0;i<nv;i++)
    {
        for(j=0;j<nv;j++)
            list[i][j]=0;
    }
    for(i=0;i<ne;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        list[a-1][b-1]=1;
        list[b-1][a-1]=1;//无向图对称矩阵
    }

    int num;
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        int num1;
        scanf("%d",&num1);
        int input[501];
        for(j=0;j<num1;j++)
            scanf("%d",&input[j]);
        if(num1!=nv+1)
        {
            printf("NO\n");
            continue;
        }  
        if(ifham(list,input,nv)==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
}