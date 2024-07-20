/**
 *    title:  05线性表_Linux内核链表.c
 *    author:  sleeeeeping
 *    created:  2024-07-17 14:44:11
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 遍历
#define listForEach(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

// 计算出结构体type成员mem所在的地址距离第一个成员位置的字节数
#define offsetof(type, member) \
    ((unsigned long)(&(((type *)0)->member)))

/**
 * 根据结构成员member的地址(ptr) 计算出它所在结构(type)变量的首地址
 * @ptr: 要计算的某个节点的地址
 * @type: ptr所在结构体名
 * @member: 结构体成员名
**/
#define container_of(ptr, type, member) \
    (type *)((char *)ptr - offsetof(type, member))

// 设计Linux内核链表节点
typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

// 创建Linux内核链表
Node *createList() {
    Node *head = malloc(sizeof(Node));
    head->prev = head;
    head->next = head;
    return head;
}

// 添加
void _addList(Node *prev, Node *next, Node *node) {
    prev->next = node, next->prev = node;
    node->next = next, node->prev = prev;
}

// 头添加
void headAddList(Node *head, Node *node) {
    _addList(head, head->next, node);
}

/**
 * 以上是内核链表通用代码
 * 以下是用户使用内核链表时编写的代码
**/

typedef struct Stu {
    Node node;
    char name[20];
    char sex;
    int age;
    float score;
    int id;
} Stu;


int main() {
    // 创建一个带头节点的链表
    Node *head = createList();
    for (int i = 0; i < 10; ++i) {
        Stu *stu = malloc(sizeof(Stu));

        // printf("%p %p\n", stu, &stu->node);
        // printf("%p %p\n\n", (Stu *)0, &(((Stu *)0)->node));

        sprintf(stu->name, "hehe%d", i);
        stu->sex = i % 2 ? 'w' : 'm';
        stu->age = 18 + i;
        stu->score = rand() % 100;
        stu->id = 1001 + i;
        headAddList(head, &stu->node);
    }
    Node *n = NULL;
    listForEach(n, head) {
        Stu *stu = container_of(n, Stu, node);
        printf("%s %c\n", stu->name, stu->sex);
    }
}