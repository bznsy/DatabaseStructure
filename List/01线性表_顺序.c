/**
 *    title:  线性表_顺序.c
 *    author:  sleeeeeping
 *    created:  2024-07-15 10:23:18
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 数据元素
typedef struct Student {
    char name[20];
    char sex;
    float score;
} Student;

// 数据结构 顺序表
typedef struct Array {
    Student *ptr; // 存储元素的内存首地址

    size_t cap;  // 表的容量
    size_t size; // 表中元素的数量
} Array;

// 创建
Array *creatArray(size_t cap) {
    // 给数据结构申请堆内存
    Array *arr = malloc(sizeof(Array));
    // 给存储数据元素申请堆内存
    arr->ptr = malloc(sizeof(Student) * cap);
    // 初始化表的容量
    arr->cap = cap;
    // 初始化元素数量
    arr->size = 0;
    // 返回该空的数据结构
    return arr;
}

// 销毁
void destroyArray(Array *arr) {
    free(arr->ptr);
    free(arr);
}

// 插入
bool insertArray(Array *arr, int index, const Student *pstu) {
    // if (arr->size >= arr->cap || index < 0 || index > arr->size) {
    //     return false;
    // }
    assert(arr->size < arr->cap);
    assert(index >= 0 && index <= arr->size);
    for (int i = arr->size; i > index; --i) {
        arr->ptr[i] = arr->ptr[i - 1];
    }
    arr->ptr[index] = *pstu;
    arr->size += 1;
    return true;
}

// 删除
bool deleteArray(Array *arr, int index) {
    // if (index < 0 || index > arr->size) {
    //     return false;
    // }
    assert(index >= 0 && index <= arr->size);
    for (int i = index; i < arr->size - 1; ++i) {
        arr->ptr[i] = arr->ptr[i + 1];
    }
    arr->size -= 1;
    return true;
}

// 修改
bool modifyArray(Array *arr, int index, const Student *pstu) {
    // if (index < 0 || index >= arr->size || pstu == NULL) {
    //     return false;
    // }
    assert(pstu != NULL);
    assert(index >= 0 && index < arr->size);
    arr->ptr[index] = *pstu;
    return true;
}

// 查询
int queryArray(Array *arr, const Student *pstu) {
    for (int i = 0; i < arr->size; ++i) {
        if (strcmp(pstu->name, arr->ptr[i].name) == 0) {
            return i;
        }
    }        
    return -1;
}

// 排序
void sortArray(Array *arr) {
    for (int i = 0; i < arr->size - 1; ++i) {
        int k = i;
        for (int j = i + 1; j < arr->size; ++j) {
            if (arr->ptr[k].score < arr->ptr[j].score) {
                k = j;
            }
        }
        if (k != i) {
            Student temp = arr->ptr[i];
            arr->ptr[i] = arr->ptr[k];
            arr->ptr[k] = temp;
        }
    }    
}

// 最大值
Student *maxArray(Array *arr) {
    int maxp = 0;
    for (int i = 1; i < arr->size; ++i) {
        if (arr->ptr[maxp].score < arr->ptr[i].score) {
            maxp = i;
        }
    }
    return arr->ptr + maxp;
}

// 最小值
Student *minArray(Array *arr) {
    int minp = 0;
    for (int i = 1; i < arr->size; ++i) {
        if (arr->ptr[minp].score < arr->ptr[i].score) {
            minp = i;
        }
    }
    return arr->ptr + minp;
}

// 合并
void mergeArray(Array *arr1, Array *arr2) {
    arr1->cap += arr2->cap;
    arr1->ptr = realloc(arr1->ptr, arr1->cap * sizeof(Student));
    for (int i = arr1->size, j = 0; j < arr2->size; ++j, ++i) {
        arr1->ptr[i] = arr2->ptr[j];
    }
    arr1->size += arr2->size;
}

// 遍历
void showArray(Array *arr) {
    printf("size: %lu\n", arr->size);
    for (int i = 0; i < arr->size; ++i) {
        printf("%s %c %g\n", 
            arr->ptr[i].name,
            arr->ptr[i].sex, 
            arr->ptr[i].score);
    }
}

int main() {
    Array *arr = creatArray(10);
    Student stu = {"heheM"};
    for (int i = 0; i < 5; ++i) {
        stu.name[4] -= i % 2 ? 1 : -1;
        stu.sex = i % 2 ? 'w' : 'm';
        stu.score = rand() % 150 / 1.0;
        insertArray(arr, 0, &stu);
    }
    showArray(arr);
    sortArray(arr);
    showArray(arr);
}
