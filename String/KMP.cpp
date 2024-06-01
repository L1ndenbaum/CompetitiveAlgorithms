#include "../Heads/Head.h"
// 这样的Next数组，每个位置失配时应该回溯的位置储存在它前一个位置，即Next[i-1]位置
void GetNext(string &pattern, int *next)
{
    int i = 1, j = 0;
    next[0] = 0;
    while (i < pattern.length())
    {
        if (pattern[i] == pattern[j])
            j++, next[i++] = j;
        else if (j > 0)
            j = next[j - 1];
        else
            next[i++] = 0;
    }
}
// 下面的next数组是上面的next数组整体向右移动1个单位得到的，而第一个位置next[0]默认为-1
void GetNext_2(string &pattern, int *next)
{
    int j = -1, i = 0;
    next[0] = -1;
    while (i < pattern.length())
        if (j == -1 || pattern[i] == pattern[j])
            next[++i] = ++j;
        else
            j = next[j];
}
void GetNextVal(string &pattern, int *nextVal) // NextVal是改进的next数组
{
    int i = 0, j = -1;
    nextVal[0] = -1;
    while (i < pattern.length())
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            i++, j++;
            if (pattern[i] != pattern[j])
                nextVal[i] = j;
            else
                nextVal[i] = nextVal[j];
        }
        else
        {
            j = nextVal[j];
        }
    }
}
int KMP(string &text, string &pattern)
{
    if (pattern.length() == 0)
        return 0;
    int *next = new int[pattern.length()];
    GetNext(pattern, next);
    int i = 0, j = 0;
    while (i < text.length())
    {
        if (text[i] == pattern[j])
            i++, j++;
        else if (j > 0)
            j = next[j - 1];
        else
            i++;
        if (j == pattern.length())
        {
            delete[] next;
            return i - pattern.length();
        }
    }
    delete[] next;
    return -1;
} 
// Next[i]是字符串的0-(i-1)位置前后公共子序列长