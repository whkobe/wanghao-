#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define data_t char
typedef struct BiTNode
{
    //int num;节点编号(可选)
    data_t data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
char btree[]="AB#D##C##";//给定的遍历
void PreOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c  ",T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    InOrderTraverse(T->lchild);
    printf("%c  ",T->data);
    InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c  ",T->data);
}
BiTree CreateBiTree()//给定遍历结果（以前序为例）创建二叉树。遍历结果在全局变量数组btree中
{
    data_t data;
    static int i=0;//使用静态变量才能让不同层次的递归共用一个变量i从而得到btree内存储的值
    if(!strlen(btree))
    {
        printf("Can't Create Empty Bitree.\n");
        return NULL;
    }
    data = btree[i++];
    if(data=='#')//#表示此节点为空
        return NULL;
    else
    {
        BiTree T = (BiTree)malloc(sizeof(BiTNode));
        if(!T)
        {
            printf("CreateBiTree Error\n");
            exit(0);
        }
        T->data = data;
        T->lchild = CreateBiTree();
        T->rchild = CreateBiTree();
        return T;
    }
}
int main()
{
    BiTree root = CreateBiTree();
    printf("Preorder:\n");
    PreOrderTraverse(root);
    printf("\nInorder:\n");
    InOrderTraverse(root);
    printf("\nPostorder:\n");
    PostOrderTraverse(root);
    return 0;
}
