// 排列有两种实现方式：自写排列函数 和 STL的next_permutation()函数
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
// 一、next_permutation()函数
/*
返回值：布尔值 如果没有下一个排列组合 返回false 否则返回true。
每执行next_permutation()一次，都会把新的排列放到原来的空间里
函数的排列范围为[first,last)
next_permutation()从当前的排列开始 逐渐输出更大的排列，而不是输出全排列
如果要输出全排列，需要从最小的排列开始
比如："bca" 重复执行next_permutation()会得到bca cab cba
使用sort函数排序后 再执行next_permutation()既可得到全排列
如果序列中有重复元素，那么next_permutation()生成的序列会自动去重
此外还有prev_permutation()函数 与next_permutation()相反，得到的是从大到小的字典序全排列
next_permutation()无法实现从n个数中取m个数的全排列
*/
// 例：得到abc的字典序全排列
void STL_permutation()
{
    string s = "cab";
    sort(s.begin(), s.end());
    do
    {
        cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
    return;
}

// 二、自写排列函数
/*
用递归写全排列函数 a[]是原排列 用b[]记录一个新的全排列 用vis[]记录某个数是否已经被选过 选过的数不能继续被选
第一次进入My_permutation()函数时,b[0]在n个数中选一个
第二次进入函数时，b[1]在剩下的n-1个数中选一个。以此类推
自写排列函数从小到大打印全排列 但是要求a[]中的数字是从小到大的 a[]需要先经过排序
全排列算法时间复杂度：O(N!)
*/
int a[20];                        // 原排列
bool vis[20];                     // 记录第i个数是否被筛选过
int b[20];                        // 记录新产生的排列
void My_permutation(int s, int t) // 基于DFS的全排列生成
{
    if (s == t) // 递归结束 取t个数产生一个排列
    {
        for (int i = 0; i < t; i++)
            cout << b[i] << ' '; // 输出一个排列
        cout << endl;
        return;
    }
    for (int i = 0; i < t; i++)
    {
        // 枚举每一个位置的数
        if (!vis[i])
        {
            vis[i] = true;
            b[s] = a[i];
            My_permutation(s + 1, t);
            vis[i] = false; // 回溯
        }
    }
    // 如果要实现从n个数中任意取m个数的排列 需要在调用函数时将参数t设为n 并在函数中修改if(s==t)为if(s==m)
}
// 如果不需要实现从n个数中任意取m个的排列 可以这样写
const int N = 15;
int n;
bool state[N]; // 初始化为false表示没选过
int arr[N];
void DFS(int x) // x表示当前枚举到了哪个位置
{
    if (x > n) // 一个情况枚举完成的条件
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!state[i]) // 如果没有被选过
        {
            state[i] = true; // 选他 状态记为选过了
            arr[x] = i;
            DFS(x + 1);
            state[i] = false; // 回溯
            arr[x] = 0;
        }
    }
}