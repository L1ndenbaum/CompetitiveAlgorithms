#include <iostream>
#include <algorithm>
using namespace std;
// 离散化
/*
一、离散化的概念
给出一列数字，在有些情况下，这些数字的值的绝对大小不重要，而相对大小很重要。
如：对一个班级的学生成绩进行排名，此时不关心成绩的绝对值，只需要输出排名，如分数{95,50,72,21}，排名为{1,3,2,4}
离散化就是用数字的相对值代替它们的绝对值。离散化是一种数据处理的技巧，将分布广而系数的数据转换为密集分布，让算法更快速、更节省空间
例如{4000,201,11,45,830}的分布稀疏，按大小排序为{5,3,1,2,4}如果处理的是数字的相对位置问题，那么对后者的处理更容易

二、离散化的步骤和编码
(一)离散化的步骤
(1)排序    先对数列排序，确定相对大小
(2)离散化  将排序后的数列元素从1开始逐个分配数值，完成离散化
(3)归位    将离散化后的每个元素放回原始位置，结束

(二)离散化的编码
给定的数列中经常有重复的数据，如{4000，201,11,45,11}，数字11重复了。可分为两种情况进行离散化
(1)一般是把相同的数据离散化为相同的数据，如把{4000，201,11,45,11}离散化为{5,4,1,3,1}
(2)有时要求后出现的数据比先出现的大，比如{4000，201,11,45,11}离散化为{5,4,1,3,2},则不将原值相同的元素的新值赋值为相同即可。
*/

// 手写离散化
const int N = 500010;
struct data
{
    int val, id;                  // val记录元素的值 id记录元素的位置
} Primitive[N];                   // 记录离散化之前的原始数据
int Discretized[N];               // 离散化之后的结果
bool My_compare(data &x, data &y) // 离散化的排序规则
{
    return x.val < y.val;
}
void My_Discretization()
{
    int n;
    scanf("%d", &n); // 离散化的元素个数
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Primitive[i].val); // 读元素的值
        Primitive[i].id = i;            // 记录元素位置
    }
    sort(Primitive + 1, Primitive + n + 1, My_compare);
    for (int i = 1; i <= n; i++) // 生成离散化后的数据
    {
        Discretized[Primitive[i].id] = i; // 这个元素原来的位置为Primitive[i].id,将其值赋为i，i为离散化之后的新值
        if (Primitive[i].val == Primitive[i - 1].val)
            Discretized[Primitive[i].id] = Discretized[Primitive[i - 1].id]; // 若两个元素的原值相同，将新值赋为相同
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", Discretized[i]);
    }
    return;
}

// STL函数实现离散化
/*
STL的lower_bound()和unique()函数可以实现离散化
lower_bound()函数可以在有序的数列中查找某个元素的相对位置。这个位置正好是做离散化时元素初值对应的新值
有时需要用unique()函数去重，下面分别讨论不去重和去重情况下的操作
*/

//(1)不去重 将相同的数据离散化为相同的数据。 如把{4000，201,11,45,11}离散化为{5,4,1,3,1}
int OldArr[N]; // 离散化前
int NewArr[N]; // 离散化后
void STL_Discretization()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &OldArr[i]); // 读元素的值
        NewArr[i] = OldArr[i];
    }
    sort(OldArr + 1, OldArr + 1 + n);
    int cnt = n;
    // cnt = unique(OldArr + 1, OldArr + 1 + n) - (OldArr + 1);//去重，cnt是去重后的数量
    for (int i = 1; i <= cnt; i++)
        NewArr[i] = lower_bound(OldArr + 1, OldArr + 1 + n, NewArr[i]) - OldArr; // 查找相等的元素的位置，这个位置就是离散化后的新值
    for (int i = 1; i <= n; i++)
        printf("%d ", NewArr[i]);
    return;
}
//(2)去重，将相同的数据离散化为一个数据 上述代码将unique行的注释取消即可实现去重 将{4000，201,11,45,11}离散化为{4,3,1,2}