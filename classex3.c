#include <stdio.h>

int if_possible(int M,int N,int* list);

int main()
{
    int M,N,K,i,j;
    scanf("%d %d %d",&M,&N,&K);
    int list[N];
    for(i=0;i<K;i++)
    {
        for(j=0;j<N;j++)
            scanf("%d",&list[j]);
        if(if_possible(M,N,list)==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
}

int if_possible(int M,int N,int* list)
{
    int index,i,j,biggest;
    int stack[1000];//栈,在 C 语言中，M 是动态输入的，数组 stack[M] 可能导致 变长数组（VLA）越界，如果 M=0，或者 M 过大，会导致运行时错误
    for(i=0;i<M;i++)
        stack[i]=0;
    for(i=0;i<N;i++)
    {
        if(i==0)//第一个element
        {
            for(j=1;j<list[0];j++)
                stack[j-1]=j;//压栈
            index=list[0]-2;//栈顶索引
            biggest=list[0];//目前进过栈的最大值
            if(list[0]>M)
                return 0;//第一次压栈时就超过栈容量，报错
        }
        else//其他element
        {
            if(list[i]<list[i-1])//只发生弹栈
            {
                if(list[i]==stack[index])//如果与栈顶值相同，则是可能发生的
                    index--;//栈顶值减一  
                else
                    return 0;//与栈顶值不同则报错
            }
            else if(list[i]>list[i-1])//发生多次（一次或零次）压栈和一次弹栈
            {
                for(j=biggest+1;j<list[i];j++)
                {
                    index++;
                    stack[index]=j;//一个个压栈，同时更新栈顶索引
                } 
                biggest=list[i];//更新目前进过栈的最大值
                if(index+1>=M)
                    return 0;//压栈元素超过栈容量，报错
            }
        }