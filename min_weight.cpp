#include "min_weight.h"


int min_weight(double weight[], bool vis[], int V)
{
    int min_weight = ENDLESS, min_index = -1;

        for(int i=1;i<=V;i++)
        {
            if(!vis[i] && weight[i] < min_weight)	//如果结点i还没有访问（并入路径），并且	起点到该点的路径长度小于当前最小值
            {
                min_weight =weight[i];
                min_index = i;
            }
        }
        return min_index;               //找到路径长度最短的结点并返回（此时vis没有更新，说明该子函数未将其并入路径）
}
