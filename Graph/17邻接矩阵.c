/**
 *    title:  17邻接矩阵.c
 *    author:  sleeeeeping
 *    created:  2024-07-23 17:05:16
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

// 设计邻接矩阵结构
typedef struct Graph {
    char *v; // 顶点数组
    char *e; // 边数组
    int cnt; // 顶点数量
} Graph;

// 创建邻接矩阵 只有顶点没有边
Graph *createGraph(const char *vertex) {
    // 申请图结构内存
    Graph *graph = malloc(sizeof(Graph));
    // 计算出顶点数量
    graph->cnt = strlen(vertex);
    // 申请存储顶点所需内存
    graph->v = malloc(graph->cnt);
    // 存储节点
    memcpy(graph->v, vertex, graph->cnt);
    // 申请存储边所需内存
    graph->e = calloc(graph->cnt, graph->cnt);
    return graph;
};

void addEdge(Graph *g, char u, char v) {
    int x = -1, y = -1;
    for (int i = 0; i < g->cnt; ++i) {
        if (u == g->v[i]) x = i;
        if (v == g->v[i]) y = i;
    } 
    assert(x != -1 && y != -1);
    g->e[x * g->cnt + y] = 1;
    // g->e[y * g->cnt + x] = 1;
}

// 计算顶点的出度
int outDegree(Graph *g, char v) {
    for (int i = 0; i < g->cnt; ++i) {
        if (v == g->v[i]) {
            int out = 0;
            for (int j = 0; j < g->cnt; ++j) {
                out += g->e[i * g->cnt + j];
            }
            return out;
        }
    }
    assert(false);
    return -1;
}

// 计算顶点的入度
int inDegree(Graph *g, char v) {
    for (int i = 0; i < g->cnt; ++i) {
        if (v == g->v[i]) {
            int in = 0;
            for (int j = 0; j < g->cnt; ++j) {
                in += g->e[j * g->cnt + i];
            }
            return in;
        }
    }
    assert(false);
    return -1;
}


void showGraph(Graph *g) {
    printf("  ");
    for (int i = 0; i < g->cnt; ++i) {
        printf("%c%c", g->v[i], " \n"[i == g->cnt - 1]);
    }
    for (int i = 0; i < g->cnt; ++i) {
        printf("%c ", g->v[i]);
        for (int j = 0; j < g->cnt; ++j) {
            printf("%hhd ", g->e[i * g->cnt + j]);
        }
        printf("out = %d, in = %d\n", outDegree(g, g->v[i]), inDegree(g, g->v[i]));
    }
}

// 对第i个顶深度优先遍历 vflag数组表示顶点是否被遍历标记
void _dfs(Graph *g, int u, bool *vflag) {
    if (u >= g->cnt || vflag[u]) return ;
    printf("%c ", g->v[u]);
    vflag[u] = true;
    for (int v = 0; v < g->cnt; ++v) {
        if (g->e[u * g->cnt + v]) {
            _dfs(g, v, vflag);
        }
    }
}

// 深度优先遍历
void dfsShow(Graph *g) {
    // 变长数组
    bool vflag[g->cnt];
    // 内存清零
    memset(vflag, 0, sizeof vflag);
    for (int i = 0; i < g->cnt; ++i) {
        _dfs(g, i, vflag);
    }
    printf("\n");
}

void bfsShow(Graph *g) {
    bool vflag[g->cnt];
    memset(vflag, 0, sizeof vflag);
    ListQueue *q = createListQueue();
    for (int i = 0; i < g->cnt; ++i) {
        if (inDegree(g, g->v[i]) == 0) {
            vflag[i] = true;
            pushListQueue(q, i);
        }
    }
    while (!emptyListQueue(q)) {
        int u = frontListQueue(q);
        popListQueue(q);
        printf("%c ", g->v[u]);
        for (int v = 0; v < g->cnt; ++v) {
            if (!vflag[v] && g->e[u * g->cnt + v]) {
                vflag[v] = true;
                pushListQueue(q, v);
            }
        } 
    }
    printf("\n");
    destroyListQueue(q);
}

int main() {
    const char *vertex = "ABCDEFG";
    Graph *g = createGraph(vertex);
    addEdge(g, 'A', 'B');
    addEdge(g, 'A', 'D');
    addEdge(g, 'A', 'C');
    addEdge(g, 'B', 'D');
    addEdge(g, 'B', 'F');
    addEdge(g, 'C', 'F');
    addEdge(g, 'D', 'E');
    addEdge(g, 'D', 'G');
    addEdge(g, 'E', 'F');
    addEdge(g, 'F', 'G');
    showGraph(g);
    dfsShow(g);
    bfsShow(g);
}