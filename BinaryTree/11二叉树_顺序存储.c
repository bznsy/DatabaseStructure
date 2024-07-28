/**
 *    title:  11二叉树_顺序存储.c
 *    author:  sleeeeeping
 *    created:  2024-07-19 14:10:34
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "queue.h"

#define TREE_TYPE char
#define EMPTY '#'

// 顺序二叉树结构
typedef struct BinTree {
    TREE_TYPE *ptr;
    size_t cap;
} BinTree;

// 构建二叉树
// 根据提供的完全二叉树层序遍历的结果，来构建堆内存中的二叉树
BinTree *createTree(TREE_TYPE *arr, size_t len) {
    BinTree *tree = malloc(sizeof(BinTree));
    tree->ptr = malloc(sizeof(TREE_TYPE) * len);
    memcpy(tree->ptr, arr, sizeof(TREE_TYPE) * len);
    tree->cap = len;
    return tree;
}

// 前序遍历 preOrder
// 在tree中的第index编号节点开始 进行前序遍历
void _dlrShow(BinTree *tree, size_t u) {
    if (u > tree->cap || tree->ptr[u - 1] == EMPTY) {
        return ;
    }
    // 访问根节点
    printf("%c ", tree->ptr[u - 1]);
    // 对左右子树遍历
    _dlrShow(tree, u << 1), _dlrShow(tree, u << 1 | 1);
}

void dlrShow(BinTree *tree) {
    _dlrShow(tree, 1);
    printf("\n");
}

void _ldrShow(BinTree *tree, size_t u) {
    if (u > tree->cap || tree->ptr[u - 1] == EMPTY) {
        return ;
    }
    _ldrShow(tree, u << 1);
    printf("%c ", tree->ptr[u - 1]);
    _ldrShow(tree, u << 1 | 1);
}

// 中序
void ldrShow(BinTree *tree) {
    _ldrShow(tree, 1);
    printf("\n");
}

void _lrdShow(BinTree *tree, size_t u) {
    if (u > tree->cap || tree->ptr[u - 1] == EMPTY) {
        return ;
    }
    _lrdShow(tree, u << 1), _lrdShow(tree, u << 1 | 1);
    printf("%c ", tree->ptr[u - 1]);
}

// 后序
void lrdShow(BinTree *tree) {
    _lrdShow(tree, 1);
    printf("\n");
}

// 层序遍历 借助队列
void layerShow(BinTree *tree) {
    ListQueue *q = createListQueue();
    pushListQueue(q, 1);
    while (!emptyListQueue(q)) {
        int u = frontListQueue(q);
        popListQueue(q);
        printf("%c ", tree->ptr[u - 1]);
        int l = u << 1, r = u << 1 | 1;
        if (tree->ptr[l - 1] != EMPTY && l <= tree->cap) {
            pushListQueue(q, l);
        }
        if (tree->ptr[r - 1] != EMPTY && r <= tree->cap) {
            pushListQueue(q, r);
        }
    }
    destroyListQueue(q);
    printf("\n");
}

int max(int a, int b) { return a > b ? a : b; }

int _highTree(BinTree *tree, int u) {
    if (u > tree->cap || tree->ptr[u - 1] == EMPTY) {
        return 0;
    }
    return max(_highTree(tree, u << 1), _highTree(tree, u << 1 | 1)) + 1;
}

// 树的高度
int highTree(BinTree *tree) {
    return _highTree(tree, 1);
}

int _densityTree(BinTree *tree, int u) {
    if (u > tree->cap || tree->ptr[u - 1] == EMPTY) {
        return 0;
    }
    return 1 + _densityTree(tree, u << 1) + _densityTree(tree, u << 1 | 1);
}

// 树的密度
int densityTree(BinTree *tree) {
    return _densityTree(tree, 1);
}

int main() {
    char *str = "ABCDE#FG#HI##J";
    BinTree *tree = createTree(str, strlen(str));
    layerShow(tree);
    printf("high = %d\n", highTree(tree));
    printf("density = %d\n", densityTree(tree));
}