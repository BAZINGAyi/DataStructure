#include <iostream>
using namespace std;

/**
 这里通过邻接矩阵来构建邻接表
 **/

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100
#define MAXSIZE 9 /* 存储空间初始分配量 */

typedef int Status;

typedef char VertexType;

typedef int  EdgeType; // 权值

// 邻接矩阵结构
typedef struct{
    VertexType vex[MAXVEX]; // 顶点表
    
    EdgeType arc[MAXVEX][MAXVEX]; //邻接矩阵 边表
    
    int numEdges = 15;
    
    int numVertexes = 9;
    
}MGraph;



// 边表节点
typedef struct EdgeNode{
    
    int adjvex;     // 存储该顶点对应的下标
    
    EdgeType info;
    
    struct EdgeNode * next;
    
}EdgeNode;

// 顶点节点
typedef struct VertexNode{
    // 统计每个顶点的入度
    int in;
    
    VertexType data;
    
    EdgeNode * firstedge; // 第一个指向边表的指针
    
}VertexNode,AdjList[MAXVEX];

// 图的邻接表结构
typedef  struct {
    
    AdjList adjList;
    
    int numNodes,numEdges;
    
}GraphAdjList,*GraphAdjListLink; // 定义邻接表的指针

/**********************/
/**
 定义用到的数据结构队列  
 使用的是循环队列 (判断队列满的方法为差一个位置)
 **/
typedef struct {
    
    int data[MAXSIZE]; //用来存放被访问的结点
    
    int front;
    
    int rear;

}Queue;


Status InitQueue(Queue * q){
    q->front = 0;
    q->rear = 0;
    return OK;
}

Status QueueEmpty(Queue q){
    if(q.front == q.rear)
        return TRUE;
    else
        return FALSE;
}

Status DeQueue(Queue *q,int *e){
    
    // 队列空的条件判断
    
    if(q->front == q->rear)
        return ERROR;
    
    *e=q->data[q->front];
    
    q->front = (q->front+1)%MAXSIZE;
    
    return OK;
}

Status EnQueue(Queue * Q, int e){
    
    // 队列满的条件
    if((Q->rear+1)%MAXSIZE == Q->front)
        
        return ERROR;
    
    Q->data[Q->rear] = e;
    
    Q->rear = (Q->rear+1)%MAXSIZE;
    
    return OK;
}


/************************/


/************************/
/**
 使用邻接矩阵的构建图
 **/


void CreateMGraph(MGraph *G){

    int i , j;
    
    G->numEdges = 15;
    
    G->numVertexes = 9;
    
    // 输入顶点的结点
    G->vex[0] = 'A';
    G->vex[1] = 'B';
    G->vex[2] = 'C';
    G->vex[3] = 'D';
    G->vex[4] = 'E';
    G->vex[5] = 'F';
    G->vex[6] = 'G';
    G->vex[7] = 'H';
    G->vex[8] = 'I';
    
    // 邻接矩阵初始化
    for(i = 0; i < G->numVertexes; i++ ){
        for (j = 0; j < G->numVertexes; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    // 随机生成图
    
    G->arc[0][1] = 1;
    G->arc[0][5] = 1;
    
    G->arc[1][2] = 1;
    G->arc[1][8] = 1;
    G->arc[1][6] = 1;
    
    G->arc[2][3] = 1;
    G->arc[2][8] = 1;
    
    G->arc[3][4] = 1;
    G->arc[3][7] = 1;
    G->arc[3][6] = 1;
    G->arc[3][8] = 1;
    
    G->arc[4][5] = 1;
    G->arc[4][7] = 1;
    
    G->arc[5][6] = 1;
    
    G->arc[6][7] = 1;
    
    //因为构建的是无向图，
    
    for(i = 0; i < G->numVertexes; i++){
        for( j = i; j < G->numVertexes; j++)
            G->arc[j][i] = G->arc[i][j];
    }

}


// 使用邻接矩阵构建邻接链表
void CreateALGraph(MGraph G, GraphAdjListLink * GL){
    
    int i , j;
    
    EdgeNode * e;
    
    *GL = (GraphAdjListLink)malloc(sizeof(GraphAdjList));
    
    (*GL)->numEdges = G.numEdges;
    
    (*GL)->numNodes = G.numVertexes;
    
    // 生成顶点表
    for(i= 0;i <G.numVertexes;i++) /* 读入顶点信息,建立顶点表 */
    {
        (*GL)->adjList[i].in=0;
        (*GL)->adjList[i].data=G.vex[i];
        (*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
    }
    
    
    // 生成邻接表
    for(i = 0; i < G.numVertexes; i++){
        for (j = 0; j < G.numVertexes; j++) {
            if(G.arc[i][j] == 1){
                
                e = (EdgeNode * )malloc(sizeof(EdgeNode));
                
                e->adjvex = j;
                
                e->next = (*GL)->adjList[i].firstedge;
                
                
                (*GL)->adjList[i].firstedge = e;
                (*GL)->adjList[j].in ++ ; // 顶点入度加1
            
            }
        }
    }

}

/*********************/

/**********************／
/** 深度优先相关 遍历所有结点**/

/** 过程:
    1. 依次遍历顶点表的每个顶点，防止非连通图的出现
    2. 如果该顶点没有访问，则访问该顶点，
    3. 找到与该顶点相连的第一个临界点，进行递归，结束条件是 p 的临界点为空
    4. 继续从第一个顶点的第二个邻接点进行遍历
 **/

bool visited[MAXSIZE];

void DFS(GraphAdjListLink GL,int pos){
    
    EdgeNode *p;
    
    visited[pos] = true;
    
    cout<<GL->adjList[pos].data<<endl;
    
    p = GL->adjList[pos].firstedge;
    
    while (p) {
        
        if(!visited[p->adjvex])
            DFS(GL, p->adjvex);
        
        p = p->next;
    }
}

void DFSTraverse(GraphAdjListLink GL){
    int i;
    for(i = 0; i < (GL)->numEdges; i++)
        visited[i] = FALSE;
    for (i = 0; i < GL->numNodes; i++) {
        if(visited[i] == FALSE){
            DFS(GL,i);
        }
    }

}


/**********************/
// 邻接表的广度遍历算法

/** 过程：1. 依次从顶点表开始遍历 防止非连通图的出现
         2. 判断结点有没有被访问
         3. 没有被访问则进入队列
         4. 判断队列是否为空，如果不为空，出队列，并且将与顶点直接相连的所有临近点按照顺序入队列
         5. 重复 1 - 4 的过程
**/
void BFSTraverse(GraphAdjListLink GL){
    
    int i;
    
    EdgeNode *p;
    
    Queue Q;
    
    for(i =0; i < GL->numNodes; i++)
        visited[i] = FALSE;
    
    InitQueue(&Q);
    
    for(i = 0; i < GL->numNodes; i++){
    
        if(!visited[i]){
            
            visited[i] = true;
            
            cout<<GL->adjList[i].data<<endl;
            
            EnQueue(&Q, i);
            
            while (!QueueEmpty(Q)) {
                
                DeQueue(&Q, &i);
                
                p = GL->adjList[i].firstedge;
                
                while (p) {
                    
                    if(!visited[p->adjvex]){
                        
                        visited[p->adjvex] = true;
                        
                        cout<<GL->adjList[p->adjvex].data<<endl;
                        
                        EnQueue(&Q, p->adjvex);
                    }
                    
                    p = p->next;
                }
                
            }
        }
    }
    
}

 
int main(int argc, const char * argv[]) {
    
    MGraph G;
    GraphAdjListLink GL;
    CreateMGraph(&G);
    CreateALGraph(G,&GL);
    
    printf("\n深度遍历:");
    DFSTraverse(GL);
    printf("\n广度遍历:");
    BFSTraverse(GL);
    return 0;
    
    
    return 0;
}
