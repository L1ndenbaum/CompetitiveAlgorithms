#include "../../Heads/Head.h"
// 3.单调栈
/*
单调栈结构上是一个普通的栈，单调栈是栈的一种使用方式
单调栈内元素单调递增或递减，可以处理比较问题
例如单调递减栈，当一个数入栈时，先与栈顶元素比较，比栈顶小入栈，比栈顶大，弹出栈顶直到这个数可以入栈位置，需注意每个数都一定入栈

单调栈广泛应用于找到最近的更大/小的值
*/
stack<int> IncreasingStackConstruction(int *arr, const int ARRSIZE)
{
    stack<int> st;
    for (int i = 0; i < ARRSIZE; i++)
    {
        while (!st.empty() && st.top() > arr[i])
            st.pop();
        st.push(arr[i]);
    }
    return st;
}

/*
    场景：N头奶牛站在一排，奶牛的身高为H[i]，(1<=H[i]<=1e6),现在每头奶牛都在向右看齐，对于奶牛i,如果奶牛j
    满足i<j,且H[i]<H[j],我们说奶牛i仰望奶牛j,求出每头奶牛离它最近的仰望对象
    输入N+1行 第一行N 接下来N行为N个奶牛身高H[i] 输出N行，按顺序输出一头奶牛的最近的仰望对象，没有输出0
*/
const int x = 1e6 + 5;
int h[x], ans[x];
void STL_stack(int n)
{
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    stack<int> st;               // 栈存奶牛的位置
    for (int i = n; i >= 1; i--) // 从右到左遍历奶牛
    {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop(); // 栈顶奶牛没有i高，弹出，直到栈顶奶牛更高为止
        if (st.empty())
            ans[i] = 0; // 栈空，奶牛i没有仰望对象
        else
            ans[i] = st.top(); // 栈顶奶牛更高，是仰望对象
        st.push(i);            // 进栈
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return;
}
