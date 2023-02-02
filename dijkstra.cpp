#include "dijkstra.h"



void dijkstra(AMGraph* G,int city1,int city2){

/*这里是求无向网的最短路径,故两城市起点终点可以互换,这里默认1为起点,2为终点*/
    int u = city1;//用u代替起点参数保护原始数据
    int n = G->n;
    int D[n];//以1-13为下标设置辅助向量D,记录到各地点的最短路径长度
    QVector<int> S;//辅助向量,记录已并入路径的地点下标
    S.push_back(u);
    QVector<int> path;
    for(int k=0;k<n-1;k++){  //最多需要循环n-1次
        //每次循环都要找到未并入路径的顶点的最短路径长度,如下:





    }


}


bool inpath(QVector<int> S, int index)
{
    for(int i=0;i<S.size();i++){
        if(S[i] == index)   return true;
    }
    return false;
}

