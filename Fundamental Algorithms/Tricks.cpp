#include "../Heads/Head.h"
// 一些小方法：
/*
1.逐个取出一个数x的所有位:
while(x)
{
    int bit=x%10;
    cout<<bit<<endl;
    x/=10;
}

2.已知一个长度为N的数组中所有元素都满足1<=x<=N，检查这个数组是否是一个排列:
bool Is_premutation(vector<int>& v,int length_N)
{
    set<int> s;
    for(int i=0;i<v.size();i++)
        s.insert(v[i]);
    return s.size()==length_N;
}

3.获取一个二进制数的第i位(从右往左数,最右边的一位是第0位)
bool GetBit(long long x, int i)
{
    return x & (1LL << i);
}
*/
