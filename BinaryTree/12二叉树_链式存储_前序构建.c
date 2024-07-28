/**
 *    title:  12二叉树_链式存储_前序构建.c
 *    author:  sleeeeeping
 *    created:  2024-07-19 16:30:01
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TREE_TYPE char
#define EMPTY '#'
#define END '\0'

// 设计二叉树节点结构
typedef struct TreeNode {
    TREE_TYPE val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建节点
TreeNode *createTreeNode(TREE_TYPE val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 按照前序顺序 构建二叉树
TreeNode *createTree() {
    TREE_TYPE val = 0;
    scanf("%c", &val);
    if (val == EMPTY) return NULL;
    // 创建根节点
    TreeNode *root = createTreeNode(val);
    root->left = createTree();
    root->right = createTree();
    return root;
}

// 第二种前序构建
TreeNode *createTreeStr(const char **str) {
    if (**str == EMPTY || **str == END) return NULL;
    // 构建当前的根节点
    TreeNode *root = createTreeNode(**str);
    *str += 1;
    root->left = createTreeStr(str);
    *str += 1;
    root->right = createTreeStr(str);
    return root;
}

// 前序
void dlrShow(TreeNode *root) {
    if (root == NULL) return ;
    printf("%c ", root->val);
    dlrShow(root->left), dlrShow(root->right);
}

// 中序
void ldrShow(TreeNode *root) {
    if (root == NULL) return ;
    ldrShow(root->left);
    printf("%c ", root->val);
    ldrShow(root->right);
}

// 后序
void lrdShow(TreeNode *root) {
    if (root == NULL) return ;
    lrdShow(root->left), lrdShow(root->right);
    printf("%c ", root->val);
}

int max(int a, int b) { return a > b ? a : b; }

// 树的高度
int highTree(TreeNode *root) {
    if (root == NULL) return 0;
    return max(highTree(root->left), highTree(root->right)) + 1;
}

// 树的密度
int densityTree(TreeNode *root) {
    if (root == NULL) return 0;
    return densityTree(root->left) + densityTree(root->right) + 1;
}

// 插入 把新节点插入到有空子树的父节点下 假设节点值不重复
bool insertTree(TreeNode *root, TREE_TYPE pval, TREE_TYPE val) {
    if (root == NULL) return false;
    if (root->val == pval) {
        if (root->left == NULL) {
            return root->left = createTreeNode(val);
        }
        if (root->right == NULL) {
            return root->right = createTreeNode(val);
        }
        return false;
    }
    if (insertTree(root->left, pval, val) || insertTree(root->right, pval, val)) {
        return true;
    }
    return false;

}

int main() {
    // TreeNode *root = createTree();   
    const char *str = "ABDG###EH##I##C#FJ###"; 
    TreeNode *root = createTreeStr(&str);
    dlrShow(root);
    printf("\n");
    ldrShow(root);
    printf("\n");
    lrdShow(root);
    printf("\n");
}