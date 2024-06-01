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
string Addition(string a, string b)
{
    vector<int> v1 = StringToVector(a);
    vector<int> v2 = StringToVector(b);
    int n = max(v1.size(), v2.size());
    if (v1.size() < v2.size())
        v1.resize(n);
    else if (v2.size() < v1.size())
        v2.resize(n);
    vector<int> result(n + 1, 0);
    for (int i = 0; i < n; i++)
        result[i] = v1[i] + v2[i];
    for (int i = 0; i < n; i++) // 处理进位
        result[i + 1] += result[i] / 10, result[i] %= 10;
    while (result.back() == 0 && result.size() > 1) // 去掉结果中的前导0
        result.pop_back();
    return VectorToString(result); // 将结果转换为字符串后返回
}