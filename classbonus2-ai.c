#include <stdio.h>
#include <stdlib.h>

// 最小堆实现
typedef struct {
    int *data;     // 堆数组
    int capacity;   // 堆容量
    int size;       // 当前堆大小
} MinHeap;

// 初始化堆
MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

// 释放堆
void freeHeap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮调整
void heapifyUp(MinHeap *heap, int index) {
    while (index > 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
        swap(&heap->data[(index - 1) / 2], &heap->data[index]);
        index = (index - 1) / 2;
    }
}

// 下沉调整
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

// 插入元素
void insertHeap(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) return;
    heap->data[heap->size++] = value;
    heapifyUp(heap, heap->size - 1);
}

// 取出堆顶
int extractMin(MinHeap *heap) {
    if (heap->size == 0) return -1;
    int min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapifyDown(heap, 0);
    return min;
}

// 置换选择排序主函数
void replacementSelection(int *records, int N, int M) {
    MinHeap *heap = createHeap(M);
    int *buffer = (int*)malloc(N * sizeof(int)); // 缓冲区
    int bufferSize = 0;
    int currentRunSize = 0;
    int *currentRun = (int*)malloc(N * sizeof(int));
    int index = 0;
    int lastOutput = -1;

    // 初始填充堆
    while (index < N && heap->size < M) {
        insertHeap(heap, records[index++]);
    }

    while (heap->size > 0) {
        int minVal = extractMin(heap);
        currentRun[currentRunSize++] = minVal;
        lastOutput = minVal;

        // 读取新记录
        if (index < N) {
            int newVal = records[index++];
            if (newVal >= lastOutput) {
                insertHeap(heap, newVal);
            } else {
                buffer[bufferSize++] = newVal;
            }
        }

        // 当前run完成
        if (heap->size == 0) {
            // 输出当前run
            for (int i = 0; i < currentRunSize; i++) {
                if (i > 0) printf(" ");
                printf("%d", currentRun[i]);
            }
            printf("\n");
            currentRunSize = 0;

            // 重新填充堆
            for (int i = 0; i < bufferSize && heap->size < M; i++) {
                insertHeap(heap, buffer[i]);
            }
            // 移动剩余元素到缓冲区开头
            int remaining = 0;
            for (int i = heap->size; i < bufferSize; i++) {
                buffer[remaining++] = buffer[i];
            }
            bufferSize = remaining;
        }
    }

    freeHeap(heap);
    free(buffer);
    free(currentRun);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *records = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &records[i]);
    }

    replacementSelection(records, N, M);

    free(records);
    return 0;
}