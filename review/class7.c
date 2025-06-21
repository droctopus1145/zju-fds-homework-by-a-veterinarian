//disjoint set 并查集/不相交集
#include <stdio.h>
#include <stdlib.h>

#define NumSets 10
int disjoint[NumSets];

void initialize(int* disjoint)
{
    for(int i=0;i<NumSets;i++)
        disjoint[i]=0;//全部初始化为0，代表现在没有元素连接
}

void union1(int* disjoint,int root1,int root2)
{
    disjoint[root2]=root1;//将root2连接到root1上
}

int find_rec(int* disjoint,int x)
{
    if(disjoint[x]<=0)
        return x;
    else
        return find_rec(disjoint,disjoint[x]);
}

int find_iter(int* disjoint,int x)
{
    while(disjoint[x]>0) x=disjoint[x];

    return x;
}

//路径压缩算法--循环写法
int find_best_iter(int* disjoint,int x)
{
    int root=x;
    int tmp;
    while(disjoint[root]>0) root=disjoint[root];//先找到根节点
    while(disjoint[x]>0)
    {
        tmp=x;
        x=disjoint[x];
        disjoint[tmp]=root;
    }
}
//路径压缩算法--递归写法
int find_best_rec(int* disjoint,int x)
{
    if(disjoint[x]<=0)
        return x;
    else
    {
        disjoint[x]=find_best_rec(disjoint,disjoint[x]);//路径压缩
        return disjoint[x];//不要在递归浪费资源
    }
}

//smart union algorithms
//union by size
//union by height


