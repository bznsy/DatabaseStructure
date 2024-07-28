/**
 *    title:  18邻接表.c
 *    author:  sleeeeeping
 *    created:  2024-07-24 10:31:45
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

// 边结构
typedef struct Edge {
    int index; // 顶点下标
    struct Edge *next; // 下一条边
} Edge;

Edge *createEdge(int index) {
    Edge *edge = malloc(sizeof(Edge));
    edge->index = index;
    edge->next = NULL;
    return edge;
}

// 顶点结构
typedef struct Vertex {
    char ver; // 顶点数据
    Edge *first; // 第一条边
} Vertex;

typedef struct Graph {
    Vertex *v; // 顶点表 顺序
    int cnt; // 顶点数量
} Graph;

// 创建有顶点无边图
Graph *createGraph(const char *vertex) {
    Graph *graph = malloc(sizeof(Graph));
    // 计算顶点数量
    graph->cnt = strlen(vertex);
    graph->v = malloc(sizeof(Vertex) * graph->cnt);
    for (int i = 0; i < graph->cnt; ++i) {
        graph->v[i].ver = vertex[i];
        graph->v[i].first = NULL; //  初始化边链表指针
    }
    return graph;
}

void addEdge(Graph *g, char u, char v) {
    for (int i = 0; i < g->cnt; ++i) {
        if (u != g->v[i].ver) continue;
        for (int j = 0; j < g->cnt; ++j) {
            if (v !=  g->v[j].ver) continue;
            // 遍历v1的边链表是否已经存在到v2的边
            for (Edge *e = g->v[i].first; e != NULL; e = e->next) {
                if (e->index == j) return ;
            }
            Edge *edge = createEdge(j);
            edge->next = g->v[i].first;
            g->v[i].first = edge;
            return ;
        }
    }
    assert(false);
}

int outDegree(Graph *g, char v) {
    for (int i = 0; i < g->cnt; ++i) {
        if (v == g->v[i].ver) {
            int out = 0;
            for (Edge *e = g->v[i].first; e != NULL; e = e->next) {
                out += 1;
            }
            return out;
        }
    }
    assert(false);
    return -1;
}

int inDegree(Graph *g, char v) {
    for (int i = 0; i < g->cnt; ++i) {
        if (v == g->v[i].ver) {
            int in = 0;
            for (int u = 0; u < g->cnt; ++u) {
                for (Edge *e = g->v[u].first; e != NULL; e = e->next) {
                    if (e->index == i) {
                        in += 1;
                        break;
                    }
                }
            }
            return in;
        } 
    }
    assert(false);
    return -1;
} 

void _dfs(Graph *g, int u, bool *vflag) {
    printf("%c ", g->v[u].ver);
    vflag[u] = true;
    for (Edge *e = g->v[u].first; e != NULL; e = e->next) {
        if (!vflag[e->index]) {
            _dfs(g, e->index, vflag);
        }
    }
}

void dfsShow(Graph *g) {
    bool vflag[g->cnt];
    memset(vflag, 0, sizeof vflag);
    for (int i = 0; i < g->cnt; ++i) {
        _dfs(g, i, vflag);
    }
    printf("\n");
}

void showGraph(Graph *g) {
    for (int i = 0; i < g->cnt; ++i) {
        printf("%c : ", g->v[i].ver);
        for (Edge *e = g->v[i].first; e != NULL; e = e->next) {
            printf("%c ", g->v[e->index].ver);
        }
        printf("\n");
    }
}

int main() {
    const char *Vertex = "ABCDEFG";
    Graph *g = createGraph(Vertex);
    addEdge(g, 'A', 'B');
    addEdge(g, 'A', 'C');
    addEdge(g, 'A', 'D');
    addEdge(g, 'B', 'C');
    addEdge(g, 'B', 'E');
    addEdge(g, 'C', 'F');
    addEdge(g, 'C', 'G');
    addEdge(g, 'C', 'E');
    showGraph(g);
}