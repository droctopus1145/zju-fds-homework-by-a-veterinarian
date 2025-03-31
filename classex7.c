#include <stdio.h>

int find(int x,int* list);
void union_size(int a,int b,int* list);

int main()
{
    int num,i;
    int sum=0;
    scanf("%d",&num);
    int list[num];
    for(i=0;i<num;i++)
        list[i]=-1;
    char flag;
    int a,b;
    while (scanf(" %c",&flag) == 1) 
    {
        if (flag=='S')  // 终止输入
            break;
        if (flag=='I'||flag=='C') 
            scanf("%d %d",&a,&b);
        if(flag=='I')
            union_size(find(a-1,list),find(b-1,list),list);
        else if(flag=='C')
        {
            if(find(a-1,list)==find(b-1,list))
            {
                printf("yes\n");
            }
            else
                printf("no\n");
        }
    } 
    for(i=0;i<num;i++)
    {
        if(list[i]<0)
            sum++;
    }
    //printf("%d",sum);
    if(sum==1)
        printf("The network is connected.");
    else if(sum>1)
        printf("There are %d components.",sum);   
}

int find(int x, int* list)
{
    if (list[x]<0) 
        return x;
    return list[x]=find(list[x],list); // 路径压缩：直接更新父节点
}

void union_size(int a,int b,int* list)
{
    if(list[a]<list[b])//a的绝对值大于b
    {
        list[a]+=list[b];
        list[b]=a;
    }
    else
    {
        list[b]+=list[a];
        list[a]=b;
    }      
}