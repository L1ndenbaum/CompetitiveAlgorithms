#include "../../Heads/Head.h"
//快速乘法

/*
快速乘法计算a*b%m的原理是将b分解为二进制。 b=Sigma(b[i]*(2^i))
b[i]是二进制中b的每一位，不是0就是1 将b的每一位和权重乘积进行加和得到的就是十进制的b.
之后，a*b=a*(Sigma(b[i]*(2^i)))=Sigma(a*b[i]*2^i)
在代码中，如果b的最后一位是1，那么就处理这一位，将res加上a*b在这一位的权重
*/
ll FastMultiplication(ll a, ll b, ll m) // 计算a*b%m
{
    ll res = 0;
    while (b)
    {
        if (b & 1)               // 当b的最后一位是0，就加到res上
            res = (res + a) % m; // 这里取模利用加法取模的性质(a+b)%m=((a%m)+(b%m))%m
        a = (a << 1) % m;        // 通过每次将a乘2实现2^i中i逐渐增加的操作。
        b >>= 1;                 // 处理完b的最后一位后将其舍弃，直至b为0
    }
    return res;
}