#include <stdio.h>
typedef struct treenode *ptrtonode;
struct treenode
{
    int element;
    ptrtonode firstchild;//第一子结点（靠次结点连接其他节点）
    ptrtonode nextsibling;//下一兄弟节点（父结点的其他子节点）
}
    