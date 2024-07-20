/**
 *    title:  02线性表_单链表_不带头节点.c
 *    author:  sleeeeeping
 *    created:  2024-07-15 15:16:59
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define TYPE int

typedef struct ListNode {
    TYPE val; //数据域
    struct ListNode *next; // 指针域
} ListNode;

// 创建节点
ListNode *creatListNode(TYPE val) {
    // 给节点分配堆内存
    ListNode *node = malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// 头添加 链表不会满
void headAddListNode(ListNode **head, TYPE val) {
    ListNode *node = creatListNode(val);
    node->next = *head;
    *head = node;
}

// 尾添加
void tailAddListNode(ListNode **head, TYPE val) {
    ListNode *node = creatListNode(val);
    if (*head == NULL) {
        *head = node;
    } else {
        ListNode *n = *head; 
        while (n->next != NULL) {
            n = n->next;
        }
        n->next = node;
    }
}

// 插入
void insertListNode(ListNode **head, int index, TYPE val) {
    assert(index >= 0);
    ListNode *node = creatListNode(val);
    if (head == NULL) {
        *head = node;
    } else if (index == 0) {
        node->next = *head;
        *head = node;
    } else {
        ListNode *prev = *head;
        while (--index && prev->next != NULL) {
            prev = prev->next;
        }
        assert(index == 0);
        node->next = prev->next;
        prev->next = node;
    }
}
 
// 头删除
void headDelList(ListNode **head) {
    assert(*head != NULL);
    // 记录待删除节点
    ListNode *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// 尾删除
void tailDelList(ListNode **head) {
    assert(*head != NULL);
    ListNode *prev = *head;
    if (prev->next == NULL) {
        free(prev);
        *head = NULL;
    } else {
        while (prev->next->next != NULL) {
            prev = prev->next;
        }
        free(prev->next);
        prev->next = NULL;
    }
}

// 按位置删除
void indexDelList(ListNode **head, int index) {
    assert(head != NULL);
    assert(index >= 0);
    if (index == 0) {
        headDelList(head);
    } else {
        ListNode *prev = *head;
        while (--index && prev->next != NULL) {
            prev = prev->next;
        }
        assert(prev->next != NULL);
        ListNode *temp = prev->next;
        prev->next = temp->next;
        free(temp);
    }
}

void showList(ListNode *head) {
    for (ListNode *n = head; n != NULL; n = n->next) {
        printf("%d%c", n->val, " \n"[n->next == NULL]);
    }
}

int main() {
    ListNode *head = NULL;
    for (int i = 0; i < 5; ++i) {
        tailAddListNode(&head, i);
    }
    insertListNode(&head, 5, 6);
    indexDelList(&head, 5);
    showList(head);
}