#include <stdio.h>

struct node{
    int item;
    int pick;
};

typedef struct node queue;
typedef queue* ptr_queue;

int if_in(int num,ptr_queue access,int front_a,int rear_a);//在的话return index，不在的话return -1
int if_out(int num,ptr_queue access,int front_a,int rear_a,int K);
void delete(int num,ptr_queue access,int front_a,int rear_a);

int main()
{
    int K,N,M,i,temp;
    scanf("%d %d %d",&K,&N,&M);//K为最大kick数，N为队列容量，M为总元素个数
    queue access[100];
    int cache[100];//以数组形式创建两个队列
    int front_a,rear_a=0;
    int front_c,rear_c=0;//定义首尾索引
    for(i=0;i<M;i++)
    {
        scanf("%d",&temp);
        //分以下几种情况：如果access队列中没有满且其中没有这个数：入队即可
        //如果access队列已满且其中没有这个数：队列首位出队，该数入队
        //如果access队列中有这个数，但是还没到出队pick数：pick++
        //如果access队列中有这个数，且到了出队pick数：从access中删除此数，加入缓存队列，同时注意缓存队列容量
        if(if_in(temp,access,front_a,rear_a)==-1 && rear_a-front_a<5)
        {
            
            access[rear_a].item=temp;
            access[rear_a].pick=1;
            rear_a++;
        }
        else if(if_in(temp,access,front_a,rear_a)==-1 && rear_a-front_a==5)
        {
            
            front_a++;
            access[rear_a].item=temp;
            access[rear_a].pick=1;
            rear_a++; 
        }
        else if(if_in(temp,access,front_a,rear_a)>=0 && if_out(temp,access,front_c,rear_c,K)==0)
            access[if_in(temp,access,front_c,rear_c)].pick++;
        else if(if_in(temp,access,front_a,rear_a)>=0 && if_out(temp,access,front_c,rear_c,K)==1)
        {
            printf("%d\n",temp);
            delete(temp,access,front_a,rear_a);//删除元素
            rear_a--;//队尾减一
            if(rear_c-front_c<5)
            {
                cache[rear_c]=temp;
                rear_c++;
            }
            else
            {
                front_c++;
                cache[rear_c]=temp;
                rear_c++;
            }
        }    
    }

    if(rear_a==front_a)
        printf("-\n");
    else
    {
        for(i=front_a;i<rear_a-1;i++)
            printf("%d ",access[i].item);
        printf("%d\n",access[rear_a-1].item);
    }
    
    if(rear_c==front_c)
        printf("-\n");
    else
    {
        for(i=front_c;i<rear_c-1;i++)
            printf("%d ",cache[i]);
        printf("%d\n",cache[rear_c-1]);
    }
}

int if_in(int num,ptr_queue access,int front_a,int rear_a)
{
    int i;
    for(i=front_a;i<rear_a;i++)
    {
        if(access[i].item==num)
            return i;
    }
    return -1;
}

int if_out(int num,ptr_queue access,int front_a,int rear_a,int K)
{
    if(access[if_in(num,access,front_a,rear_a)].pick+1<K)
        return 0;
    else
        return 1;
}

void delete(int num,ptr_queue access,int front_a,int rear_a)
{
    int i;
    for(i=if_in(num,access,front_a,rear_a);i<rear_a;i++)
        access[i]=access[i+1];
}