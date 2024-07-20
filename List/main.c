/**
 *    title:  main.c
 *    author:  sleeeeeping
 *    created:  2024-07-17 17:11:41
**/
#include <stdlib.h>

#include "list.h"

typedef struct Stu {
    char name[20];
    char sex;
    int id;
} Stu;

void showStu(void *ptr) {
    Stu *stu = ptr;
    printf("%s %c %d\n",
        stu->name, stu->sex, stu->id);
}

int main() {
    List *list = createList();
    for (int i = 0; i < 10; ++i) {
        Stu *stu = malloc(sizeof(Stu));
        sprintf(stu->name, "hehe%d", i);
        stu->sex = i % 2 ? 'w' : 'm';
        stu->id = 1001 + i;
        addList(list, stu);
    }
    showList(list, showStu);
}