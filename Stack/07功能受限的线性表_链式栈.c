/**
 *    title:  07功能受限的线性表_链式栈.c
 *    author:  sleeeeeping
 *    created:  2024-07-18 14:16:49
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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

typedef struct ListStack {
    ListNode *top; // 栈顶指针 指向栈顶节点
    size_t size; // 节点数量
} ListStack;

ListStack *createListStack() {
    ListStack* stk = malloc(sizeof(ListStack));
    stk->top = NULL;
    stk->size = 0;
    return stk;
}

// 栈空
bool emptyListStack(ListStack* stk) {
    return stk->size == 0;
}

// 入栈
void pushListStack(ListStack* stk, TYPE val) {
    ListNode* node = createListNode(val);
    node->next = stk->top;
    stk->top = node;
    stk->size += 1;
}

// 出栈
void popListStack(ListStack* stk) {
    assert(stk->size > 0);
    ListNode* temp = stk->top;
    stk->top = stk->top->next;
    free(temp);
    stk->size -= 1;
}

TYPE topListStack(ListStack* stk) {
    return stk->top->val;
}

size_t sizeListStack(ListStack* stk) {
    return stk->size;
}

void destroyListStack(ListStack* stk) {
    while (!emptyListStack(stk)) {
        popListStack(stk);
    }
    free(stk);
}

int main() {

}