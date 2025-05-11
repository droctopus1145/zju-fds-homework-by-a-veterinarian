#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    int i;
    int pointer;//确定sorted列表加到哪里了
    int left,mid,right;//确定每次合并的左右子数组
    for(i=0;i<N-length;i+=2*length)//遍历左子数组的起始元素，通过这个确定每次合并的左右子数组(gpt死了吗了
    {
        left=i;
        mid=i+length;
        right=(i+2*length<=N)?i+2*length:N;//如果越界，则取边界
        printf("%d %d %d %d\n",length,left,mid,right);

        int j=left;
        int k=mid;
        pointer=left;
        while(j<mid && k<right)
        {
            if(list[j]<list[k])
                sorted[pointer++]=list[j++];
            else
                sorted[pointer++]=list[k++];
        }
        while(j<mid) 
            sorted[pointer++]=list[j++];
        while(k<right)
            sorted[pointer++]=list[k++];
    }
    for(;i<N;i++) 
        sorted[i]=list[i];
}