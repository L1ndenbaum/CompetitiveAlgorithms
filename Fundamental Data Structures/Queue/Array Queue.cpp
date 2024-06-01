#include "../../Heads/Head.h"
class ArrayQueue
{
public:
    int head, rear, size;
    unsigned int capacity;
    int *QueueArr;
    ArrayQueue(unsigned MaxSize)
    {
        this->capacity = MaxSize;
        this->head = this->size = 0;
        this->rear = MaxSize - 1;
        this->QueueArr = new int[MaxSize];
    }
    bool IsFull() // 当队列已满 返回true
    {
        return this->capacity == this->size;
    }
    bool IsEmpty() // 当队列为空 返回true
    {
        return this->size == 0;
    }
    void push(int item) // 将item入队
    {
        if (IsFull())
        {
            cout << "Overflowed." << endl;
            return;
        }
        this->rear = (this->rear + 1) % this->capacity;
        this->QueueArr[this->rear] = item;
        this->size += 1;
        cout << item << "has been pushed in queue." << endl;
    }
    int pop() // 将队头出队并返回队头
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, can not dequeue" << endl;
            return INT_MIN;
        }
        int item = this->QueueArr[this->head];
        this->head = (this->head + 1) % this->capacity;
        this->size--;
        return item;
    }
    int front()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty" << endl;
            return INT_MIN;
        }
        return this->QueueArr[this->head];
    }
    int back()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty" << endl;
            return INT_MIN;
        }
        return this->QueueArr[this->rear];
    }
};
