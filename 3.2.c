//使用链表的例子
//多项式ADT
//1
//使用数组存储多项式系数，适合稠密的多项式，当多项式稀疏时对多项式进行运算效率较低
//2
typedef struct node *ptrtonode;

struct node
{
    int coef; //定义系数
    int exp; //定义次数
    ptrtonode next;
};
//变量定义与函数声明应该放到c head文件中

//桶式排序
int* bucket_sort(int *list,int M,int N)//N个整数，范围从1->M
{
    int i;
    int *count;
    for(i=0;i<M;i++)
        count[i]=0; //2M，初始化为0
    for(i=0;i<N;i++)
        count[list[i]-1]+=1; //2N，归入每个桶中
    for(i=0;i<M;i++)
    {
        if(count[i]==1)
            printf("%d",i+1); //3M
    }

    return count; 
} 

//基数排序（通过最高有效位对桶进行排序）
int* radix_sort(int *list,int n,int p)
{
    int i;
    int *count;
    for(i=0;i<n;i++)
        count[i]=0; //2n，初始化为0
    
}

//多重表
