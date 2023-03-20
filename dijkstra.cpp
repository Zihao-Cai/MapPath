#include "dijkstra.h"
#include "min_weight.h"



void dijkstra(AMGraph* G,int V,int src,double weight[],QVector<QString>* path_city){

        bool vis[V+1];
        for(int i=1;i<=V;i++)
        {
            vis[i] = false;
            weight[i] = G->arcs[src][i];
        }

        weight[src] = 0;            //起点到起点的最短路径为0，此后无需考虑
        vis[src] = true;

        for(int i=1;i<=V;i++)
        {	//（外部主循环for，代表求索更新的步骤或者趟数）
            int u = min_weight(weight, vis, V);
            vis[u] = true;
            //每一趟找到最小路径顶点u；同时顶点u即可并入路径，所以vis[u]置为true
            for(int j=1;j<=V;j++)
            {	//（内部循环for，该循环应该是在上述新结点并入后更新计算各个结点路径的操作）
                if(!vis[j] && G->arcs[u][j] != 0 && weight[u] + G->arcs[u][j] < weight[j])
                {
                    weight[j] = weight[u] + G->arcs[u][j];//经过中间结点的路径更新为最短路径值
                    //path_city[j].push_back(G->vexs[u]);//同时将该中间结点并入该结点最短路径的城市集中
                }
            }

        }
        return ;
}







