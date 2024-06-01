/*
BFS的原理：逐层扩散。 从起点出发，按层次先后搜索。 编程时BFS用队列实现
BFS的特点是逐层搜索，先搜到的层离起点更近，所以BFS一般用于求解最短路径问题
*/

// 二、BFS与最短路径
/*
1.计算最短路径是BFS的基本应用。但只适用于一种情况：
相邻两点之间的距离相等(一般将这个距离看成1，有时称为1跳),
此时BFS是最优的查找起点到终点的最短路径的方法，时间复杂度为O(n+m),n为图上的点的数量.m为边的数量
当1跳的距离不是1，则一条有更多的跳的路径可能比有更少跳的路径更短，此时不能使用BFS
2.计算最短路径存在的两个问题：
(1)最短路径有多长。 最短路径的长度是唯一的
(2)最短路径经过了哪些点。
*/

// 例:迷宫 本题说明最短路径的计算和最短路径的两种输出方法
/*
给出迷宫的平面图 1为障碍 0为路
010000
000100
001001
110000
下面有一个更复杂的迷宫(30行50列)
迷宫的入口为左上角 出口为右下角 在一个位置，只能向上下左右四个方向走
要求找到一种走出迷宫的方式，使用的步数。如果存在多种最短路，输出字典序最小的方法。(注意字典序中D<L<R<U)
*/

// 输出最短路径的简单方法：
/*
每扩展到一个点v,都在点v上存储从起点s到点v的完整路径path。
到达终点t时，即得到了s到t的完整路径。
这样做的缺点时占用了大量的空间，因为每个点上都存储了完整的路径，只适合小图
*/

// 对于迷宫地图 (0,0)为左上角坐标
#include <iostream>
#include <string>
#include <queue>
using namespace std;
struct node
{
    int x, y;    // 坐标
    string path; // 从起点(0,0)到这个点的完整路径
};
char mp[31][51];
char k[4] = {'D', 'L', 'R', 'U'}; // 表示按字典序排列的四个方向 BFS时会按字典序处理每个点的邻居点
int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
bool state[31][51]; // 记录是否被搜索过
void Simple_print_BFS()
{
    struct node start;
    start.x = 0, start.y = 0, start.path = ""; // 定义起点
    state[0][0] = true;                        // 标记起点被搜索过
    queue<struct node> q;
    q.push(start);
    while (!q.empty())
    {
        struct node now = q.front();
        q.pop();                        // 取走并弹出队首
        if (now.x == 29 && now.y == 49) // 第一次遇到终点 就是字典序最小的路径 因为每次扩散下一层节点时都按字典序进行
        {
            cout << now.path;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            struct node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            if (next.x < 0 || next.y < 0 || next.x >= 30 || next.y >= 50)
                continue; // 超出了地图
            if (state[next.x][next.y] == true || mp[next.x][next.y] == '1')
                continue;                // 下一个点已经搜索过或者下一个点是障碍
            state[next.x][next.y] = 1;   // 标记已经被搜索过
            next.path = now.path + k[i]; // 记录完整路径：复制上一个点的路径，加上这一步的路径
            q.push(next);
        }
    }
}

// 输出最短路径的标准方法
/*
其实可以不用在每个点上储存完整路径，在每个点上记录它的前驱点就够了
这样从终点可以一步步回溯到起点，得到一条完整路径。这种方法是输出路径的标准方法
*/
// 上面简单方法定义的全局变量不变 且结构体node中只有两个变量x,y，可以用键值对替代这个结构体
using PII = pair<int, int>;
char dir_prev[31][51];        // 用于查找前驱点
void Print_path(int x, int y) // 输出路径：从(0,0)到(29,49)
{
    if (x == 0 && y == 0) // 回溯到了起点 递归结束 返回
        return;
    if (dir_prev[x][y] == 'D') // 回溯，往上(U)
        Print_path(x - 1, y);
    if (dir_prev[x][y] == 'L') // 回溯，往右(R)
        Print_path(x, y + 1);
    if (dir_prev[x][y] == 'R') // 回溯，往左(L)
        Print_path(x, y - 1);
    if (dir_prev[x][y] == 'U') // 回溯，往下(D)
        Print_path(x + 1, y);
    printf("%c", dir_prev[x][y]); // 最后输出的是终点
}
/*
上面的Print_path()是递归函数，功能为递归、回溯，再输出。
从终点开始，回溯到起点后，再按从起点到终点的顺序，正序输出完整路径。
先前定义的dir_prev[][]用于查找前驱点。
例如:dir_prev[x][y]='D'，表示上一个点往下走一步到了(x,y)，那么上一个点就是(x-1,y)。
*/
void Standard_print_BFS()
{
    PII start;
    start.first = 0, start.second = 0;
    state[0][0] = true;
    queue<PII> q;
    q.push(start);
    while (!q.empty())
    {
        PII now = q.front();
        q.pop();
        if (now.first == 29 && now.second == 49)
        {
            Print_path(29, 49);
            // 输出完整路径。从终点回溯到起点，输出的是从起点到终点的正序
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            PII next;
            next.first = now.first + dir[i][0], next.second = now.second + dir[i][1];
            if (next.first < 0 || next.first > 29 || next.second < 0 || next.second > 49)
                continue;
            if (state[next.first][next.second] || mp[next.first][next.second] == '1')
                continue;
            state[next.first][next.second] = true;
            dir_prev[next.first][next.second] = k[i];
            q.push(next);
        }
    }
}
void Maze_main()
{
    for (int i = 0; i < 30; i++)
        scanf("%s", mp[i]);
    Simple_print_BFS();
    Standard_print_BFS();
}

// 三、BFS处理连通性问题
/*
BFS处理连通性问题的步骤如下：
(1)从图上任意一个点u开始遍历，将其放进队列中
(2)弹出队首u，标记点u已经被搜索过，之后搜索点u的邻居点(与点u连通的点)，将其放入队列
(3)弹出队首，标记为已搜索过，搜索与他连通的邻居点，放进队列
   重复以上步骤，直到队列为空，此时已经找到了一个连通块。其他没有被访问的点，
   属于另外的连通块。重复按上述步骤再次处理这些点。最后所有点都被搜索过。所有连通块也都找到了
*/

// 例：全球变暖
/*
有一张某海域NxN 像素的照片，"."表示海洋、"#"表示陆地
其中"上下左右"四个方向上连在一起的一片陆地组成一座岛屿.
由于全球变暖导致了海面上升，科学家预测未来几十年，岛屿边缘一个像素的范围会被海水淹没。
具体来说如果一块陆地像素与海洋相邻(上下左右四个相邻像素中有海洋)，它就会被淹没。
请计算：依照科学家的预测，照片中有多少岛屿会被完全淹没。
输入：第一行包含一个整数N(1≤N≤1000),以下N 行 N 列代表一张海域照片。
照片保证第1行、第1列、第N行、第N列的像素都是海洋。
输出一个整数表示答案。
*/
using PII = pair<int, int>;
queue<PII> q;
const int N = 1e3 + 5;
char mp[N][N];
bool vis[N][N];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool Can_survive;
int cnt = 0;
void connectivity_BFS(int x, int y)
{
    vis[x][y] = true; // 标记起始点为已搜索过
    PII start;        // 起始点坐标
    start.first = x, start.second = y;
    q.push(start); // 起始点入队
    while (!q.empty())
    {
        PII current = q.front(); // 取队首
        q.pop();                 // 弹出队首
        if (mp[current.first - 1][current.second] == '#' && mp[current.first + 1][current.second] == '#' && mp[current.first][current.second - 1] == '#' && mp[current.first][current.second + 1] == '#')
            Can_survive = true; // 判断有没有高地
        for (int i = 0; i < 4; i++)
        {
            PII next; // 相邻点坐标
            next.first = current.first + dir[i][0], next.second = current.second + dir[i][1];
            if (mp[next.first][next.second] == '#' && !vis[next.first][next.second])
            {
                vis[next.first][next.second] = true; // 如果没有访问过且是一个陆地，就向四处搜索连通陆地
                q.push(next);                        // 入队 准备下一层的BFS
            }
        }
    }
}
int connectivity_BFS_Main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", mp[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (mp[i][j] == '#' && !vis[i][j])
            {
                Can_survive = false;
                connectivity_BFS(i, j);
                if (Can_survive == false)
                    cnt++;
            }
    printf("%d", cnt);
}

// 四、BFS与判重
/*
BFS的队列中，任意时刻只包含相邻两层的点，有时两层的点太多了，队列放不下，
即使放得下，也会影响计算量。
(1)如果这些点互不相同，那只能将所有点放进队列
(2)如果这些点有相同的，那么只搜索一次就够了，相同的点不用再搜索，此时需要判重
*/

// 例：跳蚱蜢
/*
有9个盘子，排成一个圆圈。其中8个盘子内装着8只蚱蜢，有一个盘子是空的。
将这些蚱蜢按顺时针编号为1-8。每只蚱蜢都可以跳到相邻的空盘中，也可以再
用点力，越过一个相邻的蚱蜢跳到空盘中。请计算如果要使得蚱蜢的队形改为按照逆时针方向排列，
并且保持空盘的位置不变(即1与8换位，2与7换位，···)至少要经过多少次跳跃？

解决方案:
(1)直接让蚱蜢跳比较混乱，可以视为空盘在跳
(2)将盘子排成一个圆圈不好处理，可以将圆形转化为线形，
   将空盘看成0，有9个数字{0,1,2,3,4,5,6,7,8}，
   将一个圆圈上的9个数字拉直成了一条线上的9个数字，这条线的首尾两个数字处理成相连的
(3)本题为八数码问题，八数码问题是经典的BFS问题，有9个数字{0,1,2,3,4,5,6,7,8}，共有9!种排列
(4)本题初始状态为012345678,目标状态为087654321,第一次跳完有4中情况，之后从这4种情况扩展到每一层
   扩展到某一层时如果发现目标状态，那么这一层的深度就是蚱蜢跳跃的次数
(5)本题需要判重，因为每一层的情况都会在上一层基础上乘4，队列放不下这么多。
   通过判断有没有重复跳，如果跳到一种曾经出现过的情况，就不用往下跳了，这样只有9!种情况
(6)判重可以通过mp、set
*/

// mp判重
#include <map>
struct node2
{
    node2(string ss, int tt)
    {
        s = ss,
        t = tt;
    }
    string s;
    int t;
};
map<string, bool> mp2;
queue<node2> q2;
void Grasshopper_jump_BFS_eliminate_with_map()
{
    while (!q2.empty())
    {
        node2 now = q2.front();
        q2.pop();
        string s = now.s;
        int step = now.t;
        if (s == "087654321") // 找到目标状态
        {
            printf("%d", step); // 输出跳跃次数
            break;
        }
        int i;
        for (i = 0; i < 10; i++) // 找到盘子的位置
            if (s[i] == '0')
                break;
        for (int j = i - 2; j <= i + 2; j++) // 4种跳法
        {
            int k = (j + 9) % 9; // 由于j=i-2后可能为负数，则需要(j+9)%9表示环上的位置
            if (k == i)
                continue; // 当前状态，不用检查
            string news = s;
            char temp = news[i];
            news[i] = news[k];
            news[k] = temp; // 跳到一种情况
            if (!mp2[news]) // 判重：这种情况没有出现过
            {
                mp2[news] = true;
                q2.push(node2(news, step + 1));
            }
        }
    }
}

// set判重
#include <set>
set<string> visited;
void Grasshopper_jump_BFS_eliminate_with_set()
{
    while (!q2.empty())
    {
        node2 now = q2.front();
        q2.pop();
        string s = now.s;
        int step = now.t;
        if (s == "087654321") // 找到目标状态
        {
            printf("%d", step); // 输出跳跃次数
            break;
        }
        int i;
        for (i = 0; i < 10; i++) // 找到盘子的位置
            if (s[i] == '0')
                break;
        for (int j = i - 2; j <= i + 2; j++) // 4种跳法
        {
            int k = (j + 9) % 9; // 由于j=i-2后可能为负数，则需要(j+9)%9表示环上的位置
            if (k == i)
                continue; // 当前状态，不用检查
            string news = s;
            char temp = news[i];
            news[i] = news[k];
            news[k] = temp;               // 跳到一种情况
            if (visited.count(news) == 0) // 判重：这种情况没有出现过
            {
                visited.insert(news);
                q2.push(node2(news, step + 1));
            }
        }
    }
}
int Grasshopper_jump_main()
{
    string s = "012345678";
    q2.push(node2(s, 0));
    mp2[s] = true;
    Grasshopper_jump_BFS_eliminate_with_map();
    Grasshopper_jump_BFS_eliminate_with_set();
    return 0;
}

// 五、双向广搜
/*
双向广搜是由BFS优化得来的算法
搜索场景：有确定的起点s和终点t，并且能把从起点到终点的单向搜索变换为
         分别从起点出发和从终点出发的“相遇”问题。
此时可以进行以下优化操作：
    从起点s(正向搜索)和终点t(逆向搜索)同时开始搜索
    当两个搜索产生相同的一个子状态v时就结束搜索。v是相遇点
    得到的s-v-t是一条最佳路径(最佳路径可能不止一条)
注意：与普通的BFS一样，双向广搜在搜索时并没有“方向感”。
      正向搜索和反向搜索其实都是盲目的，它们分别表示从s和t逐层扩散出去，直到相遇位置。
上面的跳蚱蜢可以用双向广搜，因为它有一个起点"012345678"和一个终点"087654321"，可以大大减少计算量
*/

// 双向广搜解决跳蚱蜢
/*
两个队列q_front和q_back分别实现正反向搜索。
由于起点和终点的字符串不同，因此正向BFS和逆向BFS扩展的下一层数量也不同，
即：进入两个队列的字符串的数量不同。先处理较小的队列可以加快搜索速度
*/
bool meet = false; // meet=true表示两端相遇
void Double_threshold_BFS(queue<string> &q, map<string, int> &m1, map<string, int> &m2)
{
    string s = q.front();
    q.pop();
    int i;
    for (i = 0; i < s.size(); i++)
        if (s[i] == '0')
            break;
    for (int j = 0; j < 4; j++) // 下一跳有四种情况
    {
        string new_s = s;
        if (j == 0)
            swap(new_s[(i - 2 + 9) % 9], new_s[i]);
        if (j == 1)
            swap(new_s[(i - 1 + 9) % 9], new_s[i]);
        if (j == 2)
            swap(new_s[(i + 1 + 9) % 9], new_s[i]);
        if (j == 3)
            swap(new_s[(i + 2 + 9) % 9], new_s[i]);
        if (m2[new_s]) // 正向搜索和逆向搜索相遇了 因为这个状态在m2中出现过
        {
            cout << m1[s] + 1 + m2[new_s] << endl; // 输出跳跃次数后退出
            meet = true;
            return;
        }
        if (!m1[new_s])
        {
            q.push(new_s);
            m1[new_s] = m1[s] + 1;
        }
    }
    meet = false; // 没有相遇
}
void Grasshopper_BFS()
{
    string start = "012345678";
    string end = "087654321";
    queue<string> q_front, q_back;
    q_front.push(start);
    q_back.push(end);
    map<string, int> mp_front, mp_back;
    mp_front[start] = 0;
    mp_back[end] = 0;
    while (!q_front.empty() && !q_back.empty()) // 一个队列空了 就说明已经找到目标状态
    {
        if (q_front.size() <= q_back.size()) // 如果正向队列小 先扩展它
            Double_threshold_BFS(q_front, mp_front, mp_back);
        else // 否则扩展逆向队列
            Double_threshold_BFS(q_back, mp_back, mp_front);
        if (meet) // 判断是否相遇
            break;
    }
}