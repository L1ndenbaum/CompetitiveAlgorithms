#include "../../Heads/Head.h"
// 适用于小于1e7的数(这个规模下这个方法是最快的)，找到所有小于等于这个数的素数
/*
1.创建一个bool数组prime[]，初始化为true,算法结束时prime[i]为true的是素数
  (prime[0],prime[1]不使用,从prime[2]开始)
2.依次访问prime[i],访问到的prime[i]如果还是true,i就是一个素数
3.每访问一次prime[i],就标记所有小于n的

*/
void SieveOfEratosthenes(int n)
{
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
    for (int p = 2; p <= n / p; p++)            // 遍历从2到sqrt(n)的所有数
        if (prime[p])                           // 如果p是一个素数
            for (int i = p * p; i <= n; i += p) // 从p^2开始(防止重复标记),标记n以内i的倍数,它们都不是素数
                prime[i] = false;
    for (int p = 2; p <= n; p++)
        if (prime[p])
            cout << p << " ";
}