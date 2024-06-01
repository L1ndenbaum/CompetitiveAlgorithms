#include "../../Heads/Head.h"
#define Lson 2 * i + 1
#define Rson 2 * i + 2
void Heapify(int *arr, int N, int i) // N为数组长 i为当前节点索引 此函数将以i为根节点的子树调整为大顶堆
{
    int largest = i;                          // 将最大值索引设置为当前位置
    if (Lson < N && arr[Lson] > arr[largest]) // 如果当前节点的左孩子值大于此节点值 调换两个节点索引
        largest = Lson;
    if (Rson < N && arr[Rson] > arr[largest]) // 如果当前节点的右孩子值大于此节点值 调换两个节点索引
        largest = Rson;
    if (largest != i) // 如果最大值索引不是此层函数的根索引 那么调换两个位置的值
    {
        swap(arr[i], arr[largest]);
        Heapify(arr, N, largest);
    }
}
void HeapSort(int *arr, int N)
{
    for (int i = N / 2 - 1; i >= 0; i--) // 从最后一个非叶子节点开始 依次调用Heapify() 从而构建一个大顶堆
        Heapify(arr, N, i);
    // 现在arr[0]是数组中最大的数
    for (int i = N - 1; i > 0; i--) // 依次调换堆顶与数组中的当前元素(从数组末尾开始)
    {
        swap(arr[0], arr[i]); // 将当前i位置元素与堆顶调换
        Heapify(arr, i, 0);   // 调换一次之后，需要重新建立大顶堆
    }
}
void Heapify1(int *arr, int N, int i)
{
    if (i >= N)
        return;
    Heapify1(arr, N, Lson);
    Heapify1(arr, N, Rson);
    if (Lson < N && arr[Lson] > arr[i])
        swap(arr[Lson], arr[i]);
    if (Rson < N && arr[Rson] > arr[i])
        swap(arr[Rson], arr[i]);
}
void HeapSort1(int *arr, int N)
{
    Heapify1(arr, N, 0);
    for (int i = N - 1; i > 0; i--)
    {
        swap(arr[i], arr[0]);
        Heapify1(arr, i, 0);
    }
}