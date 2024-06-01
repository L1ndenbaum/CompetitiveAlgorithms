#include "../../Heads/Head.h"
class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
class LinkedStack
{
public:
    Node *p_top;
    LinkedStack()
    {
        p_top = NULL;
    }
    void push(int x)
    {
        Node *temp = new Node(x);
        if (!temp)
        {
            cout << "Stack overflowed" << endl;
            return;
        }
        temp->next = p_top;
        p_top = temp;
    }
    void pop()
    {
        if (!p_top)
            return;
        Node *temp = p_top;
        p_top = p_top->next;
        delete temp;
    }
    bool IsEmpty()
    {
        return p_top == NULL;
    }
    int top()
    {
        if (!this->IsEmpty())
            return p_top->data;
        return INT_MIN;
    }
};