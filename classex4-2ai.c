#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
};

// 函数声明
void zprint(Tree tree, int num);
Tree remaketree(int* inorder, int* postorder, int indexleft, int indexright, int *postIndex);

int main() {
    // 读取输入数据
    int num, i;
    scanf("%d", &num);
    int inorder[num], postorder[num];

    for (i = 0; i < num; i++)
        scanf("%d", &inorder[i]);
    for (i = 0; i < num; i++)
        scanf("%d", &postorder[i]);

    int postIndex = num - 1;  // 传递后序数组的最后一个索引
    Tree root = remaketree(inorder, postorder, 0, num - 1, &postIndex);
    zprint(root, num);

    return 0;
}

// 递归重建二叉树
Tree remaketree(int* inorder, int* postorder, int indexleft, int indexright, int *postIndex) {
    if (indexleft > indexright) return NULL; // 递归终止条件

    Tree root = (Tree)malloc(sizeof(struct TreeNode));
    if (!root) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    root->Element = postorder[*postIndex]; // 取后序遍历的当前根节点
    (*postIndex)--; // 移动后序索引

    // 在中序遍历中找到根节点位置
    int i;
    for (i = indexleft; i <= indexright; i++) {
        if (inorder[i] == root->Element)
            break;
    }

    // 递归构建右子树（先右后左，保证后序索引正确）
    root->Right = remaketree(inorder, postorder, i + 1, indexright, postIndex);
    root->Left = remaketree(inorder, postorder, indexleft, i - 1, postIndex);

    return root;
}

// 之字形层序遍历
void zprint(Tree tree, int num) {
    if (!tree) return;

    Tree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = tree; // 入队根节点

    int flag = 0; // 0 代表从右向左，1 代表从左向右
    while (front < rear) {
        int size = rear - front;
        Tree stack[size]; // 反向存储当前层的节点
        int top = -1;

        for (int i = 0; i < size; i++) {
            Tree node = queue[front++];
            if (flag == 0) { // 反向存入栈
                stack[++top] = node;
            } else { // 直接打印
                printf("%d ", node->Element);
            }

            // 正常入队下一层
            if (node->Left) queue[rear++] = node->Left;
            if (node->Right) queue[rear++] = node->Right;
        }

        // 反向打印
        while (top >= 0) {
            printf("%d ", stack[top--]->Element);
        }

        flag = !flag; // 交换方向
    }
}
