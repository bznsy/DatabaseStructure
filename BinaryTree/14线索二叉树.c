/**
 *    title:  14线索二叉树.c
 *    author:  sleeeeeping
 *    created:  2024-07-22 14:48:58
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
    bool rflag; // 右子树是否为线索 为真时，是线索
} TreeNode;

TreeNode *createNode(int val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    node->lflag = node->rflag = false; // 默认非线索
    return node;
}

void _insertTree(TreeNode **root, TreeNode *node) {
    if (*root == NULL) {
        *root = node;
    } else {
        if (node->val < (*root)->val) {
            _insertTree(&((*root)->left), node);
        } else {
            _insertTree(&((*root)->right), node);
        }
    }
}

// 搜索还是按照搜索二叉树的规则
void insertTree(TreeNode **root, int val) {
    TreeNode *node = createNode(val);
    _insertTree(root, node);
}

void ldrShow(TreeNode *root) {
    if (root == NULL) return ;
    ldrShow(root->left);
    printf("%d ", root->val);
    ldrShow(root->right);
}

// 按中序遍历时，当前节点的前一个节点
TreeNode *prev = NULL;
// 按照中序进行遍历并创建线索
void createClue(TreeNode *root) {
    if (root == NULL) return ;
    // 给左子树创建线索
    createClue(root->left);
    // 检查根节点是要要创建线索
    // 当prev指向树中节点 且prev的右子树为空 可以创建线索 指向下一个节点root
    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->rflag = true;
    }
    prev = root;
    createClue(root->right);
}

// 按照线索进行循环遍历 无序递归
void clueShow(TreeNode *root) {
    while (root != NULL) {
        while (root->left != NULL) {
            root = root->left;
        }
        printf("%d ", root->val);
        // roo右子树是线索 指向下一个节点
        while (root->rflag) {
            root = root->right;
            printf("%d ", root->val);
        }
        root = root->right;
    }
    printf("\n");
}

int main() {
    TreeNode *root = NULL;
    for (int i = 0; i < 10; ++i) {
        insertTree(&root, rand() % 100);
    }
    ldrShow(root);
    printf("\n");
    createClue(root);
    clueShow(root);
}