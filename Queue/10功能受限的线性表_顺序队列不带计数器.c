/**
 *    title:  10功能受限的线性表_顺序队列不带计数器.c
 *    author:  sleeeeeping
 *    created:  2024-07-18 18:46:52
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define TYPE int

typedef struct ArrayQueue {
    TYPE *ptr;
    size_t cap;
    int front;
    int rear;
} ArrayQueue;

ArrayQueue *createArrayQueue(size_t cap) {
    ArrayQueue *q = malloc(sizeof(ArrayQueue));
    q->ptr = malloc(sizeof(TYPE) * (cap + 1));
    q->cap = cap + 1;
    q->front = 0;
    q->rear = 0;
    return q;
}

bool emptyArrayQueue(ArrayQueue *q) {
    return q->rear == q->front;
}

bool fullArrayQueue(ArrayQueue *q) {
    return (q->rear + 1) % q->cap == q->front;
}

void pushArrayQueue(ArrayQueue *q, TYPE val) {
    assert(!fullArrayQueue(q));
    q->ptr[q->rear] = val;
    q->rear = (q->rear + 1) % q->cap;
}

void popArrayQueue(ArrayQueue *q) {
    assert(!emptyArrayQueue(q));
    q->front = (q->front + 1) % q->cap;
}

TYPE frontArrayQueue(ArrayQueue *q) {
    assert(!emptyArrayQueue(q));
    return q->ptr[q->front];
}

TYPE rearArrayQueue(ArrayQueue *q) {
    assert(!emptyArrayQueue(q));
    return q->ptr[(q->rear - 1 + q->cap) % q->cap];
}

size_t sizeArrayQueue(ArrayQueue *q) {
    return (q->rear + q->cap - q->front) % q->cap;
}

void destroyArrayQueue(ArrayQueue *q) {
    free(q->ptr);
    free(q);
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