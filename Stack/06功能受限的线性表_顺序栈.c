/**
 *    title:  06功能受限的线性表_顺序栈.c
 *    author:  sleeeeeping
 *    created:  2024-07-18 10:44:55
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define TYPE int

// 设计顺序栈结构
typedef struct ArrayStack {
    TYPE *ptr; // 存储栈原元素的内存首地址
    size_t cap; // 栈的容量
    size_t top; // 记录栈顶的位置
} ArrayStack;

// 创建
ArrayStack *createArrayStack(size_t cap) {
    // 分配栈结构内存
    ArrayStack *stk = malloc(sizeof(ArrayStack));
    // 分配存储数据元素的内存
    stk->ptr = malloc(sizeof(TYPE) * cap);
    // 记录栈的容量
    stk->cap = cap;
    stk->top = 0;
}

// 销毁
void destroyArrayStack(ArrayStack *stk) {
    free(stk->ptr);
    free(stk);
}

// 栈空
bool emptyArrayStack(ArrayStack *stk) {
    return stk->top == 0;
}

// 栈满
bool fullArrayStack(ArrayStack *stk) {
    return stk->top == stk->cap;
}

// 入栈
void pushArrayStack(ArrayStack *stk, TYPE val) {
    assert(stk->top < stk->cap);
    stk->ptr[stk->top++] = val;
}

// 出栈
void popArrayStack(ArrayStack *stk) {
    assert(stk->top > 0);
    stk->top--;
}

// 查看栈顶
TYPE topArrayStack(ArrayStack *stk) {
    assert(stk->top > 0);
    return stk->ptr[stk->top - 1];
}

// 元素数量
size_t sizeArrayStack(ArrayStack *stk) {
    return stk->top;
}

int main() {
    ArrayStack *stk = createArrayStack(10);
    for (int i = 0; i < 10; ++i) {
        pushArrayStack(stk, i);
        printf("top = %d, size = %lu\n", topArrayStack(stk), sizeArrayStack(stk));
    }
    printf("+++++++++++++++++\n");
    while (!emptyArrayStack(stk)) {
        printf("top = %d, size = %lu\n", topArrayStack(stk), sizeArrayStack(stk));
        popArrayStack(stk);
    }
}