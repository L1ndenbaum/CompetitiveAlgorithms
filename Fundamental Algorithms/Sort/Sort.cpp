// 一、基于比较方法的暴力排序：选择排序 冒泡排序 插入排序 时间复杂度均为O(N^2)
#include <iostream>
using namespace std;
// 1.选择排序
void SelectSort(int *arr, int len)
{
    if (len < 2)
        return;
    for (int i = 0; i < len - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        if (i != min)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    return;
}

// 2.冒泡排序
void BubbleSort(int *arr, int len)
{
    if (len < 2)
        return;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return;
}

// 3.插入排序
void InsertSort(int *arr, int len)
{
    if (len < 2)
        return;
    for (int i = 1; i < len; i++) // 外层，使0~i位置有序
    {
        /*
        内层，因为0~(i-1)位置已经有序，j来到i-1位置，当j不越界时，如果j位置数>j+1位置数，交换，且j左移直到j为0
        注意：j为当前数的前一个位置，j+1为当前数位置
        */
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
        {
            int temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;
        }
    }
}

// 二、基于分治思想的排序：归并排序和快速排序 时间复杂度均为O(N*logN)
/*
1.分治思想
分治是将原问题分解为k个较小规模的子问题，对k个子问题分别求解。 如果不够小则继续划分 直到很容易求出子问题的解
可以使用分治法的情况有以下的两个特征：
(1)平衡子问题：子问题的规模大致相同。能把问题划分为大小差不多的相等的k个子问题。 子问题规模相等时的处理效率要比规模不等时高
(2)独立子问题：子问题之间互相独立。这是区别于动态规划算法的根本特征
此外 分治法可以优化算法复杂度，因为局部的优化有利于全局：一个子问题的解决，其影响力扩大了k倍，即扩大到了全局

2.分治法建模
(1)分解：将问题分解为独立子问题
(2)解决：递归解决子问题
(3)合并：将子问题的结果合并为原问题的解
其经典应用有汉诺塔、归并排序、快速排序
*/

// 例1：汉诺塔问题
/*
汉诺塔用分治法解决：将n个牌子的问题分治为两个子问题
设有x,y,z 3根杆子，初始的n个盘子在x杆上
(1)将x杆的n-1个小盘子移动到y杆(将n-1个小盘子看成一个整体)，然后把第n个大盘子移动到z杆
(2)将y杆上的n-1个小盘子移动到z杆
*/
int sum = 0;                                     // 总共需要多少步
void Hanoi(char x, char y, char z, int n, int m) // m表示在最少移动步数的第m步
{
    if (n == 1) // 最小问题
    {
        sum++;
        if (sum == m)
            cout << '#' << n << ':' << x << "->" << z << endl;
    }
    else // 分治
    {
        Hanoi(x, z, y, n - 1, m); // 先把x的n-1个小盘子移动到y,之后把第n个大盘子移动到z
        sum++;
        if (sum == m)
            cout << '#' << n << ':' << x << "->" << z << endl;
        Hanoi(y, x, z, n - 1, m); // 把y的n-1个小盘子移动到z
    }
}

// 例2：快速幂
/*
快速幂可以高效地算出a^n
*/
// 当n很大时，由于a^n极大，一般会取模后输出
using ll = long long;
ll FastPow(ll a, ll n, ll m) // 会输出a^n mod m
{
    if (n == 0)
        return 1;
    if (n == 1)
        return a;
    ll temp = FastPow(a, n / 2, m); // 分治
    if (n & 1)                      // 奇数个a
        return temp * temp * a % m;
    else // 偶数个a
        return temp * temp % m;
}
// 注：快速幂的标准写法不是分治，而是基于二进制的倍增法

// 3.归并排序
void Merge(int *arr, int L, int Mid, int R)
{
    int *help = new int[R - L + 1];
    int i = 0, p1 = L, p2 = Mid + 1; // i为临时额外数组的位置指针 p1为原数组左半部分的指针 p2为原数组右边部分的指针
    while (p1 <= Mid && p2 <= R)
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    while (p1 <= Mid)
        help[i++] = arr[p1++];
    while (p2 <= R)
        help[i++] = arr[p2++];
    for (i = 0; i < R - L + 1; i++)
        arr[L + i] = help[i];
    delete[] help;
}
void MergeSort(int *arr, int L, int R)
{
    if (L == R)
        return;
    int Mid = L + (R - L) >> 1;
    MergeSort(arr, L, Mid);     // 递归划分左半部分 使左半部分有序
    MergeSort(arr, Mid + 1, R); // 递归划分右边部分 使右边部分有序
    Merge(arr, L, Mid, R);      // 使整体有序
}
/*
场景：求逆序对
输入一个序列a[]，交换任意两个相邻的元素，不超过k次，交换之后，最少的逆序对有多少个？

方法：归并排序过程中可以记录逆序对的数量
当k=0时，即原始有多少个逆序对 可以在归并排序过程中求出，设逆序对计数器为cnt=0,那么一次合并中,设左指针为p1,右指针为p2,指向help数组的指针为i
由于子序列已经有序 则如果a[p1]和a[p2]形成了一个逆序对，那么a[p1]之后一直到a[mid]的数都会和a[p2]形成逆序对，即cnt+=mid-p1+1
当k!=0时，即将序列任意两个相邻数交换不超过k次，逆序对最少有多少：
在所有相邻数中，只有交换逆序的，才会减少逆序对的个数(如果交换的是逆序的，则逆序对-1，且不产生新的逆序对,否则逆序对+1),设原始序列有cnt个逆序对
(1)若cnt<=k，总逆序对数量不够/恰好可以交换k次，那么交换k次后，最少的逆序对数为0
(2)若cnt>k,让k次交换都发生在逆序的相邻数上，那么剩余的逆序对数为cnt-k
*/

// 4.快速排序
/*
快速排序的步骤:
(1)从数组中选择一个数作为基准元素
(2)将数组分为两个子数组，左边的子数组都小于基准元素，右边的都大于基准元素
(3)对左右两个数组递归地进行快速排序
(4)合并左右排好序的数组
*/
void QuickSort(int *arr, int L, int R)
{
    if (L < R)
    {
        int pL = L, pR = R, Pivot = arr[L]; // 设置基准元素为第一个元素
        while (pL < pR)                     // 当左右指针未相遇
        {
            while (pL < pR && arr[pR] > Pivot) // 从右向左 寻找第一个小于等于Pivot的数
                pR--;
            if (pL < pR) // 如果找到了 将该数放在左指针的位置 并将左指针向右移动一位
                arr[pL++] = arr[pR];
            while (pL < pR && arr[pL] < Pivot) // 从左向右 寻找第一个大于等于Pivot的数
                pL++;
            if (pL < pR) // 如果找到了 将该数放在右指针的位置 并将右指针向左移动一位
                arr[pR--] = arr[pL];
        }
        arr[pL] = Pivot;           // 将基准元素放到左右指针相遇的位置
        QuickSort(arr, L, pL - 1); // 左半部分递归地进行快速排序
        QuickSort(arr, pL + 1, R); // 右边部分递归地进行快速排序
    }
}
