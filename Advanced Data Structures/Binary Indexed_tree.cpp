// 树状数组(二进制索引树)
/*
前缀和数组可以处理静态数组的区间和问题。
但是如果数组随时会被修改，修改和查询区间和轮流进行，那么前缀和就变得没有效率了。
树状数组可以处理动态数组的区间和问题，将“改变n次元素值，查询n次区间和”的时间复杂度降低为O(nlogn)。
使用树状数组处理动态数组的区间和问题分为以下步骤：
(1)初始化：
   将数组a[]存储到tree[]中。主程序先清空数组tree[]，之后读取a[1]~a[n]，
   用update()逐一处理这n个数，得到数组tree[]。update()的计算复杂度是O(logn)，计算n次为O(nlogn)
(2)求前缀和：
   用sum()函数计算前缀和a[1]+···+a[x]，求和函数sum()基于tree[],计算时间复杂度为O(logn)
(3)修改元素：
   执行update(int x,int d)，修改元素a[x]，即a[x]+=d。实际上是在修改数组tree[]
(4)查询区间和：例如区间[5,8]的和为sum(8)-sum(4)
   初始化计算tree[]数组的复杂度为O(nlogn)；
   修改一次元素的复杂度为O(logn)；
   查询一次区间和的复杂度为O(logn)；
   修改n次元素，查询n次区间和，总时间复杂度为O(nlogn)
*/

/*
一、树状数组的原理
树状数组时利用数的二进制特征进行检索的一种树状的结构。其利用了二分思想，并利用二叉树实现。
树状数组存储的特征是：偶数位置存的是部分和 奇数位置存的是单点值
下面的去掉最后的1,如果一个数是奇数，那么去掉最后一位1就变成了比它小的、离它最近的偶数
                 如果一个数是偶数，那么去掉最后一位1就变成了比它小的、里它最近的偶数 如果只剩一个1了，去掉1后就是0，这个过程就结束了。
这样逐层寻找，就可以在update()过程中更新前缀和，并用sum()求前缀和
1.查询：
查询的过程时每次去掉二进制数的最后的1，如求sum(7)=tree[7]+tree[6]+tree[4]步骤如下：
(1)7的二进制数时111，去掉最后的1，得到110，110的十进制数是6，即tree[6]
(2)去掉6的二进制数110的最后的1，得到100，100的十进制数是4，即tree[4]
(3)4的二进制数是100，去掉最后一个1后就全是0了，所以最后加到tree[4]
2.维护：
维护的过程是每次在二进制数的最后的1上加1，如更新了a[3]，则需要修改tree[4]、tree[8]，步骤如下：
(1)3的二进制数是11，在最后的1上加1，得到100，对应十进制数4，即修改tree[4]
(2)4的二进制数是100，在最后的1上加1，得到1000，对应十进制数8，即修改tree[8]
(3)修改tree[16]、tree[32]等
这样做的原理以维护为例，比如更新了a[3]，需要修改tree[3]、tree[4]、tree[8]等，
实际上是沿着二叉树往上跳到2的倍数的那些tree[]，而2的倍数在二进制数中，
对应的就是二进制数的每一位的权值。所以从二进制数的最后的1开始逐个处理，就是跳到新的tree[]

找到一个数的二进制数的最后一个1，可以使用lowbit()函数：
lowbit(x)=x&-x，其功能为找到x的二进制数的最后一个1，原理利用了负数的补码表示
x&-x先得到一个二进制数，是x的最后一个1和1后面的0，之后将这个二进制数转换为10进制数，就是lowbit(x)的值
令m=lowbit(x)，tree[x]的值是把a[x]和它前面m-1个数相加的结果 如lowbit(6)=2，则tree[6]=a[5]+a[6]
tree[]是通过lowbit()计算出的树状数组，它能够以二分的复杂度储存一个数列的数据。
具体地，tree[x]中储存的是[x-lowbit(x)+1,x]中每个数的和
*/
// 树状数组C++代码 树状数组的下标总是从1开始，0不使用 原数组也不用0这个下标
#define lowbit(x) ((x) & -(x))
const int N = 1e3;
int tree[N];
void update(int x, int d) // 单点修改 修改元素a[x]+=d
{
   while (x <= N)
   {
      tree[x] += d;
      x += lowbit(x);
   }
}
/*
update()函数有两个作用
(1)初始化计算tree[]数组。定义tree[N]={0}，之后逐个读入a[1]~a[8]，用update()更新每个tree[]
   for(int i=1;i<=10;i++) update(i,a[i]);
(2)修改a[x]，更新tree[]数组。执行update(x,a[x])，更新tree[x]，并沿着二叉树往上更新相关的tree。
*/
int sum(int x) // 返回前缀和ans=a[1]+a[2]+···+a[x]
{
   int ans = 0;
   while (x > 0)
   {
      ans += tree[x];
      x -= lowbit(x);
   }
   return ans;
}

// 二、树状数组的基本应用

/*
1.区间修改+单点查询(区间修改就是像差分数组一样，一次改变一个区间[L,R]内的所有数)：
树状数组的原始功能是：单点修改+区间查询 引入差分数组，即可实现区间修改+单点查询

例：N(M<=1e5)个气球排成一排，从左到右编号为1···N。每次给定两个整数L，R，某人从L开始到气球R，依次给每个气球涂一次颜色
   但是N次后他忘记了第i个气球已经涂过几次颜色了，请计算每个气球涂了几次颜色。
输入：对每个样例，第一行是N 接下来N行 每行两个数L,R 当N=0时输入结束
输出：对每个样例，输出一行，第i个数代表第i个气球总共被涂色的次数
*/
#include <cstring>
#include <iostream>
const int N = 1e5 + 5;
int Balloon_Main()
{
   int n;
   while (scanf("%d", &n) != 0)
   {
      memset(tree, 0, sizeof(tree));
      int L, R;
      for (int i = 1; i <= n; i++) // 这里直接将树状数组当做差分数组，之后直接对差分数组求和
      {
         scanf("%d %d", &L, &R);
         update(L, 1);
         update(R + 1, -1);
      }
      for (int i = 1; i <= n; i++) // 用树状数组自带的sum函数对差分数组求和
      {
         printf("%d ", sum(i));
      }
      printf("\n");
   }
}

/*
2.区间修改+区间查询(查询的不是一个单点a[x]的值，而是区间[i,j]的和)：
只用一个树状数组无法同时快速完成区间修改和区间查询，因为这个树状数组的tree[]已经用于区间修改，
它用sum()函数计算了单点a[x],不能再用于求a[i]~a[j]的区间和。
需要使用二阶树状数组，即用两个树状数组紧密结合，同时也是差分数组和树状数组的结合

例：
已知一个数列，进行两种操作：(1)将某个区间每个数加d;(2)求某区间所有数的和
输入：第一行两个整数n,m(1<=n,m<=1e5)表示该数列数字的个数和操作的总个数
     第二行输入n个用空格分隔的整数，第i个数字表示数列第i项的初始值(数列元素的范围为[-2^63,2^63])；
     接下来m行 每行输入3或4个整数 表示一个操作，如下：
     (1) 1 L R d：将数列区间[L,R]内每个数加d。
     (2) 2 L R  ：输出区间[L,R]内每个数的和。
*/

/*
求区间和的操作sum(L,R)=sum(1,R)-sum(1,L-1)，所以 只要求出sum(1,k)的通式，即可实现求区间和
定义一个差分数组Diff，它与原数组的关系仍然是D[k]=a[k]=a[k-1]，有a[k]=Diff[1]+···+D[k]
[1,k]区间和a[1]+···+a[k]
=Diff[1]+(Diff[1]+Diff[2])+(Diff[1]+Diff[2]+Diff[3])+···+(Diff[1]+···+Diff[k])
=k*Diff[1]+(k-1)*Diff[2]+(k-2)*Diff[3]+···+(k-(k-1))*Diff[k]
=k*(Diff[1]+···+Diff[k])-(Diff[2]+2*Diff[3]+···+(k-1)*D[k])
=k*(Sigma(Diff[i]),i from 1 to k)-(Sigma((i-1)*Diff[i]),i from 1 to k)
最后一行求两个前缀和，用两个树状数组分别处理，一个实现Diff[i]，另一个实现(i-1)*Diff[i]。
时间复杂度O(mlogn)
*/
using ll = long long;
const int N = 1e5 + 5;
#define lowbit(x) ((x) & -(x))
ll tree1[N], tree2[N]; // 两个树状数组
void update1(ll x, ll d)
{
   while (x <= N)
   {
      tree1[x] += d;
      x += lowbit(x);
   }
}
void update2(ll x, ll d)
{
   while (x <= N)
   {
      tree2[x] += d;
      x += lowbit(x);
   }
}
ll sum1(ll x)
{
   ll ans = 0;
   while (x > 0)
   {
      ans += tree1[x];
      x -= lowbit(x);
   }
   return ans;
}
ll sum2(ll x)
{
   ll ans = 0;
   while (x > 0)
   {
      ans += tree2[x];
      x -= lowbit(x);
   }
   return ans;
}
int Section_modify_and_query()
{
   ll n, m;
   scanf("%lld %lld", &n, &m);
   int previous = 0, a;
   for (int i = 1; i <= n; i++)
   {
      scanf("%lld", &a);        // 初始值
      update1(i, a - previous); // tree1和tree2都是差分数组，利用差分数组原理进行初始化
      update2(i, (i - 1) * (a - previous));
      previous = a;
   }
   while (m--)
   {
      ll op, L, R, d;
      scanf("%lld", &op);
      if (op == 1)
      {
         scanf("%lld %lld %lld", &L, &R, &d);
         update1(L, d); // 第一个树状数组
         update1(R + 1, -d);
         update2(L, d * (L - 1)); // 第二个树状数组 (i-1)*(Diff[i]+d)=(i-1)*d+(i-1)*Diff[i]。即：对tree2的区间修改操作是将tree2[i]+d*(L-1)之后再tree2[i]-d*(R+1-1)
         update2(R + 1, -d * R);  // -d*R=-d*(R+1-1)
      }
      else
      {
         scanf("%lld %lld", &L, &R);
         printf("%lld\n", R * sum1(R) - (L - 1) * sum1(L - 1) - sum2(R) + sum2(L - 1));
      }
   }
   return 0;
}
/*
.树状数组求解逆序对个数
给定一个序列A[1]~A[n]，求解这个序列的逆序对个数  (1<=n<=5e5) A[i]都是long long类型的整数

用树状数组求解逆序对问题要用一个技巧：将数字看作树状数组的下标
如序列{5，4，2，6，3，1}对应了a[5] a[4] a[2] a[6] a[3] a[1]
每处理序列中的一个数字，树状数组的下标所对应的元素数值就加1，统计前缀和，即可得到逆序对的数量
处理序列的方法有两种：
1.用树状数组正序处理序列：当前已经处理的数字个数减去当前数字的前缀和就是以该数为较小数的逆序对个数
2.用树状数组逆序处理序列：当前数字的前一个数的前缀和就是以该数为较大数的逆序对的数量
另外，将数字看做树状数组的下标，需要进行离散化操作，因为数字最大为2^63，不能开那么大的空间，就用相对大小替换原来的数，替换后，逆序对的个数并不会改变。
在树状数组求逆序对时，离散化是必需的。
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define lowbit(x) ((x) & -(x))
const int N = 5e6 + 5;
int tree[N], Rank[N]; // 离散化之后的数据 注意rank是C++的保留字
int n;
struct number
{
   int index;
   long long value;
} num[N];
void update(int x, int d)
{
   while (x <= N)
   {
      tree[x] += d;
      x += lowbit(x);
   }
}
int sum(int x)
{
   int ans = 0;
   while (x > 0)
   {
      ans += tree[x];
      x -= lowbit(x);
   }
   return ans;
}
bool Mycompare(struct number &n1, struct number &n2)
{
   if (n1.value == n2.value)
      return n1.index < n2.index;
   return n1.value < n2.value;
}
int Inverse_number_calculate_Main()
{
   scanf("%d", &n);
   for (int i = 1; i <= n; i++)
   {
      scanf("%lld", &num[i].value);
      num[i].index = i; // 记录顺序  用于离散化
   }
   sort(num + 1, num + 1 + n, Mycompare); // 排序 得到每个数的位置
   for (int i = 1; i <= n; i++)
      Rank[num[i].index] = i; // 离散化 得到新的数字序列
   long long ans = 0;
   for (int i = n; i > 0; i--) // 用树状数组逆序处理求逆序对
   {
      update(Rank[i], 1);
      ans += sum(Rank[i] - 1);
   }
   printf("%lld", ans);
}