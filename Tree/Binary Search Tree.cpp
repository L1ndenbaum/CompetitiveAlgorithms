// 二叉查找树BST
#include "../Heads/Head.h"
/*
二叉查找树的特征：
(1)每个节点有唯一的键值，可以比较大小
(2)在二叉查找树上，以任意节点为根的一棵子树仍然是而二叉查找树。
   任意节点的键值比它的左子树所有节点的键值大，比它的右子树所有节点的键值小。
   键值最大的节点没有右儿子，键值最小的节点没有左儿子。
(3)对二叉查找树进行中序遍历，即可得到一个有序排列。
(4)若按照给定的序列顺序进行插入，得到的二叉查找树一定唯一。
*/
struct Node // BST节点
{
    int key;
    struct Node *Lchild, *Rchild;
};
bool SearchNode(Node *Root, int Val) // 在以Root为根的子树中搜索Key为Val的节点
{
    if (!Root)
        return false;
    if (Root->key == Val)
        return true;
    else if (Root->key < Val)
        return SearchNode(Root->Rchild, Val);
    else
        return SearchNode(Root->Lchild, Val);
    return false;
}
Node *CreateNode(int Val) // 创建一个新的Key为Val的BST节点
{
    Node *temp = new Node;
    temp->key = Val;
    temp->Lchild = temp->Rchild = nullptr;
    return temp;
}
Node *InsertNode(Node *Root, int Val) // 向以Root为根的BST中插入Key为Val的节点
{
    // 这种插入方式不先查找一个节点是否存在也可以 因为如果已存在，不会进入if-else，而是直接return，进行自我赋值
    if (Root == nullptr) // 如果树是空的，返回一个树根节点
        return CreateNode(Val);
    // 否则递归地找到应该插入的位置
    if (Val < Root->key)
    {
        Root->Lchild = InsertNode(Root->Lchild, Val);
    }
    else if (Val > Root->key)
    {
        Root->Rchild = InsertNode(Root->Rchild, Val);
    }
    return Root; // 为了总存在返回值，故自己给自己赋值(Node->L/Rchild = return Node->L/Rchild)
}
Node *DeleteNode(Node *Root, int Val) // 删除以Root为根的子树中的一个Key为Val的节点
{
    /*
    删除节点有三种情况:
    (1)被删除的节点是一个叶子节点，直接delete后置为nullptr即可
    (2)被删除的节点有一个子树，可以直接用这个子树节点替换被删除的节点
    (3)被删除的节点有两个子树:为了不破坏二叉查找树的结构，选择一个节点去替换这个被删除的节点
                            这个节点可以是 左子树中最大的那个，也可以是 右子树中最小的那个
    */
    if (Root == nullptr)
        return Root;
    // 如果将被删除的节点的key小于当前根节点的key,那么这个要被删除的节点位于根节点的左子树上
    if (Val < Root->key)
    {
        Root->Lchild = DeleteNode(Root->Lchild, Val);
    }
    // 如果将被删除的节点的key大于当前根节点的key,那么这个要被删除的节点位于根节点的右子树上
    else if (Val > Root->key)
    {
        Root->Rchild = DeleteNode(Root->Rchild, Val);
    }
    // 如果将被删除的节点的key等于当前根节点的key,那么就找到了这个节点，进行删除
    else
    {
        // 被删除的节点没有孩子或者只有一个孩子的情况
        if (!Root->Lchild)
        {
            Node *temp = Root->Rchild;
            delete Root;
            return temp;
        }
        else if (!Root->Rchild)
        {
            Node *temp = Root->Lchild;
            delete Root;
            return temp;
        }
        // 被删除的节点有两个孩子的情况
        //  找到右子树key最小的节点
        Node *MinValNode = Root->Rchild;
        while (MinValNode && MinValNode->Lchild)
            MinValNode = MinValNode->Lchild;
        Root->key = MinValNode->key;                              // 将右子树最小节点的key复制到将要删除的节点
        Root->Rchild = DeleteNode(Root->Rchild, MinValNode->key); // 进行嫁接,也就是把MinValNode删除，这个过程中包含了修改MinValNode的指针的过程
    }
    return Root; // 返回当前节点:将不被删除的节点递归返回，形成原来的树
}
int GetHeight(Node *Root) // 求树高
{
    if (Root == nullptr)
    {
        return 0;
    }
    else // 分别计算左右子树树高 取最大值
    {
        int L_Depth = GetHeight(Root->Lchild);
        int R_Depth = GetHeight(Root->Rchild);
        if (L_Depth > R_Depth)
            return L_Depth + 1;
        else
            return R_Depth + 1;
    }
}
int NodeCount(struct Node *Node) // BST的节点总数
{
    if (Node == nullptr)
        return 0;
    else
        return NodeCount(Node->Lchild) + NodeCount(Node->Rchild) + 1; // 返回左子树节点总数 + 右子树节点总数 + 本节点(1)
}
void DeleteBST(Node *Root) // 销毁二叉搜索树
{
    if (Root == nullptr)
        return;
    DeleteBST(Root->Lchild);
    DeleteBST(Root->Rchild);
    cout << "\nReleased Node:" << Root->key;
    delete Root;
}
void InorderTraversal(Node *Root) // 中序遍历获得有序序列
{
    if (Root == nullptr)
        return;
    InorderTraversal(Root->Lchild);
    cout << Root->key << ' ';
    InorderTraversal(Root->Rchild);
}
