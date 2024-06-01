#include "../../Heads/Head.h"

// LCA应用1:树上两点的最近距离

/*
    树上两点最近距离 = 两点深度之和减去两倍LCA深度
    Distance(x,y) = Depth[x] + Depth[y] - 2 * Depth[LCA(x,y)]
*/
