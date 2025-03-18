#include <stdio.h>

long int Factorial(int N)
{
    if(N==1)
        return 1;
    else
        return N*Factorial(N-1);
}
//递归

long int Fib(int N)
{
    if(N<=1)
        return 1;
    else
        return Fib(N-1)+Fib(N-2);
}
//t(N)=t(N-1)+t(N-2)+2,t(N)大于对应的斐波那契数

//最大子序列和问题的解
int maxsubsequencesum1(const int *A,int N)
{
    int thissum,maxsum,i,j,k;
    maxsum=0;
    for(i=0;i<N;i++)
        for(j=i;j<N;j++) //遍历所有可能的i，j数对(i<j)
        {
            thissum=0;
            for(k=i;k<=j;k++) //这一步浪费了
                thissum+=A[k]; 
            if(thissum>maxsum)
                maxsum=thissum;
        }
    return maxsum;
} //O(N^3)

int maxsubsequence2(const int *A,int N)
{
    int thissum,maxsum,i,j;
    maxsum=0;
    for(i=0;i<N;i++)
    {
        thissum=0;
        for(j=i;j<N;j++)
        {
            thissum+=A[j];//在遍历同时累加求和
            if(thissum>maxsum)
                maxsum=thissum;
        }
    }
    return maxsum;
}

static int maxsubsum(const int *A,int left,int right)
{
    int maxleftsum,maxrightsum;
    int maxleftbordersum,maxrightbordersum;
    int leftbordersum,rightbordersum;
    int center,i;

    if(left==right) //基准情况（递归到只有一个元素）
        if(A[left]>0)
            return A[left];
        else
            return 0;

    center=(left+right)/2; //当原序列有奇数个元素，center是最中间的元素；当原序列有偶数个元素，center是中间左边的元素
    maxleftsum=maxsubsum(A,left,center); //递归调用函数获得左边最大子序列和
    maxrightsum=maxsubsum(A,center+1,right); //递归调用函数获得右边最大子序列和

    //准备开始计算第三种情况--最大序列和横跨center
    maxleftbordersum=0;
    leftbordersum=0;
    for(i=center;i>=left;i--)
    {
        leftbordersum+=A[i];
        if(leftbordersum>maxleftbordersum)
            maxleftbordersum=leftbordersum;
    }
        
    maxrightbordersum=0;
    rightbordersum=0;
    for(i=center+1;i<=right;i++)
    {
        rightbordersum+=A[i];
        if(rightbordersum>maxrightbordersum)
            maxrightbordersum=rightbordersum;
    }

    return 0;//Max3(maxleftsum,maxrightsum,maxleftbordersum+maxrightbordersum);       
} //T(N)=2T(N/2)+O(N),经计算T(N)=O(N*logN)

int maxsubsequence3(const int *A,int N)
{
    int thissum,maxsum,j;

    thissum=maxsum=0;
    for(j=0;j<N;j++)
    {
        thissum+=A[j];
        
        if(thissum>maxsum)
            maxsum=thissum;
        else if(thissum<0) //关键在于下面这两句
            thissum=0; //如果某一段元素和小于0，那么他们已经失去利用价值，可以抛弃掉然后从头开始了
    }
    return maxsum;
}

//运行时间中的对数
//first example对分查找
int binarysearch(const int A[],int x,int N)
{
    int low,mid,high;

    low=0;
    high=N-1;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(A[mid]>x)
            low=mid+1;
        else if(A[mid]<x)
            high=mid-1;
        else
            return mid;
    }
    return -1;
}
//欧几里德算法（辗转相除法）
unsigned int gcd(unsigned int M,unsigned int N)
{
    unsigned int rem;
    while(N>0)
    {
        rem=M%N;
        M=N;
        N=rem;
    }
    return M;
}
//高效的取幂算法
long int Pow(long int X,unsigned int N)
{
    if(N==0)
    {
        return 1;
    }
    if(N==1)
    {
        return X;
    }
    if(N%2==0)
    {
        return Pow(X,N/2)*Pow(X,N/2);
    }
    else
        return Pow(X,N/2)*Pow(X,N/2)*X;
}

//int main()
//{
//    printf("%ld",Pow(3,4));
//}

