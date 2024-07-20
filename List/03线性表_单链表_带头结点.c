/**
 *    title:  03线性表_单链表_带头结点.c
 *    author:  sleeeeeping
 *    created:  2024-07-16 09:34:51
**/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct ListNode {
    TYPE val;
    struct ListNode* next;
} ListNode;

// 创建节点
ListNode *createListNode(TYPE val) {
    ListNode *node = malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// 带头结点的单链表结构

typedef struct List {
    ListNode *head; // 头指针
    ListNode *tail; // 尾指针
    size_t size; // 有效节点数量
} List;

// 创建单链表
List *createList() {
    // 分配链表结构内存
    List *list = malloc(sizeof(List));
    // 创建头结点
    list->head = createListNode(0);
    // 初始化尾节点
    list->tail = list->head;
    list->size = 0;
    return list;
}

// 头插
void headAddList(List *list, TYPE val) {
    // 创建新节点
    ListNode *node = createListNode(val);
    // 判断是否空表，如果是，则需要修改tail
    if (list->size == 0) {
        list->tail = node;
    }
    // node指向第一个有效节点
    node->next = list->head->next;
    // 头结点next指向node，node成为第一个有效节点
    list->head->next = node;
    // 长度 + 1;
    list->size += 1;
}

// 尾插
void tailAddList(List *list, TYPE val) {
    ListNode *node = createListNode(val);
    // 判断是否是空表，如果是，则新节点也是头节点的next
    if (list->size == 0) {
        list->head->next = node;
    }
    // 新节点node成为链表末尾
    // 原末尾节点的next指向新节点
    list->tail->next = node;
    // 更新tail指向，指向新的末尾节点
    list->tail = node;
    list->size += 1;
}

// 插入
void insertList(List *list, int index, TYPE val) {
    // 如果是空表则不允许插入
    assert(index >= 0 && index < list->size);
    ListNode *node = createListNode(val);
    ListNode *prev = list->head;
    while (index--) {
        prev = prev->next;
    }
    node->next = prev->next;
    prev->next = node;
    list->size += 1;
}

// 头删除
void headDelList(List *list) {
    // 判断是否为空表
    assert(list->size > 0);
    // 记录待删除的第一个节点
    ListNode *temp = list->head->next;
    // 把头结点的next改为指向新的第一个节点
    list->head->next = temp->next;
    free(temp);
    list->size -= 1;
    if (list->size == 0) {
        list->tail = list->head;
    }
    temp = NULL;
}

// 尾删除
void tailDelList(List *list) {
    assert(list->size > 0);
    // 由于需要删除节点需要拿到被删除节点的前驱，所以list->tail没有提供帮助
    ListNode *prev = list->head->next;
    while (prev->next != list->tail) {
        prev = prev->next;
    }
    // prev应是最后一个节点的前驱
    prev->next = NULL;
    free(list->tail);
    list->size -= 1;
    list->tail = prev;
}

// 按位置删除
void indexdelList(List *list, int index) {
    assert(index >= 0 && index < list->size);
    ListNode *prev = list->head;
    while (index--) {
        prev = prev->next;
    }
    ListNode *temp = prev->next;
    prev->next = temp->next;
    free(temp);
    list->size -= 1;
    // 如果删除的刚好是最后一个节点, 需要更新tail指向前一个
    if (temp == list->tail) {
        list->tail = prev;
    }
}

// 查询
ListNode *queryList(List *list, TYPE key) {
    for (ListNode *n = list->head->next; n != NULL; n = n->next) {
        if (key == n->val) {
            return n;
        }
    }
    return NULL;
}

// 访问
ListNode *askList(List *list, int index) {
    assert(index >= 0 && index < list->size);
    ListNode *node = list->head->next;
    while (index--) {
        node = node->next;
    }
    return node;
}

// 按值修改
void modifyValueList(List *list, TYPE old, TYPE val) {
    ListNode *node = queryList(list, old);
    while (node != NULL) {
        node->val = val;
        node = queryList(list, old);
    }
}

// 按位置修改
void modifyIndexList(List *list, int index, TYPE val) {
    assert(index >= 0 && index < list->size);
    ListNode *node = askList(list, index);
    node->val = val;
}

// 排序
void sortList(List *list) {
    for (ListNode *i = list->head->next; i->next != NULL; i = i->next) {
        ListNode *k = i;
        for (ListNode *j = i->next; j != NULL; j = j->next) {
            if (j->val < k->val) {
                k = j;
            }
        }
        if (k != i) {
            TYPE temp = i->val;
            i->val = k->val;
            k->val = temp;
        }
    }
}

// 合并 把l2链接到l1的末尾
void mergeList(List *l1, List *l2) {
    // l1的尾节点连接l2的第一个有效节点
    l1->tail->next = l2->head->next;
    l1->tail = l2->tail;
    // 长度合并
    l1->size += l2->size;
    // 把l2变成空表
    l2->head->next = NULL;
    l2->tail = l2->head;
    l2->size = 0;
}

ListNode *maxList(List *list) {
    assert(list->head->next != NULL);
    ListNode *max = list->head->next;
    for (ListNode *n = max->next; n != NULL; n = n->next) {
        if (n->val > max->val) {
            max = n;
        }
    }
    return max;
}

// 遍历
void showList(List *list) {
    printf("size = %lu\n", list->size);
    for (ListNode *n = list->head->next; n != NULL; n = n->next) {
        printf("%d%c", n->val," \n"[n->next == NULL]);
    }
}

int main() {
    List *list = createList();
    for (int i = 0; i < 5; ++i) {
        headAddList(list, i);
    }   
    modifyValueList(list, 0, -1);
    List *list1 = createList(), *list2 = createList();
    for (int i = 0; i < 5; ++i) {
        headAddList(list1, i), headAddList(list2, i + 10);
    }
    // printf("%d!\n", queryList(list, 3)->val);
    mergeList(list2, list1);
    mergeList(list1, list2);
    mergeList(list2, list1);
    showList(list1);
    showList(list2);
}