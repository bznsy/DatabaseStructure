/**
 *    title:  08功能受限的线性表_链式队列.c
 *    author:  sleeeeeping
 *    created:  2024-07-18 16:04:25
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define TYPE int 

typedef struct ListNode {
    TYPE val;
    struct ListNode* next;
} ListNode;

ListNode *createListNode(TYPE val) {
    ListNode *node = malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// 设计链式队列结构
typedef struct ListQueue {
    ListNode *front; // 队头指针
    ListNode *rear;  // 队尾
    size_t size; // 节点数量
} ListQueue;

// 创建
ListQueue *createListQueue() {
    ListQueue *q = malloc(sizeof(ListQueue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

// 队空
bool emptyListQueue(ListQueue *q) {
    return q->size == 0;
}

// 入队
void pushListQueue(ListQueue *q, TYPE val) {
    ListNode *node = createListNode(val);
    if (emptyListQueue(q)) {
        q->front = node;
    } else {
        q->rear->next = node;
    }
    q->rear = node;
    q->size += 1;
}

// 出队
void popListQueue(ListQueue *q) {
    assert(q->size > 0);
    ListNode *node = q->front;
    q->front = node->next;
    free(node);
    q->size -= 1;
    if (q->size == 0) {
        q->rear = NULL;
    }
}

// 队头
TYPE frontListQueue(ListQueue *q) {
    return q->front->val;
}

// 队尾
TYPE rearLsitQueue(ListQueue *q) {
    return q->rear->val;
}

// 数量
size_t sizeListQueue(ListQueue *q) {
    return q->size;
}

// 销毁
void destroyListQueue(ListQueue *q) {
    while (!emptyListQueue(q)) {
        popListQueue(q);
    }
    free(q);
}

int main() {
    ListQueue *q = createListQueue();
    for (int i = 0; i < 10; ++i) {
        pushListQueue(q, i);
        printf("rear = %d, size = %lu\n", rearLsitQueue(q), sizeListQueue(q));
    }
    printf("++++++++++++++++++\n");
    while (!emptyListQueue(q)) {
        printf("front = %d, size = %lu\n", frontListQueue(q), sizeListQueue(q));
        popListQueue(q);
    }
    destroyListQueue(q);
    q = NULL;
}