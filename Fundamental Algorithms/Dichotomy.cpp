/*二分法*/

// 一、整数二分
/*
基本代码：在单调递增序列中找x或x的后继；在单调递增序列中找x或x的前驱
定义：在单调递增序列中找x或x的后继，指在单调递增序列a[]中，
如果有x，找第一个x的位置；如果没有x，找比x大的第一个数的位置

需要操作三个变量：区间左端点Left、右端点Right、二分的中位数Mid
每次将区间缩小一半，将Left或Right移动到Mid,直到Left=Right为止，即找到答案所处位置

下面为在单调递增序列中寻找x或x的后继的代码，这里给出的区间是左闭右开的编码，即[0,n)。
也可以直接对[0,n-1]区间二分。

二分法找一个数的时间复杂度为logn
*/
int Bin_search_1(int *a, int n, int x) // a[0]到a[n-1]单调递增
{
    int left = 0, right = n;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] >= x)
            right = mid;
        else
            left = mid + 1; // 在整数二分时，由于存在取整问题，不可以写left=mid，容易陷入死循环(实数二分可以)
    }
    return left;
}
/*
当a[mid]>=x，说明x在mid的左边，新的搜索区间是左半部分，left不变，更新right=mid；
当a[mid]<x，说明x在mid的右边，新的搜索区间是右半部分,right不变，更新left=mid+1;
执行完毕后,left=right，两者相等，即答案所处位置，

mid的计算方法：
mid=(left+right)/2 适用于left>=0,right>=0,left+right无溢出时，缺点为left+right可能溢出、负数情况下有向0取整问题
mid=left+(right-left)/2 适用于left-right无溢出时，缺点为若right和left都是大数且一正一负,right-left可能溢出
mid=(left+right)>>1 适用于left+right无溢出时，缺点为如果left和right都是大数，left+right可能溢出
*/

/*
在单调序列中找x或x的前驱，需要对mid向上取整，即靠近right，右中位数。
写作mid=left+(right-left+1)/2或mid=(left+right+1)>>1
代码如下
*/

int Bin_search_2(int *a, int n, int x)
{
    int left = 0, right = n;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2.;
        if (a[mid] <= x)
            left = mid;
        else
            right = mid - 1;
    }
    return left;
}
/*
当a[mid]<=x时，说明x在mid的右边，新的搜索区间为右半部分，则right不变，更新left=mid;
当a[mid]>x时，说明x在mid的左边，新的搜索区间为左边部分，left不变，right=mid-1
同样地，整数二分时，不能写为right=mid;
并且，在找后继时只能用左中位数，在找前驱时只能用右中位数
注意要谨慎使用mid=(left+right)/2,除法的取整导致在正负区间左右中位数的计算不一致
*/

/*
对比Bin_search()与STL内的lower_bound()：
Bin_search()与lower_bound()功能一致

STL内的lower_bound()与upper_bound():
C++ STL中的lower_bound()和upper_bound()函数是用于在有序的范围内查找一个值的位置的算法函数。
它们都定义在<algorithm>头文件中，返回一个迭代器，指向满足条件的元素。
lower_bound()函数返回一个迭代器，指向第一个不小于给定值的元素。如果所有元素都小于给定值，则返回最后一个迭代器。
upper_bound()函数返回一个迭代器，指向第一个大于给定值的元素。如果没有元素大于给定值，则返回最后一个迭代器。

若要查找第一个大于x的元素的位置，使用upper_bound()
若要查找第一个等于或大于x的元素的位置，使用lower_bound()
若要查找第一个与x相等的元素的位置，使用lower_bound()
若要查找最后一个与x相等的元素，使用upper_bound()的前一个位置且等于x
若要查找最后一个小于或等于x的元素，使用upper_bound()的前一个位置
若要查找最后一个小于x的元素，使用lower_bound()的前一个位置
若要计算单调序列中x的个数，使用upper_bound()-lower_bound()
在二分之前都需要排序
*/

/*
整数二分经典模型：最大值最小化和最小值最大化
最大值最小化指的是让最大值尽量小，最小值最大化指的是让最小值尽量大

场景1：序列划分
有一个序列，将其分为3个连续的子序列S[1]、S[2]、S[3],每个子序列至少有一个元素
要求使每个子序列的和的最大值最小

方法：题目的要求即：找到一个x，使其满足对任意的S[i]都有S[i]<=x,x是所有S[i]中的最大值，找到最小的x
可以用二分法在[max,sum]中查找满足条件的x，其中max是序列中最大元素，sum是所有元素的和

这是一个二分法的建模，
我们可以将x看作是目标值，而序列的和看作是数组。我们要找到一个x，
使得序列可以被划分成三个子序列，每个子序列的和都不超过x，并且x是所有可能的划分中最小的一个。
我们可以用二分查找的方法，在[max,sum]之间寻找这样的x，
其中max是序列中最大的元素，sum是序列中所有元素的和。我们可以用以下步骤来描述这个方法：
1.将左边界L设为max，右边界R设为sum。
2.如果L>R，说明没有找到满足条件的x，结束查找。
3.将中间值M设为L和R的平均值。
4.用贪心算法判断是否存在一种划分方法，使得每个子序列的和都不超过M。
  具体地，从左到右遍历序列，累加元素的和，如果和超过M，则将当前元素作为下一个子序列的第一个元素，并将子序列计数加一。
  如果最后子序列计数不超过3，则说明存在这样的划分方法。
5.如果存在这样的划分方法，说明M可能是满足条件的x，或者存在更小的x。因此，将R设为M-1，并回到步骤2。
6.如果不存在这样的划分方法，说明M太小了，需要增大x。因此，将L设为M+1，并回到步骤2。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
bool canSplit(vector<int> &nums, int M) // 判断是否存在一种划分方法，使得每个子序列的和都不超过M
{
    int count = 1; // 子序列计数
    int sum = 0;   // 当前子序列的和
    for (int num : nums)
    {
        sum += num;
        if (sum > M)
        { // 超过M，则开始下一个子序列
            count++;
            sum = num;
        }
    }
    return count <= 3; // 判断子序列是否不超过3个
}

// 在[max,sum]之间寻找满足条件的最小x
int binarySearch(vector<int> &nums, int max, int sum)
{
    int L = max; // 左边界
    int R = sum; // 右边界
    while (L <= R)
    {
        int M = L + (R - L) / 2; // 中间值
        if (canSplit(nums, M))
        { // 如果存在划分方法，则缩小右边界
            R = M - 1;
        }
        else
        { // 如果不存在划分方法，则缩小左边界
            L = M + 1;
        }
    }
    return L; // 返回左边界作为结果
}
void Separate()
{
    // 创建一个序列
    vector<int> nums = {7, 2, 5, 10, 8};
    // 计算序列中最大元素和所有元素之和
    int max = *max_element(nums.begin(), nums.end());
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // 调用二分查找方法
    /*
    accumulate(起始迭代器，结束迭代器，初始值，二元操作函数)是一个计算范围内元素累积值的函数
    如果二元操作函数不指定，默认用加法
    需要导入头文件<numeric>
    */
    int x = binarySearch(nums, max, sum);
    // 输出结果
    cout << "The minimum x is " << x << endl;
    return;
}

/*
场景2：最小值最大化
在一条很长的直线上，指定n个坐标点(x[1],x[2],···,x[n])。有c头牛，安排每头牛站在其中一个点(牛棚)上。
这些牛喜欢打架，所以尽量距离远一些。求相邻的两头牛之间距离的最大值。
输入：n+1行，第一行输入n、c  第2到n+1行每行输入一个整数表示每个点的坐标
输出：相邻两头牛之间的距离的最大值
数据范围:2<=n<=1e5,0<=x[i]<=1e9

方法：设最小距离值为dis,这个值可以用二分法寻找，因为它有上下边界并且单调递增，复杂度为(nlogn)
*/

int n1, c, x[100005];
bool check1(int dis) // 当牛之间的最小距离为dis时检查牛棚够不够
{
    int cnt = 1, place = 0; // 第一头牛，放在第一个牛棚 place为上一头牛的位置
    for (int i = 1; i < n1; i++)
    {
        if (x[i] - x[place] >= dis) // 如果距离dis的位置有牛棚
        {
            cnt++;     // 又放了一头牛
            place = i; // 更新上一头牛的位置
        }
    }
    if (cnt >= c)
        return true; // 牛棚够
    else
        return false; // 牛棚不够
}
void Cow_arrangement()
{
    scanf("%d %d", &n1, &c);
    for (int i = 0; i < n1; i++)
        scanf("%d", &x[i]);
    sort(x, x + n1);
    int left = 0, right = x[n1 - 1] = x[0];
    int ans = 0;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (check1(mid))
        {
            ans = mid;
            left = mid + 1;
            /*当牛之间的最小距离为mid时，如果牛棚够就记录mid，之后扩大距离*/
        }
        else
        {
            right = mid; // 牛棚不够就缩小距离
        }
    }
    printf("%d", ans);
}

// 二、实数二分

/*
实数的二分没有取整问题。
基本思路：
int Bin_search3()
{
    const double eps=1e-7//精度，如果用for可以没有eps
    while(right-left>eps)//也可以使用for(int i=0;i<100;i++)
    {
        double mid=left+(right-left)/2;
        if(check(mid))
            right=mid;//判定，之后继续二分
        else
            left=mid;
    }
}

其中，循环的方法用while和for都可以，如果使用for，在循环内做二分，执行100次，相当于实现了1/pow(2,100)，约为1/pow(10,30)的精度，比eps精确
但是，两种方法都有精度控制问题
for循环的循环次数不能太大或太小，一般用100次，通常比while的循环次数多，大多数情况下，增加的时间是可以接受的。
但少部分情况下较大的for循环次数会超时，此时使用50次或更少，而过少的循环次数可能导致精度不够
while循环同样需要设计精度eps，过小的eps会超时，过大的eps会输出错误
*/

/*
场景：主人过生日，m个人来庆生，有n块半径不同的圆形蛋糕，由m+1个人(加上主人)分，要求每人的蛋糕必须一样重，并且是一整块(不能是几个蛋糕碎块，也就是说，每个人的蛋糕都是从一块圆蛋糕中切下的完整一块)。
问每个人能分到的最大蛋糕是多大？
输入：第一行一个整数表示样例个数。对每个样例，第一行输入两个整数n和m(1<=n,m<=10000)，分别表示蛋糕的数量和朋友的人数；第二行输入n个整数r[i](1<=r[i]<=10000)，分别表示每个蛋糕的半径
输出：对于每个样例，输出一行表示答案，取4位小数

方法：可以建模为最小值最大化问题。设每个人能分到的蛋糕大小为x,用二分法枚举x。
*/
const double PI = 3.141592653589793;
#define eps 1e-5
double area[10010];
int n, m;
bool check2(double mid)
{
    int sum = 0;
    for (int i = 0; i < n; i++) // 每个圆蛋糕都按mid大小分开，统计总数 最后看总数够不够n个
        sum += (int)(area[i] / mid);
    if (sum >= m)
        return true;
    else
        return false;
}
void Cake_separate()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        m++;
        double max_x = 0;
        int r;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &r);
            area[i] = PI * r * r;
            if (max_x < area[i])
                max_x = area[i]; // 最大的一块蛋糕
        }
        double left = 0, right = max_x;
        while (right - left > eps)
        {
            double mid = left + (right - left) / 2;
            if (check2(mid))
                left = mid; // 每人能够分到mid大小的蛋糕
            else
                right = mid; // 不能分到mid大小的蛋糕
        }
        printf("%.4f\n", left); // 也可以打印right,因为right-left<eps
    }
    return;
}
// int main()
// {
//     Cake_separate();
// }