#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
typedef struct node *listptr;

struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
};  // 二叉树节点

struct node {
    ElementType Element;
    int index;
    struct node *ptr;
};  // 数据存储链表节点

void preorder(Tree);
Tree createtree(listptr elementtype, int num);
int rec_bst(Tree, int);

int main() {
    Tree T1, T2;
    int num1, i, element, pindex;
    
    // 读取第一棵树
    scanf("%d", &num1);
    listptr elementlist1 = (listptr)malloc(num1 * sizeof(struct node));
    for (i = 0; i < num1; i++) {
        scanf("%d %d", &element, &pindex);
        elementlist1[i].Element = element;
        elementlist1[i].index = pindex;
    }
    T1 = createtree(elementlist1, num1);
    
    // 读取第二棵树
    int num2;
    scanf("%d", &num2);
    listptr elementlist2 = (listptr)malloc(num2 * sizeof(struct node));
    for (i = 0; i < num2; i++) {
        scanf("%d %d", &element, &pindex);
        elementlist2[i].Element = element;
        elementlist2[i].index = pindex;
    }
    T2 = createtree(elementlist2, num2);
    
    int target; // 目标数字
    scanf("%d", &target);

    // 结果链表初始化
    listptr result = (listptr)malloc(sizeof(struct node));
    result->Element = result->index = -1;
    result->ptr = NULL;

    listptr tmp = result;
    
    // 遍历第一棵树，在第二棵树中查找 target - 第一棵树的元素
    for (i = 0; i < num1; i++) {
        int rtarget = target - elementlist1[i].Element;
        if (rec_bst(T2, rtarget)) {
            tmp->Element = elementlist1[i].Element;
            tmp->index = rtarget;
            tmp->ptr = (listptr)malloc(sizeof(struct node));
            tmp = tmp->ptr;
            tmp->Element = tmp->index = -1;
            tmp->ptr = NULL;
        }
    }

    // 如果没有找到匹配元素
    if (result->Element == -1) {
        printf("false\n");
    } else {
        printf("true\n");
        
        // 删除重复元素
        listptr test1 = result;
        while (test1 != NULL && test1->Element != -1) {
            listptr prev = test1, curr = test1->ptr;
            while (curr != NULL && curr->Element != -1) {
                if (test1->Element == curr->index) {
                    prev->ptr = curr->ptr;
                    free(curr);
                    curr = prev->ptr;
                } else {
                    prev = curr;
                    curr = curr->ptr;
                }
            }
            test1 = test1->ptr;
        }
        
        // 输出结果
        while (result != NULL && result->Element != -1) {
            printf("%d + %d = %d\n", result->Element, result->index, target);
            result = result->ptr;
        }
    }

    preorder(T1);
    printf("\n");
    preorder(T2);
}

void preorder(Tree t) {
    if (t == NULL) return;
    printf("%d ", t->Element);
    preorder(t->Left);
    preorder(t->Right);
}

// 创建二叉树
Tree createtree(listptr elementtype, int num) {
    int i;
    Tree root = NULL;

    for (i = 0; i < num; i++) {
        Tree newNode = (Tree)malloc(sizeof(struct TreeNode));
        newNode->Element = elementtype[i].Element;
        newNode->Left = newNode->Right = NULL;

        if (elementtype[i].index == -1) {
            root = newNode;
            elementtype[i].ptr = root;
        } else {
            int j;
            for (j = 0; j < i; j++) {
                if (elementtype[j].index == elementtype[i].index) break;
            }
            Tree parent = elementtype[j].ptr;
            if (elementtype[i].Element <= parent->Element) {
                parent->Left = newNode;
            } else {
                parent->Right = newNode;
            }
            elementtype[i].ptr = newNode;
        }
    }
    return root;
}

// 优化的 BST 查找函数
int rec_bst(Tree t, int target) {
    if (t == NULL) return 0;
    if (t->Element == target) return 1;
    return (target < t->Element) ? rec_bst(t->Left, target) : rec_bst(t->Right, target);
}