#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535 // 无穷

typedef int Status;

/**
 以邻接矩阵作为存储结构
 **/

typedef struct {
    char vex[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int vexNumbers,edgenumbers;
}MGraph;

typedef int Patharc[MAXVEX]; // 存放每个结点的最短前缀结点下标

typedef int ShortPathTable[MAXVEX] ; // 存放达到每个结点的最短路径的权值

void CreateMGraph(MGraph * G){
    
    int i,j;
    
    G->vexNumbers = 9;
    
    G->edgenumbers = 16;
    
    for(i = 0; i < G->vexNumbers; i++){
        G->vex[i] = 'A' + i;
    }
    
    for(i = 0; i < G->vexNumbers; i++){
        for(j = 0; j < G->vexNumbers; j++){
            if(j == i)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = INFINITY;
        }
    }
    
    G->arc[0][1]=1;
    G->arc[0][2]=5;
    G->arc[1][2]=3;
    G->arc[1][3]=7;
    G->arc[1][4]=5;
    
    G->arc[2][4]=1;
    G->arc[2][5]=7;
    G->arc[3][4]=2;
    G->arc[3][6]=3;
    G->arc[4][5]=3;
    
    G->arc[4][6]=6;
    G->arc[4][7]=9;
    G->arc[5][7]=5;
    G->arc[6][7]=2;
    G->arc[6][8]=7;
    
    G->arc[7][8]=4;
    
    
    for(i = 0; i < G->vexNumbers; i++)
    {
        for(j = i; j < G->vexNumbers; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
    
}

void ShortestPath_Dijkstra(MGraph G, int v0, Patharc * P, ShortPathTable * D){
    
    int final[MAXVEX]; // 用于标记结点是否已经找到最短的路径
    int min,k,v,w;
    
    for(v = 0; v < G.vexNumbers;v++){
        final[v] = 0; // 初始化所有结点没有找到最短的路径
        (*D)[v] = G.arc[v0][v]; // 将结点 0 到其它结点的距离加入到最短的路径数组中
        (*P)[v] = -1; // 初始化所有结点的前缀结点为 -1 表示没有找到最短的路径
    }
    
    (*D)[v0] = 0;
    final[v0] = 1; // 表示及结点 0 到结点 0 的最短距离已经找到了
    
    for(v = 1; v < G.vexNumbers;v++){
        
        min = INFINITY;
        
        // 找到 v0 与其它结点之间长度最短的结点
        for(w = 0; w < G.vexNumbers; w++){
            
            if(!final[w] && (*D)[w] < min){
                
                k = w;
                
                min = (*D)[w];
            }
        }
        
        final[k] = 1; // 表示到位置 k 的最短路径已经找到了
        
        // 根据新加入的结点更新之前 V0 刀到各个顶点的值
        
        for(w = 0; w < G.vexNumbers; w++){
            // 如果 V0 到新加入的节点的最小值加上，新节点到其它结点的值 比 原来 V0 到
            // 其它结点的值小, 那么更新 V0
            // k 新结点的位置
            if(!final[w] && (min + G.arc[k][w]) < (*D)[w]){
                (*D)[w] = min + G.arc[k][w];
                (*P)[w] = k;    // 如 p[2] = 1; 则代表 v0 到 V2 节点的最短路径的前驱结点是 V1 结点
            }
        }
        
    }
    
}


int main(){
    
    int i,j,v0;
    
    MGraph G;
    
    Patharc P;
    
    ShortPathTable D;
    
    v0 = 0;
    
    CreateMGraph(&G);
    
    ShortestPath_Dijkstra(G, v0, &P, &D);
    
    for(i = 1; i < G.vexNumbers; i++){
        printf("v%d - v%d : ",v0,i);
        j=i;
        while(P[j]!=-1)
        {
            printf("%d ",P[j]);
            j=P[j];
        }
        cout<<endl;
    }
    
    for(i=1;i<G.vexNumbers;++i)
        printf("v%c - v%c : %d \n",G.vex[0],G.vex[i],D[i]);
    return 0;
}
