#include "../../Heads/Head.h"
// 双向链表
class Node
{
public:
    int data;
    Node *prev;
    Node *next;
};                                        // 双向链表节点
void PushFront(Node *&Head, int new_data) // 在头部插入节点
{
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->next = Head;
    NewNode->prev = NULL;
    if (Head != NULL)
        Head->prev = NewNode;
    Head = NewNode;
}
void PushBack(Node *&Head, int new_data) // 在尾部插入节点
{
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->next = NULL;
    if (Head = NULL)
    {
        NewNode->prev = NULL;
        Head = NewNode;
        return;
    }
    Node *LastNode = Head;
    while (LastNode->next != NULL)
        LastNode = LastNode->next;
    NewNode->prev = LastNode;
    LastNode->next = NewNode;
}
void PushAfterNode(Node *PrevNode, int new_data) // 在PrevNode后插入节点
{
    if (PrevNode == NULL)
        return;
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->prev = PrevNode;
    NewNode->next = PrevNode->next;
    PrevNode->next = NewNode;
    if (NewNode->next != NULL)
        NewNode->next->prev = NewNode;
}
void PushBeforeNode(Node *NextNode, Node *&Head, int new_data) // 在NextNode前插入节点
{
    if (NextNode == NULL)
        return;
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->prev = NextNode->prev;
    NewNode->next = NextNode;
    NewNode->prev = NewNode;
    if (NewNode->prev != NULL)
        NewNode->prev->next = NewNode;
    else
        Head = NewNode;
}