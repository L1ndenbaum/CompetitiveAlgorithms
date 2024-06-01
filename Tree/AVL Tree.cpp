#include "../Heads/Head.h"
// 平衡二叉树
/*
平衡二叉树是一种优化过的二叉搜索树
[1]具有二叉搜索树的所有特征
[2]定义一个节点的平衡因子 = 左子树高度-右子树高度 保证这个平衡因子不会大于1或小于-1
*/
struct Node
{
    int key;
    int height;
    Node *Lchild, *Rchild;
};
int GetHeight(Node *Root) // 读取以Root为根的子树的树高
{
    if (!Root)
        return 0;
    return Root->height;
}
Node *CreateNode(int Val) // 返回一个值为Val的新节点
{
    Node *newNode = new Node;
    newNode->key = Val;
    newNode->Lchild = NULL, newNode->Rchild = NULL;
    newNode->height = 1; // 新节点在插入时一定是一个叶子节点 故高为1
    return newNode;
}
Node *RightRotate(Node *Root) // 将以Root为根的子树右旋
{
    Node *x = Root->Lchild;
    Node *subtree_x = x->Rchild;
    Root->Lchild = subtree_x;
    x->Rchild = Root;
    Root->height = max(GetHeight(Root->Lchild), GetHeight(Root->Rchild)) + 1;
    x->height = max(GetHeight(x->Lchild), GetHeight(x->Rchild)) + 1;
    return x;
}
Node *LeftRotate(Node *Root) // 将以Root为根的子树左旋
{
    Node *x = Root->Rchild;
    Node *subtree_x = x->Lchild;
    x->Lchild = Root;
    Root->Rchild = subtree_x;
    Root->height = max(GetHeight(Root->Lchild), GetHeight(Root->Rchild)) + 1;
    x->height = max(GetHeight(x->Lchild), GetHeight(x->Rchild)) + 1;
    return x;
}
int GetBalanceFactor(Node *Root) // 获取一个节点的平衡因子
{
    if (!Root)
        return 0;
    return GetHeight(Root->Lchild) - GetHeight(Root->Rchild);
}
Node *InsertNode(Node *Root, int Val) // 将值为Val的节点插入以Root为根的子树中 并返回这个子树的新根(因为可能旋转)
{
    // 首先执行普通的BST插入操作
    if (!Root)
        return CreateNode(Val);
    if (Root->key < Val)
        Root->Rchild = InsertNode(Root->Rchild, Val);
    else if (Root->key > Val)
        Root->Lchild = InsertNode(Root->Lchild, Val);
    else // 有相同值在AVL树中，直接返回
        return Root;
    Root->height = max(GetHeight(Root->Lchild), GetHeight(Root->Rchild)) + 1; // 更新父节点的高度
    int BalanceFactor = GetBalanceFactor(Root);                               // 获取父节点平衡因子来检查这个节点是否不平衡
    if (BalanceFactor > 1 && Val < Root->Lchild->key) // LL情况
        return RightRotate(Root);
    if (BalanceFactor < -1 && Val > Root->Rchild->key) // RR情况
        return LeftRotate(Root);
    if (BalanceFactor > 1 && Val > Root->Lchild->key) // LR情况
    {
        Root->Lchild = LeftRotate(Root->Lchild);
        return RightRotate(Root);
    }
    if (BalanceFactor < -1 && Val < Root->Rchild->key) // RL情况
    {
        Root->Rchild = RightRotate(Root->Rchild);
        return LeftRotate(Root);
    }
    return Root;
}
void InorderTraversal(Node *Root)
{
    if (Root == NULL)
        return;
    InorderTraversal(Root->Lchild);
    cout << Root->key << ' ';
    InorderTraversal(Root->Rchild);
}