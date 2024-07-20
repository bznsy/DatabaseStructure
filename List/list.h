/**
 *    title:  list.h
 *    author:  sleeeeeping
 *    created:  2024-07-17 16:53:59
**/
#ifndef _LIST_H__
#define _LIST_H__

#include <stdio.h>
#include <stdbool.h>

// 通用链表节点
typedef struct ListNode {
    void *ptr;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

// 通用链表结构 
typedef struct List {
    ListNode *head;
    size_t size;
} List;

// 创建链表
List *createList();

// 追加
void addList(List *, void *);

// 插入
void insertList(List *, int, void *);

// 遍历
void showList(List *, void (* )(const void *));

// 按位置删除
void deleteIndexList(List *, int);

typedef int (*fp)(const void *, const void *);

// 按值删除
void deleteValueList(List *, void *, fp);


// 查询
void *queryList(List *, void *, fp);

// 访问
void *askList(List *, int );

// 排序
void sortList(List *, fp);

// 清空
void clearList(List *);

// 销毁
void destoryList(List *);

#endif // _LIST_H__