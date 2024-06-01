#include "../../Heads/Head.h"
void InsertionSort(int *arr, int n)
{
    for (int i = 1; i < n; i++) // 0位置已经有序 将1到(n-1)位置排序
    {
        int key = arr[i], j = i - 1;   // 因为0到(i-1)已经有序 故每次选取标准值Key为arr[i]
        while (j >= 0 && arr[j] > key) // 用j迭代找到应该在哪个位置插入
        {
            arr[j + 1] = arr[j]; // 当序列有序时 相当于轮流把序列复制 让前面空出一个位置
            j--;
        }                 // 执行完后找到arr[j] <= key的位置
        arr[j + 1] = key; // j+1为应该插入的位置 将Key复制进去
    }
}
// 时间复杂度:最好(即初始有序时)O(N) 最坏(即初始为逆序时)O(N^2)