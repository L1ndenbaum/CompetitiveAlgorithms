#include <cstdio>
#include <stack>
using namespace std;
/*
栈的特点是“先进后出”，只有唯一入口，从此口进出
栈需要用空间储存，如果深度太大，或者存进栈的数组太大，总数会超过系统为栈分配的空间而导致栈溢出
*/

// 1.STL stack
/*
常用操作：
push(item) 将item放到栈顶
top() 返回栈顶元素
pop() 删除栈顶元素，不返回值 出栈需要先使用top()获得栈顶元素，之后用pop()删除栈顶元素
size() 返回栈元素个数
empty() 栈为空返回True 否则返回False
*/

// 2.手写栈(手写栈比较省空间)
const int N = 100100;
struct My_stack
{
    int data[N];           // 存放栈元素
    int top_pointer = 0;   // 栈顶位置
    void push(int element) // 入栈函数
    {
        data[++top_pointer] = element;
    }
    int top() // 访问栈顶元素
    {
        return data[top_pointer];
    }
    void pop() // 出栈
    {
        top_pointer--;
        return;
    }
    bool empty() // 询问栈是否为空 空则返回true
    {
        return top_pointer == 0 ? true : false;
    }
} st;