#include "../../Heads/Head.h"
void Merge(int* arr, int L, int Mid, int R)
{
    int* help = new int[R - L + 1];
    int i = 0, p1 = L, p2 = Mid + 1; // i为临时额外数组的位置指针 p1为原数组左半部分的指针 p2为原数组右边部分的指针
    while (p1 <= Mid && p2 <= R)     // 当p1不越界且p2不越界
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    while (p1 <= Mid) // 把左半部分的剩余部分复制到help
        help[i++] = arr[p1++];
    while (p2 <= R) // 把右半部分的剩余部分复制到help 最后两个while中只有一个会进行 因为只有一部分会有剩余
        help[i++] = arr[p2++];
    for (i = 0; i < R - L + 1; i++)
        arr[L + i] = help[i]; // 把help复制到arr
    delete[] help;
}
void MergeSort(int* arr, int L, int R)
{
    if (L >= R)
        return;
    int Mid = L + (R - L) >> 1;
    MergeSort(arr, L, Mid);     // 递归划分左半部分 使左半部分有序
    MergeSort(arr, Mid + 1, R); // 递归划分右边部分 使右边部分有序
    Merge(arr, L, Mid, R);      // 使整体有序
}
