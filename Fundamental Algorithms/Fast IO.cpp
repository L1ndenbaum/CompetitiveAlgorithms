#include "../Heads/Head.h"
// 快速读取整数
void FastScanf(int &number)
{
    bool Negative = false; // 指示读取的数是否为负数
    register int c;
    number = 0;
    c = getchar(); // 从缓冲区读取当前字符
    if (c == '-')
    {
        // 读取的数为负数
        Negative = true;
        c = getchar(); // 从缓冲区读取下一个字符
    }
    for (; (c > 47 && c < 58); c = getchar()) // 只要接下来的字符是整数(ASCII值在48到57之间),就持续读取它们
        number = number * 10 + c - 48;
    if (Negative) // 有负号标记,就把结果带负号
        number *= -1;
}