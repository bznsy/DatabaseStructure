/**
 *    title:  13搜索二叉树.c
 *    author:  sleeeeeping
 *    created:  2024-07-22 10:19:38
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTreeNode(int val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 插入
// void insertTree(TreeNode **root, int val) {
//     if (*root == NULL) {
//         *root = createTreeNode(val);
//     } else {
//         if (val < (*root)->val) {
//             insertTree(&((*root)->left), val);
//         } else {
//             insertTree(&((*root)->right), val);
//         }
//     }
// }

// 插入2

TreeNode *_insertTree(TreeNode *root, TreeNode *node) {
    if (node == NULL) return root;
    if (root == NULL) return node;
    if (node->val < root->val) {
        root->left = _insertTree(root->left, node);
    } else {
        root->right = _insertTree(root->right, node);
    }
    return root;
}

TreeNode *insertTree(TreeNode *root, int val) {
    TreeNode *node = createTreeNode(val);
    return _insertTree(root, node);
}


void dlrShow(TreeNode *root) {
    if (root == NULL) return ;
    printf("%d ", root->val);
    dlrShow(root->left), dlrShow(root->right);
}

void ldrShow(TreeNode *root) {
    if (root == NULL) return ;
    ldrShow(root->left);
    printf("%d ", root->val);
    ldrShow(root->right);
}

void lrdShow(TreeNode *root) {
    if (root == NULL) return ;
    lrdShow(root->left), lrdShow(root->right);
    printf("%d ", root->val);
}

// 查找
bool queryTree(TreeNode *root, int val) {
    if (root == NULL) return false;
    if (root->val == val) {
        return true;
    } else if (root->val > val) {
        return queryTree(root->left, val);
    } else {
        return queryTree(root->right, val);
    }
}

// 销毁
void destroyTree(TreeNode *root) {
    if (root == NULL) return ;
    destroyTree(root->left), destroyTree(root->right);
    free(root);
}

// 按值删除
// void delTree(TreeNode **root, int val) {
//     if (*root == NULL) return ;
//     if ((*root)->val == val) {
//         // 备份待删除节点tmp
//         TreeNode *tmp = *root;
//         // 让root指向左子树
//         *root = tmp->left;
//         // 让原来右子树往原来左子树插入
//         *root = _insertTree(*root, tmp->right);
//         // 删除节点
//         free(tmp);
//     }
//     if (val < (*root)->val) {
//         delTree(&((*root)->left), val);
//     } else {
//         delTree(&((*root)->right), val);  
//     }
// }

// 第二种删除 无需二级指针 通过返回值返回
TreeNode *delTree(TreeNode *root, int val) {
    if (root == NULL) return root;
    if (root->val == val) {
        // 把右子树插到左子树中 并记录插入后的左子树根节点
        TreeNode *tmp = _insertTree(root->left, root->right);
        // 删除原来的根节点
        free(root);
        return tmp;
    }
    if (val < root->val) {
        root->left = delTree(root->left, val);
    } else {
        root->right = delTree(root->right, val);  
    }
    return root;
}

int main() {
    TreeNode *root = NULL;
    for (int i = 0; i < 10; ++i) {
        int val = rand() % 100;
        printf("%d%c", val, " \n"[i == 9]);
        root = insertTree(root, val);
    }
    dlrShow(root);
    printf("\n");
    ldrShow(root);
    printf("\n");
    lrdShow(root);
    printf("\n");
    root = delTree(root, 83);
    printf("%d?\n", queryTree(root, 83));
}