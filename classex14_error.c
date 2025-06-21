#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int N;
int table[MAXN];
int used[MAXN]={0};

int caninsert(int value,int pos)
{
    int i=value%N;
    while(i!=pos)
    {
        if(table[i]==-1 || !used[i])
            return 0;
        i=(i+1)%N;
    }
    return 1;
}

int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;i++)
        scanf("%d",&table[i]);

    int result[MAXN];
    int count=0;

    while(1)
    {
        int minval=100000000;
        int pos=-1;
        for(int i=0;i<N;i++)
        {
            if(table[i]>=0 && !used[i] && caninsert(table[i],i))//如果尚未被模拟插入且是可合法插入的
            {
                if(table[i]<minval)
                {
                    minval=table[i];
                    pos=i;
                }

            }
        }
        if(pos==-1)//已经没有可插入值
            break;//跳出循环
        used[pos]=1;//标记为已模拟插入
        result[count++]=table[pos];
    }

    for(int i=0;i<count;i++)//打印
    {
        if(i>0) printf(" ");
        printf("%d",result[i]);
    }
    printf("\n");

    return 0;
}
