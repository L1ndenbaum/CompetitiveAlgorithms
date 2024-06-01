#include "../Heads/Head.h"
// B树

/*
B树是一种能轻松处理大量数据的结构 是自我平衡树的一种
B树中一个节点可以存储多个Key 降低树高
B树被广泛应用于硬盘设备，闪存，CD-ROM 这些需要存储大量数据的存储系统中
B树通过确保每个节点都有一个最小的Key数来保持平衡。
*/

/*
B树的性质:
[1]所有叶子节点都在同一层
[2]定义term minimum degree 't' :t的值由磁盘块大小决定
[3]除根节点外的每个节点必须最多只能有 t-1 个Key，根节点必须最少有 1个Key
[4]包括根节点在内的所有节点最多有 2*t-1 个Key
[5]一个节点的孩子数 = 此节点的Key数 + 1
[6]一个节点的所有Key都是升序排列的
[7]B树变高或变矮都在根节点上发生(不同于二叉树，在底部发生)
[8]对B树的一个节点执行插入操作只在叶子节点发生
[9]设B树的节点数为N,一个节点拥有的最大孩子数为M,非根节点拥有的最小孩子数为T则：
    B树的最小高度Height_Min=ceil(log(N + 1) ,以M为底) - 1
    B树的最大高度Height_Max=floor(log( (N+1)/2 ),以T为底)
    并且 T=ceil(M/2)
*/

/*
B树的搜索(设被搜索的Key值为Val):
(1)从根节点开始递归地向下遍历
(2)对于每个被访问的非叶子节点:
    [1]如果这个节点有Key为Val，返回此节点
    [2]否则继续向下到这个节点的一个适当的孩子节点(在第一个更大的Key之前的那个节点)
    [3]如果来到了一个叶子节点并且不能在叶子节点中找到Key为Val, 返回NULL
*/

class BTreeNode
{
    int *keys;         // 存储一个节点所有Key的数组
    BTreeNode **child; // 存储所有孩子指针的数组
    int t;             // 最小度，决定了Key数的范围
    int n;             // 这个节点当前的Key数
    bool IsLeaf;       // 标记当前节点是否为叶子节点 =True 说明为叶子节点
public:
    BTreeNode(int _t, bool _IsLeaf);   // 构造函数
    void SubtreeTraverse();            // 遍历函数 用于遍历以此节点为根一个子树的所有节点
    BTreeNode *SubtreeSearch(int Key); // 在以此节点为根的子树中搜索Key，搜索不到返回NULL
    friend class BTree;
};

class BTree
{
    BTreeNode *Root; // 根节点指针
    int t;           // 最小度
public:
    BTree(int t) // 构造函数 (初始时树为空)
    {
        this->Root = NULL;
        this->t = t;
    }
    void BTreeTraverse() // 遍历B树
    {
        if (!Root)
            Root->SubtreeTraverse();
    }
    BTreeNode *BTreeSearch(int Key)
    {
        return Root == NULL ? NULL : Root->SubtreeSearch(Key);
    }
};

BTreeNode::BTreeNode(int t, bool IsLeaf)
{
    this->t = t;
    this->IsLeaf = IsLeaf;
    // 为Key值和孩子节点指针分配空间
    this->keys = new int[2 * t - 1];
    this->child = new BTreeNode *[2 * t];
    n = 0; // 一个节点的初始Key数为0
}
void BTreeNode::SubtreeTraverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        // 如果这个节点不是叶子节点,那么在打印keys[i]前先遍历以child[i]为根的子树
        if (!IsLeaf)
            child[i]->SubtreeTraverse();
        cout << keys[i] << ' ';
    }
    if (!IsLeaf) // 打印以最后一个孩子为根的子树
        child[i]->SubtreeTraverse();
}
BTreeNode *BTreeNode::SubtreeSearch(int Val)
{
    int i = 0;
    while (i < n && Val > keys[i]) // 首先找到第一个大于或等于Val的Key
        i++;
    if (Val == keys[i]) // 如果找到了等于Val的Key 返回这个节点
        return this;
    if (IsLeaf) // 如果没有找到 且这个节点是一个叶子节点 返回NULL
        return NULL;
    return child[i]->SubtreeSearch(Val); // 定位到适当的孩子，继续搜索
}