/**
 *    title:  09功能受限的线性表_顺序队列带计数器.c
 *    author:  sleeeeeping
 *    created:  2024-07-18 17:03:31
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define TYPE int

// 顺序队列结构
typedef struct ArrayQueue {
    TYPE *ptr; // 存储元素内存首地址
    size_t cap; // 容量
    size_t size; // 元素个数 计数器
    int front; // 队头下标
    int rear; // 队尾下标
} ArrayQueue;

// 创建
ArrayQueue *createArrayQueue(size_t cap) {
    ArrayQueue *q = malloc(sizeof(ArrayQueue));
    q->ptr = malloc(sizeof(TYPE) * cap);
    q->cap = cap;
    q->size = 0;
    q->front = 0;
    q->rear = -1; // rear指向队尾元素
    return q;
}

// 销毁
void destroyArrayQueue(ArrayQueue *q) {
    free(q->ptr);
    free(q);
}

// 队满
bool fullArrayQueue(ArrayQueue *q) {
    return q->size == q->cap;
}

// 队空
bool emptyArrayQueue(ArrayQueue *q) {
    return q->size == 0;
}

// 入队
void pushArrayQueue(ArrayQueue *q, TYPE val) {
    assert(q->size < q->cap);
    // 移动rear往后一位
    q->rear = (q->rear + 1) % q->cap;
    // 把数据入队到rear的位置
    q->ptr[q->rear] = val;
    q->size += 1;
}

// 出队
void popArrayQueue(ArrayQueue *q) {
    assert(q->size > 0);
    // 往后移动front就相当于出队一个元素
    q->front = (q->front + 1) % q->cap;
    q->size -= 1;
}

// 队头
TYPE frontArrayQueue(ArrayQueue *q) {
    return q->ptr[q->front];
}

// 队尾
TYPE rearArrayQueue(ArrayQueue *q) {
    return q->ptr[q->rear];
}

// 数量
size_t sizeArrayQueue(ArrayQueue *q) {
    return q->size;
}

int main() {
    ArrayQueue *q = createArrayQueue(10);
    for (int i = 0; i < 10; ++i) {
        pushArrayQueue(q, i);
        printf("rear = %d, size = %lu\n", rearArrayQueue(q), sizeArrayQueue(q));
    }
    printf("++++++++++++++++++++++++++\n");
    while (!emptyArrayQueue(q)) {
        printf("front = %d, size = %lu\n", frontArrayQueue(q), sizeArrayQueue(q));
        popArrayQueue(q);
    }
}