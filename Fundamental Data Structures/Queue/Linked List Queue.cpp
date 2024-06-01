#include "../../Heads/Head.h"
class QNode
{
public:
    int data;
    QNode *next;
    QNode(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
class LinkedQueue
{
public:
    QNode *p_front, *p_rear;
    LinkedQueue()
    {
        this->p_front = NULL;
        this->p_rear = NULL;
    }
    void push(int x)
    {
        QNode *temp = new QNode(x);
        if (!p_rear)
        {
            p_front = p_rear = temp;
            return;
        }
        p_rear->next = temp;
        p_rear = temp;
    }
    void pop()
    {
        if (!p_front)
            return;
        QNode *temp = p_front;
        p_front = p_front->next;
        if (!p_front)
            p_rear = NULL;
        delete temp;
    }
    int front()
    {
        if (this->p_front == NULL)
            return INT_MIN;
        return this->p_front->data;
    }
    int back()
    {
        if (this->p_rear == NULL)
            return INT_MIN;
        return this->p_rear->data;
    }
    bool IsEmpty()
    {
        if (!this->p_front && !this->p_rear)
            return true;
        else
            return false;
    }
};