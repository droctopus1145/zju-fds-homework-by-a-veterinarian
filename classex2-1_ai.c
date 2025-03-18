#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};

typedef PtrToNode Polynomial;

Polynomial Read(); /* 读取多项式的函数 */
void Print(Polynomial p); /* 打印多项式的函数 */
Polynomial Add(Polynomial a, Polynomial b); /* 多项式加法函数 */

int main() {
    Polynomial a, b, s;
    a = Read();  // 读取第一个多项式
    b = Read();  // 读取第二个多项式
    s = Add(a, b);  // 计算多项式和
    Print(s);  // 打印结果
    return 0;
}

/* 读取多项式 */
Polynomial Read() {
    int num, i;
    Polynomial dummy = (Polynomial)malloc(sizeof(struct Node));  // 创建一个虚拟头结点
    dummy->Next = NULL;  // 头结点的 Next 指针初始化为 NULL
    Polynomial temp = dummy;  // temp 指针指向头结点

    scanf("%d", &num);  // 读取多项式的项数
    for (i = 0; i < num; i++) {
        int coef, exp;
        scanf("%d %d", &coef, &exp);  // 读取每一项的系数和指数

        Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));  // 创建新节点
        newNode->Coefficient = coef;  // 设置系数
        newNode->Exponent = exp;  // 设置指数
        newNode->Next = NULL;  // 新节点的 Next 指针初始化为 NULL

        temp->Next = newNode;  // 将新节点连接到链表
        temp = newNode;  // 更新 temp 为新节点
    }
    return dummy;  // 返回头结点
}

/* 打印多项式 */
void Print(Polynomial p) {
    Polynomial ptr = p->Next;  // 跳过虚拟头结点
    if (ptr == NULL) {
        printf("多项式为空\n");
        return;
    }

    while (ptr != NULL) {
        printf("%d %d", ptr->Coefficient, ptr->Exponent);  // 打印每一项
        if (ptr->Next != NULL) {
            printf(" ");  // 如果不是最后一项，打印空格
        }
        ptr = ptr->Next;  // 移动到下一个节点
    }
    printf("\n");
}

/* 多项式加法 */
Polynomial Add(Polynomial a, Polynomial b) {
    Polynomial output = (Polynomial)malloc(sizeof(struct Node));  // 创建一个虚拟头结点
    output->Next = NULL;  // 初始化虚拟头结点的 Next 指针
    Polynomial temp = output;  // temp 指针用于构建结果链表
    Polynomial ptra = a->Next;  // ptra 指向第一个多项式的第一个节点
    Polynomial ptrb = b->Next;  // ptrb 指向第二个多项式的第一个节点

    // 合并两个多项式
    while (ptra != NULL && ptrb != NULL) {
        if (ptra->Exponent < ptrb->Exponent) {  // ptra 的指数小，插入 ptrb 的项
            Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));
            newNode->Coefficient = ptrb->Coefficient;
            newNode->Exponent = ptrb->Exponent;
            newNode->Next = NULL;
            temp->Next = newNode;
            temp = newNode;
            ptrb = ptrb->Next;  // 移动 ptrb
        }
        else if (ptra->Exponent > ptrb->Exponent) {  // ptrb 的指数小，插入 ptra 的项
            Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));
            newNode->Coefficient = ptra->Coefficient;
            newNode->Exponent = ptra->Exponent;
            newNode->Next = NULL;
            temp->Next = newNode;
            temp = newNode;
            ptra = ptra->Next;  // 移动 ptra
        }
        else {  // 指数相等，合并系数
            int sum = ptra->Coefficient + ptrb->Coefficient;
            if (sum != 0) {  // 如果合并后的系数不为零，才插入该项
                Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));
                newNode->Coefficient = sum;
                newNode->Exponent = ptra->Exponent;
                newNode->Next = NULL;
                temp->Next = newNode;
                temp = newNode;
            }
            ptra = ptra->Next;  // 移动 ptra
            ptrb = ptrb->Next;  // 移动 ptrb
        }
    }

    // 如果 ptra 还有剩余项，直接添加
    while (ptra != NULL) {
        Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));
        newNode->Coefficient = ptra->Coefficient;
        newNode->Exponent = ptra->Exponent;
        newNode->Next = NULL;
        temp->Next = newNode;
        temp = newNode;
        ptra = ptra->Next;
    }

    // 如果 ptrb 还有剩余项，直接添加
    while (ptrb != NULL) {
        Polynomial newNode = (Polynomial)malloc(sizeof(struct Node));
        newNode->Coefficient = ptrb->Coefficient;
        newNode->Exponent = ptrb->Exponent;
        newNode->Next = NULL;
        temp->Next = newNode;
        temp = newNode;
        ptrb = ptrb->Next;
    }

    return output;  // 返回结果
}
