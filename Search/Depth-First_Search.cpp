#include <iostream>
#include <string>
using namespace std;
/*
一、递归与记忆化搜索
递归的思想：将大问题逐步缩小为最小的同类问题，小问题的解是已知的(给定的初始条件)。
           当达到最小问题后，回溯，将小问题的解逐个带给更大的问题，最终大问题也得到解决。
           即：递归有两个过程：递归前进 递归回溯
记忆化搜索：储存已经解决的子问题的结果，当递归时直接调用
*/
// 递归+记忆化搜索实现斐波那契数列的计算：
int data[25]; // 储存斐波那契数
int Fibonacci(int n)
{
    if (n == 1 || n == 2)
    {
        data[n] = 1;
        return data[n];
    }
    if (data[n] != 0)
        return data[n];                            // 记忆化判断：已经算过的 就不用再算 直接返回结果
    data[n] = Fibonacci(n - 1) + Fibonacci(n - 2); // 没有算过的 递归算出来
    return data[n];
}

/*
注：
如果要使用记忆化搜索，那么DFS的参数要尽可能少，
不应该把没有影响到边界的参数放进来
如果想要剪枝，就要尽可能把能进行剪枝的参数放进来。
*/
/*
二、DFS代码基本框架
int ans;//答案 使用全局变量存储
bool used[N];记录状态i是否被用过
void DFS(层数,其他参数)
{
    if(结束判断)//到达最底层或满足条件时退出
    {
        更新答案;
        return;返回到上一层
    }
    (剪枝)//再进一步DFS之前进行剪枝
    for(枚举下一层可能的情况)//对每一种情况继续DFS
    {
        if(!used[i])//如果状态i没有用过，就进入下一层
        {
            used[i]=true;//表示i已经用过 在更底层不可以再使用
            DFS(层数+1,其他参数)
            used[i]=0;//恢复状态，回溯时，不影响上一层对这个状态的使用
        }
    }
}
*/

// 三、递归(DFS)与排列组合
//  递归实现指数型枚举
// 例1：从n个数里面选数，所有可能的情况
const int N = 20;
int n1;
int state1[N];           // 记录枚举状态 0未考虑 1选 2不选
void DFS_exponent(int x) // x表示枚举到哪个位置
{
    if (x > n1)
    {
        for (int i = 1; i <= n1; i++)
        {
            if (state1[i] == 1)
            {
                printf("%d ", i);
            }
        }
        printf("\n");
        return;
    }
    // 选
    state1[x] = 1;
    DFS_exponent(x + 1);
    state1[x] = 0; // 回溯操作
    // 不选
    state1[x] = 2;
    DFS_exponent(x + 1);
    state1[x] = 0;
}
// 例2：N皇后问题
#include <cmath>
int row[15]; // row[x]=y表示第x行第y列放过棋子
int queen_n, cnt = 0;
bool Check(int x, int y)
{
    for (int i = 1; i <= x; i++) // 从第一行到第x行
    {
        if (row[i] == y)                   // 如果某一行在第y列有棋子
            return false;                  // 不可以再放了
        if (abs(x - i) == abs(y - row[i])) // 如果在点(x,y)的对角线上有棋子
            return false;
    }
    return true;
}
void DFS(int x) // 逐行搜索
{
    if (x == queen_n + 1) // 搜索结束条件
    {
        cnt++;
        return;
    }
    for (int y = 1; y <= queen_n; y++) // 对这一行的每一列
    {
        if (Check(x, y)) // 检查第x行(本行)的第y列可不可以放棋子
        {
            row[x] = y;
            DFS(x + 1);
            row[x] = 0; // 回溯
        }
    }
}
// int main()
// {
//     scanf("%d", &queen_n);
//     DFS(1);
//     printf("%d", cnt);
//     return 0;
// }

// 递归实现排列型枚举
const int N = 15;
int n2;
bool state2[N]; // 初始化为false表示没选过
int arr[N];
void DFS_permutation(int x) // x表示当前枚举到了哪个位置 依次枚举每个位置放哪个数
{
    if (x > n2) // 一个情况枚举完成的条件
    {
        for (int i = 1; i <= n2; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 1; i <= n2; i++)
    {
        if (!state2[i]) // 如果没有被选过
        {
            state2[i] = true; // 选他 状态记为选过了
            arr[x] = i;
            DFS_permutation(x + 1);
            arr[x] = 0; // 回溯
            state2[i] = false;
        }
    }
}
// 递归实现组合型枚举(每组按升序) 依次枚举每个位置放哪个数
// 如果要按字典序输出组合 那么原始的数组需要排序
const int N = 21;
int n3, r;
int arr2[N];                           // 记录生成的组合
void DFS_combination(int x, int start) // x记录当前枚举到了哪个位置 start记录当前位置从哪个数开始枚举
{
    if ((x - 1) + (n3 - start + 1) < r) // 剪枝操作 如果剩下的数不够生成这个组合 直接返回
        return;
    if (x > r) // 已经将所有的空位填完
    {
        for (int i = 1; i <= r; i++)
        {
            printf("%3d", arr2[i]);
        }
        printf("\n");
        return;
    }
    for (int i = start; i <= n3; i++)
    {
        arr2[x] = i;
        DFS_combination(x + 1, i + 1);
        arr2[x] = 0; // 回溯
    }
}

/*
四、DFS寻路
例：给出一张图，输出起点到终点的所有路径
输入：第一行为整数n,m 表示行数和列数 后面的n行，每行有m个字符
'@'表示起点 '*'表示终点 '#'表示是墙壁不能走 '.'表示是路能走。每一步都按照左->上->右->下的顺序寻路
其中1<n,m<7
输出：输出所有的路径 和路径总数
例图：
5 3
.#.
#@.
*..
...
#.#
*/
char mp[10][10];                                  // 地图
string p[10][10];                                 // 记录从起点到path[i][j]的路径
int d[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // 分别表示左 上 右 下  左上角的坐标是(0,0)
int Wy, Hx, min_room = 0;                         // Wy行 Hx列，用min_room统计路径的数量
int sx, sy, tx, ty;                               // 起点和终点
void DFS(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nx = x + d[i][0], ny = y + d[i][1]; // 表示一个邻居点
        if (nx >= Hx || nx < 0 || ny < 0 || ny >= Wy)
            continue;          // 不在地图内
        if (mp[nx][ny] == '*') // 遇到终点
        {
            min_room++;
            char t[4];
            sprintf(t, "%d%d", nx, ny);                             // 记录路径
            cout << min_room << ": " << p[x][y] + "->" + t << endl; // 输出路径
            continue;                                               // 不退出 继续寻找下一条路径
        }
        if (mp[nx][ny] == '.')
        {
            mp[nx][ny] = '#'; // 保存现场 这个点在这次更深的DFS中不可以使用
            char t[4];
            sprintf(t, "%d%d", nx, ny);
            p[nx][ny] = p[x][y] + "->" + t; // 记录路径
            DFS(nx, ny);
            mp[nx][ny] = '.'; // 恢复现场 回溯后这个点可以再使用
        }
    }
}
int Route_search_main()
{
    scanf("%d %d", &Wy, &Hx); // 图有Wy行、Hx列
    for (int y = 0; y < Wy; y++)
    {
        for (int x = 0; x < Hx; x++)
        {
            cin >> mp[x][y];
            if (mp[x][y] == '@')
            {
                sx = x;
                sy = y;
            }
            if (mp[x][y] == '*')
            {
                tx = x;
                ty = y;
            }
        }
    }
    printf("from %d%d to %d%d\n", sx, sy, tx, ty);
    char t[4];
    sprintf(t, "%d%d", sx, sy);
    p[sx][sy] = t;          // 开始记录路径
    DFS(sx, sy);            // 搜索并输出所有路径
    printf("%d", min_room); // 输出路径总数
    return 0;
}

// 五、DFS进行连通性判断
/*
DFS判断连通性的步骤如下：
(1)从图上任意一个点u开始遍历，标记点u已经被搜索过
(2)递归点u的所有符合连通条件的邻居点
(3)递归结束，找到了与点u连通的所有点，这是一个连通块
(4)不与点u连通的、其他没有访问到的点，继续用上述步骤处理，直到找到所有的连通块
注意：如果地图比较大，那么DFS的递归深度可能非常大，用DFS求解并不保险，应该使用BFS
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
const int N = 1e3 + 5;
char map[N][N];
bool vis[N][N];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
bool Can_survive;
int cnt = 0;
void DFS_connectivity(int x, int y)
{
    vis[x][y] = true;
    if (map[x - 1][y] == '#' && map[x + 1][y] == '#' && map[x][y - 1] == '#' && map[x][y + 1] == '#')
        Can_survive = true; // 找到了高地 不会被淹没
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (!vis[nx][ny] && map[nx][ny] == '#')
            DFS_connectivity(nx, ny);
    }
}
int connectivity_DFS_Main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", map[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!vis[i][j] && map[i][j] == '#')
            {
                Can_survive = false;      // 假设一个岛屿会被淹没
                DFS(i, j);                // 查找这个岛屿的连通部分 看有没有高地
                if (Can_survive == false) // 没有高地 被淹没的岛屿+1
                    cnt++;
            }
    printf("%d", cnt);
}
/*
注意：本体的测试数据不够好，所以DFS可以通过。如果有一个足够好的测试数据：
n=1000,除了四周是海洋，其他部分全是陆地，那么递归深度会超过5e4，将发生异常而退出
*/

// 六、剪枝
/*
BFS与DFS是暴力法的直接实现，但效率较低，浪费了时间在不必要的计算上
剪枝是常用的优化手段，可以优化时间复杂度
BFS的剪枝方法通常为判重，如果搜索到某一层时出现重复的状态，就剪枝
DFS的剪枝级数较多，有可行性剪枝、搜索顺序剪枝、最优性剪枝、排除等效冗余、记忆化搜索等
(1)可行性剪枝：对当前状态进行检查，如果当前状态不合法就不再继续，直接返回
(2)搜索顺序剪枝：搜索树有多个层次和分支，不同的搜索顺序会产生不同的搜索树形态，时间复杂度也相差很大
(3)最优性剪枝：在最优化问题的搜索过程中，如果当前花费的代价已经超过前面搜索到的最优解，
   那么本次搜索就没有必要再进行下去了，停止对当前状态的搜索，直接回溯
(4)排除等效冗余：搜索不同的分支，最后的结果是一样的，那么只搜索一个分支就够了
(5)记忆化搜索：在递归的过程中，有许多分支被重复计算，降低了效率，
   用记忆化搜索将已经计算出来的结果保存起来，以后需要使用时直接调用，避免重复运算
总之，剪枝就是为了减少搜索状态
*/

/*
例：分考场
n个人参加考试，任何两个认识的人不能分在同一个考场，求最少需要几个考场
输入：第一行一个整数n(1<n<100)，表示人数。 第二行一个数m，表示接下来有m行数据
      接下来m行，每行两个整数a,b(1<=a,b<=n,空格隔开)表示第a个人和第b个人认识(编号从1开始)
输出：一行 一个整数 表示最少分几个考场

解决方案：模拟把n个人安排进考场的计算过程。从第一个考场开始，逐个加入考生。
每新加入一个人x，都与已经开设的考场里面的人进行对比，如果认识，就将x换个考场，
直到找到一个考场，考场里面的人都不认识x。如果x在所有考场都有熟人，就新开考场
这样可以得到一种可行的考场安排，但不一定是最少的，那么需要将所有可能的考场都试一次，找到最少的安排
用DFS求出所有情况，得到最少考场，用剪枝减少搜索量。
在搜索一种安排时，如果需要的考场数量已经超过了原来某个可行的安排，那么直接停止
*/
const int N = 110;
int relative[N][N];   // 关系表，relative[i][j]=1表示第i个人和第j个人认识
int room_state[N][N]; // 考场状态 room_state[i][j]=t表示第i个考场的第j个座位坐第t个人
int min_room = N;
int n, m;
void Room_distribute_DFS(int x, int room) // 尝试将第x个人安排到第1-room考场
{
    if (room > min_room)
        return; // 当前需要的考场数量已经大于最优解
    if (x > n)  // 全部安排完了
    {
        min_room = min(min_room, room);
        return;
    }
    int i, j;
    for (i = 1; i <= room; i++) // 枚举考场，将第x个人放进第i个考场
    {
        j = 1;                                                     // 第j个座位
        while (room_state[i][j] && !relative[x][room_state[i][j]]) // i考场的j座位有人坐且这个人不认识第x个人
            j++;                                                   // 下一个座位
        if (room_state[i][j] == 0)                                 // j座位没人坐
        {
            room_state[i][j] = x;             // 第i个考场的第j个座位，安排给第x个人坐
            Room_distribute_DFS(x + 1, room); // 第x个人安排好了，继续安排下一个
            room_state[i][j] = 0;             // 回溯，释放这个座位
        }
    }
    room_state[room + 1][1] = x;          // 第1-room个考场都不能坐，x只能坐第room+1个考场的第一个座位
    Room_distribute_DFS(x + 1, room + 1); // 继续安排第x+1个人，尝试第1-第room+1个考场
    room_state[room + 1][1] = 0;          // 回溯
}
int Room_distrubute_Main()
{
    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 1; i <= n; i++)
    {
        // 矩阵表示两人关系
        scanf("%d %d", &a, &b);
        relative[a][b] = 1;
        relative[b][a] = 1;
    }
    Room_distribute_DFS(1, 1); // 第一个人坐第一个考场
    printf("%d", min_room);
    return 0;
}