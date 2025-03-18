#include <stdio.h>

struct node {
    int item;
    int pick;
};

typedef struct node queue;
typedef queue* ptr_queue;

// 如果在队列中找到，则返回该元素下标；否则返回 -1
int if_in(int num, ptr_queue access, int front, int rear);
// 如果下次 pick 后达到或超过阈值 K，返回 1；否则返回 0
int if_out(int num, ptr_queue access, int front, int rear, int K);
// 删除 access 队列中指定元素，并更新队尾下标
void delete_item(int num, ptr_queue access, int front, int *rear);

int main()
{
    int K, N, M, i, temp;
    // K 为最大 kick 数，N 为队列容量，M 为总元素个数
    scanf("%d %d %d", &K, &N, &M);
    
    queue access[1000];
    int cache[1000];   // 用数组模拟两个队列
    int front_a = 0, rear_a = 0;
    int front_c = 0, rear_c = 0;  // cache 队列的首尾下标

    for(i = 0; i < M; i++)
    {
        scanf("%d", &temp);
        int index = if_in(temp, access, front_a, rear_a);
        
        // 如果 access 队列中没有该元素，并且队列未满，则直接入队
        if(index == -1 && (rear_a - front_a) < N)
        {
            access[rear_a].item = temp;
            access[rear_a].pick = 1;
            rear_a++;
        }
        // 如果 access 队列中没有该元素，但队列已满，则将队首出队后再入队
        else if(index == -1 && (rear_a - front_a) == N)
        {
            front_a++;  // 队首出队
            access[rear_a].item = temp;
            access[rear_a].pick = 1;
            rear_a++; 
        }
        // 如果 access 队列中已有该元素，并且还未达到 kick 阈值，则增加 pick 数
        else if(index != -1 && if_out(temp, access, front_a, rear_a, K) == 0)
        {
            access[index].pick++;
        }
        // 如果 access 队列中已有该元素，并且达到 kick 阈值，则删除该元素，并加入 cache 队列
        else if(index != -1 && if_out(temp, access, front_a, rear_a, K) == 1)
        {
            // 输出被删除的元素（如有需要可以保留或删除该打印语句）
            printf("%d\n", temp);
            delete_item(temp, access, front_a, &rear_a); // 删除 access 队列中的该元素
            
            // 将元素加入 cache 队列中，若 cache 队列已满，则先出队队首元素
            if((rear_c - front_c) < N)
            {
                cache[rear_c] = temp;
                rear_c++;
            }
            else
            {
                front_c++;
                cache[rear_c] = temp;
                rear_c++;
            }
        }    
    }

    // 输出 access 队列
    if(rear_a == front_a)
        printf("-\n");
    else
    {
        for(i = front_a; i < rear_a - 1; i++)
            printf("%d ", access[i].item);
        printf("%d\n", access[rear_a - 1].item);
    }
    
    // 输出 cache 队列
    if(rear_c == front_c)
        printf("-\n");
    else
    {
        for(i = front_c; i < rear_c - 1; i++)
            printf("%d ", cache[i]);
        printf("%d\n", cache[rear_c - 1]);
    }
    
    return 0;
}

int if_in(int num, ptr_queue access, int front, int rear)
{
    for(int i = front; i < rear; i++)
    {
        if(access[i].item == num)
            return i;
    }
    return -1;
}

int if_out(int num, ptr_queue access, int front, int rear, int K)
{
    int index = if_in(num, access, front, rear);
    if(index == -1)
        return 0;  // 理论上不应走到此处
    // 若下次 pick 达到或超过 K，则返回 1，否则返回 0
    return (access[index].pick + 1 < K) ? 0 : 1;
}

void delete_item(int num, ptr_queue access, int front, int *rear)
{
    int index = if_in(num, access, front, *rear);
    if(index == -1)
        return;
    // 从删除位置开始，将后续元素左移覆盖
    for(int i = index; i < *rear - 1; i++)
        access[i] = access[i+1];
    (*rear)--;
}
