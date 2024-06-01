#include "../../Heads/Head.h"
vector<int> StringToVector(string s)
{
    vector<int> v;
    for (int i = s.size() - 1; i >= 0; i--)
        v.push_back(s[i] - '0');
    return v;
}
string VectorToString(vector<int> v)
{
    string s;
    for (int i = v.size() - 1; i >= 0; i--)
        s += (v[i] + '0');
    return s;
}
string Multiplication(string a, string b)
{
    bool ResNegative = false;
    if ((a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-'))
        ResNegative = true;
    if (a[0] == '-')
        a = a.substr(1);
    if (b[0] == '-')
        b = b.substr(1);
    vector<int> v1 = StringToVector(a);
    vector<int> v2 = StringToVector(b);
    int n1 = v1.size();
    int n2 = v2.size();
    vector<int> result(n1 + n2, 0);
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            result[i + j] += v1[i] * v2[j];
    for (int i = 0; i < n1 + n2 - 1; i++) // 处理进位
        result[i + 1] += result[i] / 10, result[i] %= 10;
    while (result.back() == 0 && result.size() > 1) // 去掉结果中的前导0
        result.pop_back();
    if (ResNegative)
        return "-" + VectorToString(result); // 将结果转换为字符串后返回
    else
        return VectorToString(result);
}