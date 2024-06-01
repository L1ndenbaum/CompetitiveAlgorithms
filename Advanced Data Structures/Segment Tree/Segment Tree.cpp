#include "../../Heads/Head.h"
#define Lson(x) x << 1
#define Rson(x) x << 1 | 1
const int N = 1e2;
// 1. 点修改+查询
int SegmentTree[4 * N], arr[N];
void PushUp(int Node)
{
    SegmentTree[Node] = SegmentTree[Lson(Node)] + SegmentTree[Rson(Node)];
}
void Build(int Node, int pL, int pR) // 建立一棵线段树(这里以区间和线段树为例) Node指向区间[pL,pR]
{
    if (pL == pR) // L==R时,为叶子节点
    {
        SegmentTree[Node] = arr[pL];
    }
    else
    {
        int Mid = (pL + pR) >> 1;       // 找到将数组分为两半的中间元素
        Build(Lson(Node), pL, Mid);     // 递归左子树
        Build(Rson(Node), Mid + 1, pR); // 递归右子树
        PushUp(Node);                   // 将左右孩子的和返回给父节点
    }
} // 时间复杂度O(N)
void Update(int Node, int pL, int pR, int idx, int Val) // 更新线段树,将arr[idx]增加Val
{
    if (pL == pR)
    {
        arr[idx] += Val;
        SegmentTree[Node] += Val;
    }
    else
    {
        int pMid = (pL + pR) >> 1;
        if (pL <= idx && idx <= pMid) // 如果待更新节点编号在左半部分,那么只需更新左半部分
            Update(Lson(Node), pL, pMid, idx, Val);
        else
            Update(Rson(Node), pMid + 1, pR, idx, Val);
        PushUp(Node); // 更新父节点
    }
} // 每一次Update操作时间复杂度O(logN)
int Query(int Node, int pL, int pR, int L, int R) // 查询[L,R]的和,当前节点指向[pL,pR]
{
    if (pR < L || pL > R) // 如果当前节点指向的范围和要求查询的区间范围无任何重合,返回0 (返回值应该看情况决定)
        return 0;
    if (L <= pL && pR <= R) // 如果当前节点指向的范围在[L,R]内,那么返回当前节点值(这就相当于返回了一段区间值)
        return SegmentTree[Node];
    int pMid = (pL + pR) >> 1;
    // 否则就要递归地遍历左右子树去寻找节点(也就是说所指向的区间与待查询的区间部分重合)
    return Query(Lson(Node), pL, pMid, L, R) + Query(Rson(Node), pMid + 1, pR, L, R);
} // 每一次Query时间复杂度O(logN)

// 2.区间修改+查询
int SegmentTree2[4 * N], Tag[4 * N], arr2[N];
/*
    Lazy-tag:使用tag[]数组,tag[i]记录区间i的修改,而不是一个个地修改区间内的元素。
    如果修改的是一个线段区间,就只对这个线段区间进行整体上的修改,内部的元素先不修改.
    只有当这个线段区间的一致性被破坏时,才把变化值传递给下一层的子区间。
*/
void PushUp2(int Node) // 仍以区间和线段树为例
{
    SegmentTree2[Node] = SegmentTree2[Lson(Node)] + SegmentTree2[Rson(Node)];
}
void Build2(int Node, int pL, int pR)
{
    Tag[Node] = 0; // 每一个树节点的标记初始化
    if (pL == pR)
    {
        SegmentTree2[Node] = arr2[pL];
    }
    else
    {
        int pMid = (pL + pR) >> 1;
        Build2(Lson(Node), pL, pMid);
        Build2(Rson(Node), pMid + 1, pR);
        PushUp2(Node);
    }
}
void AddTag(int Node, int pL, int pR, int Val) // 给节点Node打Tag标记,并更新线段树 将Node指向的区间内所有点的值加上Val 这是对区间进行更新
{
    Tag[Node] += Val;                          // 打Tag标记
    SegmentTree2[Node] += Val * (pR - pL + 1); // 计算新的节点值
}
void PushDown(int Node, int pL, int pR) // 当修改的区间无法覆盖一个节点指向的区间时,需要将Tag传给子树
{
    if (Tag[Node]) // 有Tag标记,这是以前做的区间修改时留下的
    {
        int pMid = (pL + pR) >> 1;
        AddTag(Lson(Node), pL, pMid, Tag[Node]);     // Tag标记传递给左子树
        AddTag(Rson(Node), pMid + 1, pR, Tag[Node]); // Tag标记传递给右子树
        Tag[Node] = 0;                               // Node的Tag被传走了,将其置为0
    }
}
void Update2(int Node, int pL, int pR, int L, int R, int Val) // 区间修改 将[L,R]内每一个元素加上Val
{
    if (L <= pL && pR <= R) // 完全覆盖,直接返回这个节点,它的子树不需要再深入了
    {
        AddTag(Node, pL, pR, Val); // 给节点Node打标记,下一次区间修改时会使用
    }
    else // 无法完全覆盖,要把Tag[Node]传给子树
    {
        int pMid = (pL + pR) >> 1;
        if (L <= pMid) // 左半部分有重叠 递归左子树
            Update2(Lson(Node), pL, pMid, L, R, Val);
        if (pMid < R) // 右半部分有重叠 递归右子树
            Update2(Rson(Node), pMid + 1, pR, L, R, Val);
        PushUp2(Node); // 将更新后的节点传递给父节点
    }
}
int Query2(int Node, int pL, int pR, int L, int R) // 查询[L,R]的区间和
{
    if (L <= pL && pR <= R) // Node指向的区间被[L,R]完全覆盖,直接返回
    {
        return SegmentTree2[Node];
    }
    else
    {
        PushDown(Node, pL, pR); // 不能完全覆盖,递归子树
        int Res = 0, pMid = (pL + pR) >> 1;
        if (L <= pMid) // 左子节点有重叠
            Res += Query2(Lson(Node), pL, pMid, L, R);
        if (pMid < R) // 右子节点有重叠
            Res += Query2(Rson(Node), pMid + 1, pR, L, R);
        return Res;
    }
}