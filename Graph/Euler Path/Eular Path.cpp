#include "../../Heads/Head.h"
/*
欧拉路:从图中某个点出发,遍历整个图,图中每条边通过且仅通过一次
      起点和终点相同的欧拉路是欧拉回路

欧拉路的存在性判断:
[1]无向图
    如果图中的点全部是偶点(点的度数为偶数),必有欧拉回路,任何点可作为起点和终点。
    如果只有两个奇点(点的度数为奇数),则存在欧拉路,一个奇点是起点,另一个奇点是终点。
    (注:没有奇数个奇点的无向图)
[2]有向图
    有向图的点的度数:将入度记为-1,出度记为1,两者相加即为有向图的一个点的度数。
    当且仅当有向图所有点的度数为0,欧拉回路存在。
    当只有一个度数为1的点,一个度数为-1的点,其他所有点的度数为0,欧拉路存在,度数为1的是起点,度数为-1的是终点。
*/