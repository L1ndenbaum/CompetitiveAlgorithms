#include "../../Heads/Head.h"
// 单链表节点
class Node
{
public:
    int data;
    Node *next;
};
/*
从头部插入节点:
(1)将单链表的第一个节点连接到新节点
(2)将原先链表的头节点指针指向新加入的节点

从某个节点后面插入节点:
(1)将新节点的next指向给定的prev节点的next
(2)将给定的prev节点的next指向新节点

从尾部插入节点:
(1)找到尾节点
(2)将尾节点的next改为新节点并将新节点的next改为NULL
*/
void PushFront(Node *&Head, int new_data) // 在链表前插入节点 注意要改变Head的指向 故传入二级指针
{
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->next = Head;
    Head = NewNode;
}
void InsertAfterNode(Node *PrevNode, int new_data) // 在链表的某个节点后面插入一个节点
{
    // PrevNode不需要二级指针 因为没有修改PrevNode的值，只是修改它指向节点的next指针
    if (PrevNode == NULL)
        return;
    Node *NewNode = new Node;
    NewNode->data = new_data;
    NewNode->next = PrevNode->next;
    PrevNode->next = NewNode;
}
void PushBack(Node *&Head, int new_data)
{
    Node *NewNode = new Node;
    NewNode->data = new_data;
    Node *LastNode = Head;
    NewNode->next = NULL;
    if (Head == NULL) // 如果链表是空的
    {
        Head = NewNode;
        return;
    }
    while (LastNode->next != NULL) // 找到尾节点
        LastNode = LastNode->next;
    LastNode->next = NewNode;
}

// 删除节点
void DeleteNode_Val(Node *&Head, int Val) // 删除所有值为Val的节点
{
    if (Head == NULL) // 空链表
        return;
    while (Head->data == Val)
    {
        Node *temp = Head;
        Head = Head->next;
        delete temp;
    }
    Node *PrevNode = Head, *NextNode = Head->next;
    while (NextNode != NULL)
    {
        if (NextNode->data == Val)
        {
            Node *temp = NextNode;
            PrevNode->next = NextNode->next;
            NextNode = NextNode->next;
            delete temp;
        }
        else
        {
            NextNode = NextNode->next;
            PrevNode = PrevNode->next;
        }
    }
}
void DeleteNode_Pos(Node *&Head, int Pos) // 删除指定Pos(从0开始)的节点
{
    if (Head == NULL)
        return;
    Node *temp = Head;
    if (Pos == 0)
    {
        Head = Head->next;
        delete temp;
        return;
    }
    for (int i = 0; i < Pos - 1 && temp; i++) // 在不越界的情况下找到指定节点
        temp = temp->next;
    if (temp == NULL || temp->next == NULL) // 不存在这样的节点(已越界) temp->next是要被删除的节点
        return;
    Node *NextNode = temp->next->next;
    delete temp->next;
    temp->next = NextNode;
}
void PrintList(Node *Head)
{
    Node *temp = Head;
    while (temp != NULL)
    {
        cout << temp->data << ' ';
        temp = temp->next;
    }
    cout << endl;
}
void DestroyList(Node *&Head)
{
    while (Head != NULL)
    {
        Node *temp = Head;
        Head = Head->next;
        delete temp;
    }
}