#include "../../Heads/Head.h"
// 双端队列和单调队列
/*
    双端队列是一种具有队列和栈性质的数据结构，可以在两端进行插入和删除数据，且只能在两端插入和删除
*/

/*
    STL提供了双端队列deque,其主要操作有：
    dq[i]：返回双端队列下标为i的元素
    front()：返回队头
    back()：返回队尾
    pop_front()：删除队头，不返回值
    pop_back()：删除队尾，不返回值
    push_back(item)：队尾添加元素item
    push_front(item)：队头添加元素item
    双端队列的经典应用为单调队列。单调队列中的元素单调有序，且元素在队列中的顺序和在原来的序列中的顺序一致。
    单调队列的队头和队尾都能入队和出队
    单调队列能使很多问题得到优化，序列中的n个元素，用单调队列处理，每个元素只需要进出队列一次，时间复杂度为O(n)
*/

deque<int> IncreasingMonotonicQueueConstruction(int *arr, int ARRSIZE)
{
    deque<int> dq;
    for (int i = 0; i < ARRSIZE; i++)
    {
        while (!dq.empty() && dq.back() > arr[i])
            dq.pop_back();
        dq.push_back(arr[i]);
    }
    return dq;
}
/*
    场景：有一个长度为n的序列a和一个大小为k的窗口。从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。
    输入两行，第一行两个正整数n,k。第二行n个整数，为序列a。输出两行，第一行为窗口每次滚动的最小值，第二行为最大值
    1<=k<=n<=1e6,a[i]在有符号int范围内
*/

const int n = 1e6 + 5;
int a[n];      // 序列
deque<int> dq; // 双端队列中的数据实际是元素在原序列中的位置
void STL_deque(int n, int k)
{
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) // 输出最小值
    {
        while (!dq.empty() && a[dq.back()] > a[i]) // 对队列的维护，核心是队列不空且新元素更优
            dq.pop_back();                         // 去尾
        dq.push_back(i);
        if (i >= k) // 每个窗口输出一次
        {
            while (!dq.empty() && dq.front() < i - k + 1) // dq.front()是序列中的一个位置，如果dq.front()<i-k+1,说明窗口已经滑出了该位置,那么该位置就应该从队列弹出
                dq.pop_front();                           // 删头
            cout << a[dq.front()] << ' ';
        }
    }
    cout << endl;
    dq.clear();                  // 清空队列
    for (int i = 1; i <= n; i++) // 输出最大值
    {
        while (!dq.empty() && a[dq.back()] < a[i])
            dq.pop_back(); // 去尾
        dq.push_back(i);
        if (i >= k)
        {
            while (!dq.empty() && dq.front() < i - k + 1)
                dq.pop_front(); // 删头
            cout << a[dq.front()] << ' ';
        }
    }
    cout << endl;
    return;
}