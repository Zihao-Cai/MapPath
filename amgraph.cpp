#include "amgraph.h"


bool AMGraph::DFS(int v)
{
    if(v<1 || v>n)   return false;
    bool isvisit[n+1] = {false};
    //这里补充访问v顶点的代码
    isvisit[v] = true;
    for(int j=1;j<=n;j++){
        if(arcs[v][j]!=ENDLESS && !isvisit[j]){
            DFS(j);
        }
    }
    return true;
}

AMGraph::AMGraph()
{

}
