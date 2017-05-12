#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;

typedef struct {
    
    int arc[MAXVEX][MAXVEX];
    
    int numVertexes, numEdges;
    
}MGraph;

void CreateMGraph(MGraph * G){
    
    int i, j;

    G->numEdges = 15;

    G->numVertexes = 9;
    
    // 无向图
    for(i = 0;i < G->numVertexes; i++){
        for(j = 0; j < G->numVertexes; j++){
            
            // 自己到自己的权值是 0
            if(i == j)
                G->arc[i][j] = 0;
            
            else
                G->arc[i][j] = G->arc[j][i] = INFINITY;
        }
    }
    
    G->arc[0][1]=10;
    G->arc[0][5]=11;
    G->arc[1][2]=18;
    G->arc[1][8]=12;
    G->arc[1][6]=16;
    G->arc[2][8]=8;
    G->arc[2][3]=22;
    G->arc[3][8]=21;
    G->arc[3][6]=24;
    G->arc[3][7]=16;
    G->arc[3][4]=20;
    G->arc[4][7]=7;
    G->arc[4][5]=26;
    G->arc[5][6]=17;
    G->arc[6][7]=19;
    
    for(i = 0; i < G->numVertexes; i++)
    {
        for(j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
}


void MiniSpanTree_Prim(MGraph G){
    int i , j;
    
    int k; // 保存找到结点的最小值。
    
    int adjvex[MAXVEX] ; // 用于保存相关结点的下标 ，最后根据还原路径.
    
    int lowcost[MAXVEX] ; // 用于保存相关结点的权值
    
    int min;
    
    lowcost[0] = 0;   // 默认从第一个结点开始开始，所以标记为0，代表该结点已经被确认，加入到生成树中
    
    adjvex[0] = 0;    // 初始化第一个结点
    
    for (i = 1; i < G.numVertexes; i++) {
        // 将 与 VO 顶点有边的权值存入数组
        lowcost[i] = G.arc[0][i];
        
        // 表示当前的结点都和 VO 相关
        adjvex[i] = 0;
    }
    
    for (i = 1; i < G.numVertexes; i++) {
        
        min = INFINITY;
        
        j = 1, k = 0;
        
        while (j < G.numVertexes) {
             // 找到与 当前访问的顶点 相关的最小权值
             // ！= 0 代表已经加入了最小的生成树中
            if(lowcost[j] != 0 && lowcost[j] < min){
                min = lowcost[j];
                k = j;
            }
            j ++ ;
        }
        
        cout<<adjvex[k]<<" "<<k<<endl;
        
        lowcost[k] = 0; // 加入到最小的生成树中.
        
        // 根据新加入的顶点，找到与所有顶底相关最小的权值，并标记为当前的顶点的下标
        for( j = 1; j < G.numVertexes; j++){
            if(lowcost[j] != 0 && G.arc[k][j] < lowcost[j]){
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
            }
        }
        
    }
}




int main(int argc, const char * argv[]) {
   	MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G);
}
