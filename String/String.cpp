// 字符串

// 一、字符串函数
/*
C++的字符串函数
1.find()：查找
[1]定义:
size_t find(const string *str, size_t pos = 0)
str是要查找的字符串，pos表示开始查找的位置，默认为字符串起始位置。
如果查找到，返回子串第一次出现的位置，否则返回string::npos
[2]除了find()外，还有其他几种查找函数：
rfind()：从后往前查找字符串，如果找到，返回子串最后一次出现的位置，否则返回string::npos
find_first_of()：从前往后查找指定字符集合中任意字符第一次出现的位置
find_last_of()：从后往前查找指定字符集合中任意字符最后一次出现的位置
[3]find()函数实现多次查找：
find()函数虽然只能返回从起始位置开始第一次出现子串的位置，但是可以设置查找位置实现多次查找，如：
void Function_find()
{
    string str = "123ab123ab";
    size_t pos = str.find("ab");
    while (pos != string::npos)
    {
        cout << "Found 'ab' at: " << pos << endl;
        pos = str.find("ab", pos + 1);
    }
    return;
}

2.substr()：查找子串
[1]定义：
string substr(size_t pos = 0, size_t len = npos)
pos为要提取的子串的起始位置，len表示要提取的子串的长度
即：返回原字符串str从pos开始长度为len的子串
如果不指定pos，默认从字符串起始位置开始;如果不指定len，默认返回从pos到原字符串末尾的子串

3.replace()：替换
[1]定义(包含多个重载版本)
string& replace (size_t pos, size_t len, const string& str)：
将字符串中从pos位置开始，长度为len的子串替换为字符串str。
string& replace (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen)：
将字符串中从pos位置开始，长度为len的子串替换为字符串str中从subpos位置开始，长度为sublen的子串。
string& replace (size_t pos, size_t len, const char* s)：
将字符串中从pos位置开始，长度为len的子串替换为以空字符结尾的字符数组s。
string& replace (size_t pos, size_t len, const char* s, size_t n)：
将字符串中从pos位置开始，长度为len的子串替换为字符数组s中前n个字符。
string& replace (size_t pos, size_t len, size_t n, char c)：
将字符串中从pos位置开始，长度为len的子串替换为由字符c重复构成的长度为n的字符串。

4.insert()：插入
[1]定义(包含多个重载版本)：
string& insert (size_t pos, const string& str)：
在原串下标为pos的字符前插入字符串str。
string& insert (size_t pos, const string& str, size_t subpos, size_t sublen)：
将字符串str从下标为subpos开始数的sublen个字符插在原串下标为pos的字符前。
string& insert (size_t pos, size_t n, char c)：
在原串下标为pos的字符前插入n个字符c。

5.append()：添加字符串
[1]定义(包含多个重载版本)：
string& append (const string& str)：
在原字符串末尾添加字符串str。
string& append (const string& str, size_t subpos, size_t sublen)：
在原字符串末尾添加字符串str中从subpos位置开始，长度为sublen的子串。
string& append (const char* s)：
在原字符串末尾添加以空字符结尾的字符数组s。
string& append (const char* s, size_t n)：
在原字符串末尾添加字符数组s中前n个字符。
string& append (size_t n, char c)：
在原字符串末尾添加由字符c重复构成的长度为n的字符串。

6.swap()：交换字符串
[1]定义：
void swap(string& str)
str是要交换的字符串
例如s1="abc"; s2="fed"; 那么s1.swap(s2);就将s1和s2的内容互换
也可以用swap(s1,s2);进行交换

7.compare()：比较字符串
[1]定义(包含多个重载版本)：
int compare (const string& str)：
比较整个字符串与str。
int compare (size_t pos, size_t len, const string& str)：
比较从pos位置开始，长度为len的子串与字符串str。
int compare (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen)：
比较从pos位置开始，长度为len的子串与字符串str中从subpos位置开始，长度为sublen的子串。
[2]返回值：
如果两个字符串相同，返回0。调用字符串小于被调用字符串，返回-1。调用字符串大于被调用字符串，返回1。
[3]例子：
例如，假设有两个字符串s1("abandon")和s2("about")，那么：
s1.compare(s2)：直接比较s1和s2，返回-1。
s1.compare(2,4,s2)：比较s1下标为2的字符a开始的4个字符ando和s2进行比较。ando大于s2故返回1。
s1.compare(2,4,s2,1,3)：比较s1下标为2的字符a开始的4个字符ando和s2下标为1的字符b开始的3个字符bou比较。前者小，故返回-1。

8.gets()可以接收带空格的字符串，而cin无法接收带空格的字符串。
*/

/*
例：单词接龙
单词接龙是一个与我们经常玩的成语接龙相类似的游戏，现在我们已知一组单词，
且给定一个开头的字母，要求出以这个字母开头的最长的“龙”（每个单词都最多在“龙”中出现两次），
在两个单词相连时，其重合部分合为一部分，例如 beast 和 astonish，如果接成一条龙则变为 beastonish，
另外相邻的两部分不能存在包含关系，例如 at 和 atide 间不能相连。
输入：第一行一个数n，表示单词数
      接下俩的n行，每行一个字符串，表示一个单词
      最后一行，一个字符，表示龙开头的字母。
输出：一个数，表示以这个字母开头的龙的最大长度。
*/
#include <iostream>
#include <string>
using namespace std;
const int N = 25;
string s[N];
int vis[N];
int n;
size_t ans = 0;
bool check(string &s1, string &s2, size_t k) // 检查s2能否拼接到s1的尾部
{
    if (s1.size() < k || s2.size() < k)
        return false;
    if (s1.substr(s1.size() - k, k) == s2.substr(0, k))
        return true;
    return false;
}
string add(string &s1, string &s2, int k) // 将s2拼接到s1的尾部
{
    return s1 += s2.substr(k, s2.size() - k);
}
void Dragon_DFS(string final_str) // 深度搜索如何拼接可以使最后的龙最长
{
    ans = max(ans, final_str.size());
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 2)
            continue;
        int k = s[i].size();
        for (int j = 1; j <= k; j++) // 枚举拼接长度
        {
            if (check(final_str, s[i], j))
            {
                string temp = final_str; // 原始的龙字符串还要参与循环 所以需要创建一个临时字符串用于储存
                temp = add(temp, s[i], j);
                vis[i]++;
                Dragon_DFS(temp);
                vis[i]--;
            }
        }
    }
}
int Dragon_Main()
{
    string final_str;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    cin >> final_str;
    Dragon_DFS(final_str);
    cout << ans;
    return 0;
}

// 二、模式匹配算法KMP
/*
模式匹配(Pattern Matching)问题：
在一篇长度为n的文本S中，查找某个长度为m的关键词P，称S为母串，P为模式串。P可能出现多次，都需要找到

KMP是一种在任何情况下都能达到O(n+m)复杂度的算法。
当P和S的大多数字符相同时，朴素模式匹配算法比较低效，主要讨论这种情况：
1.P在失配点之前的每个字符都不同：
例如S="abcabcd" P="abcd" 第一次匹配的失配点是i=3、j=3处(i指向S，j指向P)。
失配点之前的P的每一个字符都不同，而失配点之前的S与P相同
从上一步的P[0]!=P[1]、P[1]=S[1]推出P[0]!=S[1]，那么i就不用回溯到位置1。
同理可知，i不用回溯到位置2，继续从i=3、j=0开始下一轮匹配即可
2.P在失配点之前的字符有部分相同，可细分为以下两种情况：
(1)相同的部分是前缀(位于P的最前面)和后缀(在P中位于j前面的部分字符)
前缀和后缀的定义：对于字符串A和B，如果存在A=BC，其中C是任意的非空字符串，则称B为A的前缀
                 对于字符串A和B，如果存在A=CB，其中C是任意非空字符串，称B为A的后缀

*/