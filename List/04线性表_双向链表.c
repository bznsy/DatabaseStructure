/**
 *    title:  04线性表_双向链表.c
 *    author:  sleeeeeping
 *    created:  2024-07-17 10:01:39
**/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct ListNode {
    struct ListNode *prev;
    TYPE val;
    struct ListNode *next;
} ListNode;

// 创建节点
ListNode *createListNode(TYPE val) {
    ListNode *node = malloc(sizeof(ListNode));
    node->val = val;
    // 要满足循环链表的特点
    node->prev = node;
    node->next = node;
    return node;
}

// 设计双向循环链表结构
typedef struct DoubleList {
    ListNode *head; // 头结点
    // 因为双向循环链表可以通过头节点的前驱找到最后一个节点，因此不需要tail指针
    size_t size; // 节点数量
} DoubleList;

// 创建链表
DoubleList *createDoubleList() {
    DoubleList *list = malloc(sizeof(DoubleList));
    list->head = createListNode(0); // 头节点不存储有效数据
    list->size = 0;
    return list;
}

// 在两个节点之间插入一个节点
// 以下划线开头的函数，为普通函数的依赖函数，一般不给用户直接使用
void _addList(ListNode *p, ListNode *n, TYPE val) {
    ListNode *node = createListNode(val);
    node->prev = p, node->next = n;
    n->prev = node, p->next = node;
}

// 删除某个节点
void _delList(ListNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

ListNode *_dataList(DoubleList *list, TYPE val) {
    for (ListNode *i = list->head->next; i != list->head; i = i->next) {
        if (i->val == val) {
            return i;
        }
    }
    return NULL;
}

// 根据指定位置访问对应节点
ListNode *_indexList(DoubleList *list, int index) {
    assert(index >= 0 && index < list->size);
    if (index > list->size / 2) {
        index = list->size - index - 1;
        ListNode *prev = list->head->prev;
        while (index--) {
            prev = prev->prev;
        }
        return prev;
    } else {
        ListNode *next = list->head->prev;
        while (index--) {
            next = next->next;
        }
        return next;
    }
}

// 头添加
void headAddList(DoubleList *list, TYPE val) {
    _addList(list->head, list->head->next, val);
    list->size += 1;
}

// 尾添加
void tailAddList(DoubleList *list, TYPE val) {
    _addList(list->head->prev, list->head, val);
    list->size += 1;
}

// 插入
void insertList(DoubleList *list, int index, TYPE val) {
    assert(index >= 0 && index < list->size);
    ListNode *n = _indexList(list, index);
    _addList(n->prev, n->next, val);
    list->size += 1;
}

// 头删除
void headDelList(DoubleList *list) {
    assert(list->size > 0);
    _delList(list->head->next);
    list->size -= 1;
}

// 尾删除
void tailDelList(DoubleList *list) {
    assert(list->size > 0);
    _delList(list->head->prev);
    list->size -= 1;
}

// 按位置删除
void indexDelList(DoubleList *list, int index) {
    assert(index >= 0 && index < list->size);
    ListNode *node = _indexList(list, index);
    _delList(node);
    list->size -= 1;
}

// 按值修改
void modifyValueList(DoubleList *list, TYPE old, TYPE val) {
    ListNode *node = _dataList(list, old);
    if (node != NULL) {
        node->val = val;
    }
}

// 访问
ListNode *queryList(DoubleList *list, int index) {
    assert(index >= 0 && index < list->size);
    return _indexList(list, index);
}

// 查询
ListNode *askList(DoubleList *list, TYPE val) {
    return _dataList(list, val);
}

// 按值删除
ListNode *valueDelList(DoubleList *list, TYPE val) {
    ListNode *node = _dataList(list, val);
    if (node != NULL) {
        _delList(node);
        list->size -= 1;
    }
}

// 清空链表
void clearList(DoubleList *list) {
    ListNode *node = list->head->next;
    while (node != list->head) {
        ListNode *temp = node;
        node = node->next;
        free(temp);
    }
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
}

// 销毁
void destroyList(DoubleList *list) {
    clearList(list);
    free(list->head);
    free(list);
}

// 遍历
void showList(DoubleList *list) {
    for (ListNode *i = list->head->next; i != list->head; i = i->next) {
        printf("%d%c", i->val, " \n"[i->next == list->head]);
    }
}

int main() {
    DoubleList *list = createDoubleList();
    for (int i = 0; i < 5; ++i) {
        tailAddList(list, i);
    }    
    showList(list);
}