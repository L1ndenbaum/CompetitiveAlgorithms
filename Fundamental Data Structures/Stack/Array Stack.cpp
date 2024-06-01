#include "../../Heads/Head.h"
class ArrayStack
{
    int p_top;
    int MaxSize = 1000;

public:
    int *StackArr;
    ArrayStack()
    {
        p_top = -1;
        StackArr = new int[MaxSize];
    }
    bool IsFull()
    {
        return p_top >= (MaxSize - 1);
    }
    bool IsEmpty()
    {
        return p_top < 0;
    }
    void push(int x)
    {
        if (IsFull())
            return;
        StackArr[++p_top] = x;
    }
    void pop()
    {
        if (IsEmpty())
            return;
        p_top--;
    }
    int top()
    {
        if (IsEmpty())
            return INT_MIN;
        return StackArr[p_top];
    }
};