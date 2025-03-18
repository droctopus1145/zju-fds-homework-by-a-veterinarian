#ifndef __QUEUE_H
#define __QUEUE_H

struct queuerecord{
    int capacity;
    int front;
    int rear;
    int size;
    int* array;
};
typedef struct queuerecord *queue;

int isemptyq(queue q);
int isfullq(queue q);
queue createqueue(int maxelements);
void disposequeue(queue q);
void makeemptyq(queue q);
void enqueue(queue q,int x);
void dequeue(queue q);
int front(queue q);
int front_dequeue(queue q);

#endif