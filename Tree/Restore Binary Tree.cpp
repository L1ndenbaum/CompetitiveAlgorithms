#include "../Heads/Head.h"
string PreorderSequence, InorderSequence;
unordered_map<char, int> index; // 哈希表存位置
struct Node
{
    char data;
    Node *Lson;
    Node *Rson;
    Node() : data(0), Lson(nullptr), Rson(nullptr) {} // 结构体构造器 在结构体创建时自动调用，为成员赋初始值
} *TreeRoot;
void GetIndex()
{
    for (int i = 0; i < InorderSequence.length(); i++)
        index[InorderSequence[i]] = i;
}
void BuildTree(int PreL, int PreR, int InL, int InR, Node *&p) // 取Preorder[PreL,PreR]为前序,Inorder[InL,InR]为中序,构造一个p上的子树
{
    if (PreL > PreR) // 构造完成
    {
        p = nullptr;
        return;
    }
    p->data = PreorderSequence[PreL]; // 前序遍历第一个点即为当前根节点
    int Pos = index[p->data];         // 找到本次前序遍历第一个点在中序遍历中的位置
    BuildTree(PreL + 1, Pos - InL + PreL, InL, Pos - 1, p->Lson = new Node);
    // 左子树的中序遍历从InL开始,Pos-1结束,长度为Pos-InL,即下标差值+1
    // 那么左子树的前序遍历从 PreL+1 开始,到 Pos-InL+PreL(PreL+中序遍历长度-1) 结束
    BuildTree(Pos - InL + PreL + 1, PreR, Pos + 1, InR, p->Rson = new Node);
    // 右子树的中序遍历从Pos+1开始，到InR结束，长度为InR-Pos
    // 那么右子树的前序遍历从 PreL+Pos-InL+1(PreL+中序遍历长+1) 开始,到 PreR 结束
}
void DestroyTree(Node *Root)
{
    if (Root == nullptr)
        return;
    DestroyTree(Root->Lson);
    DestroyTree(Root->Rson);
    delete Root;
}
char *CreateBiTree(Node *&Root, char *str) // 根据带虚结点的前序遍历串构造二叉树
{
    if (*str == '#')
    {
        Root = nullptr;
        return str + 1;
    }
    Root = new Node;
    Root->data = *str;
    char *strAfterLeft = CreateBiTree(Root->Lson, str + 1);
    char *strAfterRight = CreateBiTree(Root->Rson, strAfterLeft);
    return strAfterRight;
}