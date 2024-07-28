/**
 *    title:  16平衡二叉树.c
 *    author:  sleeeeeping
 *    created:  2024-07-23 10:35:02
**/
#include <stdio.h>
#include <assert.h>
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

// 前序
void dlrShow(TreeNode *root) {
    if (root == NULL) return ;
    printf("%d ", root->val);
    dlrShow(root->left), dlrShow(root->right);
}

// 中序
void ldrShow(TreeNode *root) {
    if (root == NULL) return ;
    ldrShow(root->left);
    printf("%d ", root->val);
    ldrShow(root->right);
}

// 后序
void lrdShow(TreeNode *root) {
    if (root == NULL) return ;
    lrdShow(root->left), lrdShow(root->right);
    printf("%d ", root->val);
}

int max(int a, int b) { return a > b ? a : b; }

// 求高度
int highTree(TreeNode *root) {
    if (root == NULL) return 0;
    return max(highTree(root->left), highTree(root->right)) + 1;
}

// 计算左右子树高度差
int _highDiff(TreeNode *root) {
    if (root == NULL) return 0;
    return highTree(root->left) - highTree(root->right);
}

TreeNode *_rotateLeft(TreeNode *root) {
    TreeNode *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

TreeNode *_rotateRight(TreeNode *root) {
    TreeNode *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// 自动调整平衡 并返回调整后的根节点
TreeNode *autoBalance(TreeNode *root) {
    if (root == NULL) return NULL;
    int lh = highTree(root->left), rh = highTree(root->right);
    if (lh - rh > 1) {
        if (_highDiff(root->left) >= 0) { // 右旋
            root = _rotateRight(root);
        } else { // 先左旋再右旋
			root->left = _rotateLeft(root->left);
			root = _rotateRight(root);
		}
	} else if (rh - lh > 1) {
        if (_highDiff(root->right) <= 0) { // 左旋
            root = _rotateLeft(root);
        } else { // 先右旋再左旋
            root->right = _rotateRight(root->right);
            root = _rotateLeft(root);
        }
    }
    return root;
}

TreeNode *insertTree(TreeNode *root, int val) {
    if (root == NULL) {
        return createTreeNode(val);
    }
    if (val < root->val) {
        root->left = insertTree(root->left, val);
    } else {
        root->right = insertTree(root->right, val);
    }
    // 有可能添加后该位置破环平衡 需要调整
    return autoBalance(root);
}

TreeNode *findMaxNode(TreeNode *root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

TreeNode *findMinNode(TreeNode *root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode *deleteTree(TreeNode *root, int val) {
    if (root == NULL) return NULL;
    if (root->val == val) {
        if (root->right == NULL && root->left == NULL) {
            free(root);
            return NULL;
        }
        // 左空 替换为右子树
        if (root->left == NULL) {
            TreeNode *tmp = root->right;
            free(root);
            return tmp;
        }
        // 右空
        if (root->right == NULL) {
            TreeNode *tmp = root->left;
            free(root);
            return tmp;
        }
        if (_highDiff(root) >= 0) { // 左高于右
            TreeNode *max = findMaxNode(root->left);
            root->val = max->val;
            root->left = deleteTree(root->left, max->val);
        } else {
            TreeNode *min = findMinNode(root->right);
            root->val = min->val;
            root->right = deleteTree(root->right, min->val);
        }
        return autoBalance(root);
    }
    if (val < root->val) {
        root->left = deleteTree(root->left, val);
    } else {
        root->right = deleteTree(root->right, val);
    }
    return autoBalance(root);
}

int main() {
    TreeNode *root = NULL;
    for (int i = 1; i <= 10; ++i) {
        root = insertTree(root, i);
    }
    deleteTree(root, 4);
    dlrShow(root);
    printf("\n");
    ldrShow(root);
    printf("\n");
    lrdShow(root);
    printf("\n");
}