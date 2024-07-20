/**
 *    title:  list.c
 *    author:  sleeeeeping
 *    created:  2024-07-17 16:54:24
**/
#include <stdlib.h>
#include <assert.h>

#include "list.h"

// 创建节点
static ListNode *createNode(void *ptr) {
    ListNode *node = malloc(sizeof(ListNode));
    node->ptr = ptr;
    node->next = node;
    node->prev = node;
    return node;
}

// 创建链表
List *createList() {
    List *list = malloc(sizeof(List));
    list->head = createNode(NULL);
    list->size = 0;
    return list;
}

// 在两个节点之间插入新节点
static void _addList(ListNode *prev, ListNode *next, void *ptr) {
    ListNode *node = createNode(ptr);
    node->next = next, node->prev = prev;
    prev->next = node, next->prev = node;
}

// 删除节点
static void* _delList(ListNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    void *ptr = node->ptr;
    free(node->ptr);
    free(node);
    return ptr;
}

static void* _indexList(List *list, int index) {
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

static void* _valueList(List *list, void *ptr, fp cmp) {
    ListNode *node = list->head->next;
    while (node != list->head) {
        if (cmp(node->ptr, ptr) == 0) {
            return node;
        }
    }
    return NULL;
}

// 追加
void addList(List *list, void *ptr) {
    _addList(list->head->prev, list->head, ptr);
    list->size += 1;
}

// 插入
void insertList(List *list, int index, void *ptr) {
    assert(index >= 0 && index < list->size);
    ListNode *node = _indexList(list, index);
    _addList(node->prev, node, ptr);
    list->size += 1;
}

// 按位置删除
void deleteIndexList(List *list, int index) {
    assert(index >= 0 && index < list->size);
    _delList(_indexList(list, index));
    list->size -= 1;
}

// 按值删除
void deleteValueList(List *list, void *ptr, fp cmp) {
    ListNode *node = _valueList(list, ptr, cmp);
    while (node != NULL) {
        _delList(node);
        node = _valueList(list, ptr, cmp);
        list->size -= 1;
    }
}

// 查询
void *queryList(List *list, void *ptr, fp cmp) {
    return _valueList(list, ptr, cmp);
}

// 访问
void *askList(List *list, int index) {
    assert(index >= 0 && list->size > index);
    return _indexList(list, index);
}

// 排序
void sortList(List *list, fp cmp) {
    assert(list != NULL);
    for (ListNode *i = list->head->next; i->next != list->head; i = i->next) {
        ListNode *k = i;
        for (ListNode *j = i->next; j != list->head; j = j->next) {
            if (cmp(k->ptr, j->ptr) < 0) {
                k = i;
            }
        }
        if (k != i) {
            void *temp = k->ptr;
            i->ptr = k->ptr;
            k->ptr = temp;
        }
    }
}

// 清空
void clearList(List *list) {
    ListNode *node = list->head->next;
    while (node != list->head) {
        ListNode *temp = node;
        node = node->next;
        free(temp);
    }
    list->size = 0;
    list->head->prev = list->head;
    list->head->next = list->head;
}

// 销毁
void destoryList(List *list) {
    clearList(list);
    free(list->head);
    free(list);
}


// 访问
void *askList(List *list, int index) {
    assert(index >= 0 && index < list->size);
    return _indexList(list, index);
}


// 遍历
void showList(List *list, void (*show)(const void *)) {
    for (ListNode *i = list->head->next; i != list->head; i = i->next) {
        show(i->ptr);
    }
}