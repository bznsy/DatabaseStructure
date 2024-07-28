/**
 *    title:  15堆结构.c
 *    author:  sleeeeeping
 *    created:  2024-07-22 16:19:59
**/
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#define TYPE int
#define SWAP(a, b) do { typeof(a) t = (a); (a) = (b); (b) = t; } while(0)

// 设计堆结构
typedef struct Heap {
    TYPE *ptr;
    size_t cap; // 容量
    size_t cnt; // 个数
} Heap;

// 创建堆结构
Heap *createHeap(size_t cap) {
    Heap *heap = malloc(sizeof(Heap));
    heap->ptr = malloc(sizeof(TYPE) * cap);
    heap->cap = cap;
    heap->cnt = 0;
    return heap;
}

// 满堆
bool fullHeap(Heap *heap) {
    return heap->cnt >= heap->cap;
}

// 空堆
bool emptyHeap(Heap *heap) {
    return heap->cnt == 0;
}

// 添加 每次添加前heap一定满足堆结构
void pushHeap(Heap *heap, TYPE val) {
    assert(!fullHeap(heap));
    heap->ptr[heap->cnt++] = val;
    // 在添加的位置可能与它的双亲节点不构成堆结构 需要向上调整
    int index = heap->cnt; // 添加的位置的编号
    while (index > 1) {
        // 插入的值比双亲大 要交换
        if (heap->ptr[index - 1] > heap->ptr[index / 2 - 1]) {
            SWAP(heap->ptr[index - 1], heap->ptr[index / 2 - 1]);   
            index /= 2;
        } else break;
    }
}

// 查看
void showHeap(Heap *heap) {
    for (int i = 0; i < heap->cnt; ++i) {
        printf("%d%c", heap->ptr[i], " \n"[i == heap->cnt - 1]);
    }
}

void _siftSort(int arr[], int start, int end) {
    int root = start, son = start << 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son - 1] < arr[son]) {
            son += 1;
        }
        assert(root - 1 < end && root - 1 >= 0);
        assert(son - 1 >= 0 && son - 1 < end);
        if (arr[root - 1] < arr[son - 1]) {
            SWAP(arr[root - 1], arr[son - 1]);
            root = son;
            son <<= 1;
        } else return ;
    }
}

void heapSort(int arr[], int len) {
    for (int i = len / 2; i >= 1; --i) {
        _siftSort(arr, i, len);
    }
    for (int i = len; i > 1; --i) {
        SWAP(arr[0], arr[i - 1]);
        _siftSort(arr, 1, i - 1);
    }
}

// 从top下标打破end下标 自顶想在调成成堆结构
void _siftSortRecursion(int arr[], int top, int end) {
    if (top * 2 > end) return ;
    int root = top, son = root << 1;
    if (son + 1 <= end && arr[son - 1] < arr[son]) {
        son += 1;
    }
    if (arr[root - 1] < arr[son - 1]) {
        SWAP(arr[root - 1], arr[son - 1]);
        _siftSortRecursion(arr, son, end);
    }
}

// 递归堆排序
void heapSortRecursion(int arr[], size_t len) {
    for (int i = len / 2; i >= 1; --i) {
        _siftSortRecursion(arr, i, len);
    }
    for (int i = len; i > 1; --i) {
        SWAP(arr[0], arr[i - 1]);
        _siftSortRecursion(arr, 1, i - 1);
    }
}

int main() {
    // Heap *heap = createHeap(10);
    // for (int i = 0; i < 10; ++i) {
    //     int x = rand() % 100;
    //     pushHeap(heap, x);
    // }
    int n = 10, m = 10;
    int arr[10] = {5, 75, 97, 96, 18, 1, 90, 5, 76, 16};
    
    heapSortRecursion(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d%c", arr[i], " \n"[i == n - 1]);
    }
    // showHeap(heap);
}