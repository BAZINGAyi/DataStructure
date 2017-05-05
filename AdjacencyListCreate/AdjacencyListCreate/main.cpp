#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0
#define MAXVEX 100

typedef int Status;

typedef char VertexType;

typedef int  EdgeType; // 权值

// 边表节点
typedef struct EdgeNode{
    
    int adjvex;
    
    EdgeType info;
    
    struct EdgeNode * next;
    
}EdgeNode;

// 顶点节点
typedef struct VertexNode{
    
    VertexType data;
    
    EdgeNode * firstedge; // 第一个指向边表的指针
    
}VertexNode,AdjList[MAXVEX];

// 图的邻接表结构
typedef  struct {
    
    AdjList adjList;
    
    int numNodes,numEdges;
    
}GraphAdjList;

void CreateALGraph(GraphAdjList * G){
    int i,j,k;
    
    EdgeNode *e;
    
    printf("输入顶点数和边数：\n");
    
    cin>>G->numNodes>>G->numEdges;
    
    //顶点表创建
    for(i = 0; i < G->numNodes; i++){
        
        cin>>G->adjList[i].data;
        
        G->adjList[i].firstedge = NULL;
    }
    
    // 无向图的边表创建  使用头头插法
    for(k = 0;k < G->numEdges; k++){
        
        cout<<"输入边 (vi,vj) 上的顶点序号:\n";
        
        cin>>i>>j;
        
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        
        e->adjvex = j;
        
        e->next = G->adjList[i].firstedge;
        
        G->adjList[i].firstedge = e;
        
        
        
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        
        e->adjvex = i;
        
        e->next = G->adjList[j].firstedge;
        
        G->adjList[j].firstedge = e;
        
    }
}
int main(int argc, const char * argv[]) {
    
    GraphAdjList G;
    
    CreateALGraph(&G);
    
    return 0;
}
