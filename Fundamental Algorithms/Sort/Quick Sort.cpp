#include "../../Heads/Head.h"
int Partition(int *arr, int L, int R)
{
    int pivot = arr[R];             // 执行一次Partition后，将arr[L]到arr[R]的部分的所有小于pivot的全部凡放在pivot的左边 大于pivot的全部放在右边
    int i = (L - 1);                // i初始位置在L的左侧
    for (int j = L; j < R; j++)     // 扫描L到R部分的所有数 每当找到小于pivot的数时就发生调换
        if (arr[j] < pivot)         // 每当需要移动时,i向前移动一位
            swap(arr[++i], arr[j]); // i移动后,调换这个比pivot小的数和arr[i]
    swap(arr[i + 1], arr[R]);       // 将pivot值放在中间位置
    return (i + 1);                 // 返回pivot值的位置
}
void QuickSort(int *arr, int L, int R) // 将arr[L]到arr[R]部分排好序
{
    if (L < R)
    {
        int pos = Partition(arr, L, R);
        QuickSort(arr, L, pos - 1);
        QuickSort(arr, pos + 1, R);
    }
}
