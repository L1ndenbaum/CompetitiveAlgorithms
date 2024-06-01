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
string Subtraction(string num1, string num2) // num1 - num2
{
    bool Reversed = false;
    vector<int> v1 = StringToVector(num1);
    vector<int> v2 = StringToVector(num2);
    int n1 = v1.size(), n2 = v2.size();
    int n = max(n1, n2);
    if (n1 < n2)
    {
        v1.resize(n);
        swap(v1, v2);
        Reversed = true;
    }
    else if (n1 == n2)
    {
        for (int i = n1 - 1; i >= 0; i--)
        {
            if (v1[i] == v2[i])
            {
                continue;
            }
            else if (v1[i] > v2[i])
            {
                break;
            }
            else
            {
                swap(v1, v2);
                Reversed = true;
                break;
            }
        }
    }
    else
    {
        v2.resize(n);
    }
    vector<int> result(n);
    for (int i = 0; i < n; i++)
    {
        if (v1[i] < v2[i])
        {
            int j = i + 1;
            while (!v1[j])
                v1[j++] = 9;
            v1[j]--;
            result[i] = 10 + v1[i] - v2[i];
        }
        else
        {
            result[i] = v1[i] - v2[i];
        }
    }
    while (result.back() == 0 && result.size() > 1) // 去掉结果中的前导0
        result.pop_back();
    if (Reversed)
        return "-" + VectorToString(result);
    else
        return VectorToString(result);
}