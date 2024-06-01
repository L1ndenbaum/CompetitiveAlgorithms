#include <iostream>
using namespace std;
/*链表，可分为动态链表、静态链表、STL链表*/

// 1.动态链表
/*动态链表需要临时分配链表节点，使用完毕后释放节点。
  优点是即使释放空间而不使用多余内存，缺点是需要管理空间，容易出错*/

/*场景：n个人，编号1-n,按顺序围一圈，从第一个人开始报数，数到m的人出列，之后下一个人从1重新报数
  数到m的人再出列，类推，到所有人都出列，依次输出出猎人的编号(1<=m,n<=100) 输入为n,m*/
struct node1
{
    int data;    // 数据区
    node1 *next; // 单项指针
};
void Unidirectional_dynamic_list(int n, int m)
{
    node1 *head, *p, *now, *prev; // head为头指针 p为临时分配指针 now为当前指针(尾指针) prev为先前的指针
    head = new node1;
    head->data = 1;    // 分配第一个(头)节点，这里将其数据置为1
    head->next = NULL; // 头节点的下一个节点暂不分配
    now = head;        // 当前指针为头
    for (int i = 2; i <= n; i++)
    {
        p = new node1; // p为新产生的节点
        p->data = i;
        p->next = NULL;
        now->next = p; // 申请的新节点链接到前面的链表上
        now = p;       // 尾指针后移一个
    }
    now->next = head;        // 首尾相连，循环链表建立完成
    now = head, prev = head; // 从第一个开始数
    while ((n--) > 1)
    {
        for (int i = 1; i < m; i++) // 数到m停下
        {
            prev = now;      // 记录上一个位置，用于之后跳过第m个节点
            now = now->next; // 当前节点变换为下一个
        }
        cout << now->data << ' '; // 输出第m个节点
        prev->next = now->next;   // 跳过这个节点 注意next是个地址 这句话意思是将now的下一个节点的地址给prev指向的节点的指针区
        delete now;               // 释放
        now = prev->next;         // 跳过后把now更新
    }
    cout << now->data; // 打印最后一个节点
    delete now;        // 释放 至此全部释放完毕
    return;
}

// 2.静态链表
/*静态链表使用预先分配的一段连续空间存储链表。先定义链表结构体，之后使用一维数组，在数组上进行链表操作*/

// 结构体数组实现单向静态链表，这个静态分配应该定义在全局，防止爆栈
struct node2
{
    int id, next_id;
} nodes_1[105];
void Unidirectional_static_list(int n, int m)
{
    nodes_1[0].next_id = 1;
    for (int i = 1; i <= n; i++)
    {
        nodes_1[i].id = i;
        nodes_1[i].next_id = i + 1;
    }
    nodes_1[n].next_id = 1; // 尾指头，循环
    int now = 1, prev = 1;  // 从第一个节点开始
    while ((n--) > 1)
    {
        for (int i = 1; i < m; i++)
        {
            prev = now;
            now = nodes_1[now].next_id; // 数到m停下
        }
        cout << nodes_1[now].id << ' ';
        nodes_1[prev].next_id = nodes_1[now].next_id; // 跳过now节点，即删除now
        now = nodes_1[prev].next_id;                  // 更新now
    }
    cout << nodes_1[now].next_id;
    return;
}

// 结构体数组实现双向静态链表
struct node3
{
    int id;
    int preid, nextid;
} nodes_2[105];
void Bi_directional_static_list(int n, int m)
{
    nodes_2[0].nextid = 1;
    for (int i = 1; i <= n; i++)
    {
        nodes_2[i].id = i;
        nodes_2[i].preid = i - 1;  // 前节点
        nodes_2[i].nextid = i + 1; // 后节点
    }                              // 初始化双向链表
    nodes_2[n].nextid = 1;         // 完成循环 尾指头
    nodes_2[1].preid = n;          // 头指尾
    int now = 1;                   // 当前指针，从第一个节点开始
    while ((n--) > 1)
    {
        for (int i = 1; i < m; i++)
        {
            now = nodes_2[now].nextid; // 数到m停下
        }
        cout << nodes_2[now].id << ' ';
        int prev = nodes_2[now].preid, next = nodes_2[now].nextid;
        nodes_2[prev].nextid = nodes_2[now].nextid;
        nodes_2[next].preid = nodes_2[now].preid; // 删除now节点
        now = next;
    }
    cout << nodes_2[now].nextid;
    return;
}

// 一维数组实现单向静态链表
/*这是最简单的实现方法,nodes[i]的i就是节点值，nodes[i]的值是下一个节点，这种方法的使用环境有限，因为一个节点只能存一个数据，就是i*/
int nodes_3[105];
void Unidirectional_static_list_array(int n, int m)
{
    for (int i = 1; i <= n - 1; i++)
    {
        nodes_3[i] = i + 1; // nodes_3[i]d 的值为下一个节点
    }
    nodes_3[n] = 1;
    int now = 1, prev = 1;
    while ((n--) > 1)
    {
        for (int i = 1; i < m; i++)
        {
            prev = now;
            now = nodes_3[now]; // now更新为下一个节点
        }
        cout << now << ' ';
        nodes_3[prev] = nodes_3[now]; // 跳过now节点
        now = nodes_3[prev];
    }
}

// 3.STL链表