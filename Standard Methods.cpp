#include "Heads/Head.h"
template <typename T, size_t N>
void PrintArray(T (&arr)[N])
{
    for (size_t i = 0; i < N; i++)
        cout << arr[i] << ' ';
    cout << endl;
}