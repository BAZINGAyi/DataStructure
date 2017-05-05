#include <iostream>

using namespace std;

#include "stdlib.h"

#include "math.h"

#include "time.h"
// 无向图的创建
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100                  // 最大的顶点数
#define INFINITY 65535
#define MAXSIZE   9                   // 初始化的分配量
typedef int Boolean;
Boolean visited[MAXSIZE];



typedef int Status;
typedef int VertexType ;            // 顶点的类型
typedef int EdgeType;               // 边上权值的类型
typedef struct{
    
    VertexType vex[MAXVEX];         // 顶点表
    
    EdgeType arc[MAXVEX][MAXVEX];   // 邻接矩阵
    
    int numNodes, numEdges;         // 图中当前的顶点数和边数
    
}MGraph;

void CreateMGraph(MGraph * G){
    
    int i,j;
    
    int k,w;
    
    cout<<"输入顶点数和边数"<<endl;
    
    cin>>G->numNodes>>G->numEdges;
    
    for(i = 0;i <G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
        
        cin>>(G->vex[i]);
    
    for (i = 0; i < G->numNodes ; i++) { // 邻接矩阵初始化
        
        for (j = 0; i < G->numNodes ; i++) {
            
            G->arc[i][j] = INFINITY;
            
        }
    }
    
    for(k = 0; k < G->numEdges; k++){
        
        cout<<"输入边 (vi,vj)上的下标i，下标j,和权值w:"<<endl;
        
        cin>>i>>j>>w;
        
        G->arc[i][j] = w;
        
        G->arc[j][i] = G->arc[i][j]; // 无向图对称
        
    }
}

void CreateMGraph1(MGraph * G){
    int i, j;
    
    G->numEdges=15;
    G->numNodes=9;
    
    /* 读入顶点信息，建立顶点表 */
    G->vex[0]='A';
    G->vex[1]='B';
    G->vex[2]='C';
    G->vex[3]='D';
    G->vex[4]='E';
    G->vex[5]='F';
    G->vex[6]='G';
    G->vex[7]='H';
    G->vex[8]='I';
    
    
    for (i = 0; i < G->numEdges; i++)/* 初始化图 */
    {
        for ( j = 0; j < G->numEdges; j++)
        {
            G->arc[i][j]=0;
        }
    }
    
    G->arc[0][1]=1;
    G->arc[0][5]=1;
    
    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;
    
    G->arc[2][3]=1;
    G->arc[2][8]=1;
    
    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][6]=1;
    G->arc[3][8]=1;
    
    G->arc[4][5]=1;
    G->arc[4][7]=1;
    
    G->arc[5][6]=1;
    
    G->arc[6][7]=1;
    
    
    for(i = 0; i < G->numEdges; i++)
    {
        for(j = i; j < G->numEdges; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
    
    
}

void DFS(MGraph G, int i){
    
    int j;
    
    visited[i] = TRUE;
    
    cout<<G.vex[i]<<endl;
    
    for (j = 0; j < G.numNodes; j++) {
        
        if(G.arc[i][j] != 0 && visited[j] == FALSE)
            
            DFS(G, j);
    }
    
}

void DFSTraverse(MGraph G){
    
    int i;
    
    for (int i = 0; i < G.numNodes; i++) { // 初始化所有访问的结点
        
        visited[i] = FALSE;
    }
    
    for (i = 0 ; i < G.numNodes; i++) {
        
        if(!visited[i])
            
            DFS(G,i);
    }
    
}

int main(int argc, const char * argv[]) {
    
    MGraph G;
    
    CreateMGraph1(&G);
    
    cout<<"深度遍历"<<endl;
    
    DFSTraverse(G);
    
    return 0;
}
