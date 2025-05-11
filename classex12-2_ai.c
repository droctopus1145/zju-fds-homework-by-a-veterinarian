#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

void printArray(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

int isInsertion(int origin[], int partial[], int N, int* sortedLen) {
    int i = 1;
    while (i < N && partial[i] >= partial[i - 1]) i++;
    *sortedLen = i;
    for (int j = i; j < N; j++) {
        if (origin[j] != partial[j])
            return 0;  // false
    }
    return 1;  // true
}

void nextInsertion(int arr[], int N, int sortedLen) {
    int key = arr[sortedLen];
    int i = sortedLen - 1;
    while (i >= 0 && arr[i] > key) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = key;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void downAdjust(int arr[], int low, int high) {
    int parent = low, child = 2 * parent + 1;
    while (child < high) {
        if (child + 1 < high && arr[child + 1] > arr[child])
            child++;
        if (arr[parent] >= arr[child])
            break;
        swap(&arr[parent], &arr[child]);
        parent = child;
        child = 2 * parent + 1;
    }
}

void nextHeap(int arr[], int N) {
    int i = N - 1;
    while (i > 0 && arr[i] >= arr[i - 1]) i--;
    int heapSize = i;
    swap(&arr[0], &arr[heapSize - 1]);
    downAdjust(arr, 0, heapSize - 1);
}

int main() {
    int N;
    int origin[MAXN], partial[MAXN], temp[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &origin[i]);
    for (int i = 0; i < N; i++) scanf("%d", &partial[i]);

    int sortedLen;
    if (isInsertion(origin, partial, N, &sortedLen)) {
        printf("Insertion Sort\n");
        for (int i = 0; i < N; i++) temp[i] = partial[i];
        nextInsertion(temp, N, sortedLen);
        printArray(temp, N);
    } else {
        printf("Heap Sort\n");
        for (int i = 0; i < N; i++) temp[i] = partial[i];
        nextHeap(temp, N);
        printArray(temp, N);
    }

    return 0;
}
