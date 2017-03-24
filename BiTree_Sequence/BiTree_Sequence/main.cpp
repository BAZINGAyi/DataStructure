#include <iostream>
#include <stdlib.h>
#include "math.h"
#include "time.h"
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int  TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE]; // 0 号单元存储根节点

typedef struct {
    
    int level,order; //节点的层，本层序号(按满二叉树计算)
    
}Postion;

TElemType Nil = 0;   //设整型以 0 为空

Status visit(TElemType c){
    
    cout<<c<<" ";
    
    return OK;
}

// 构造空二叉树 T 。因为 T 是固定数组，不会改变，故不需要 & *。
// 在顺序存储结构中，初始化和清空二叉树是一样的
#define InitBiTree ClearBiTree
Status InitBiTree(SqBiTree T){
    
    for (int i = 0; i < MAXSIZE; i++) {
        
        T[i] = Nil;
        
    }
    
    return OK;
}

// 注：根据节点位置求双亲节点位置的方法为 (i／2) (1 <= i <= n)
// 这里位置是从 0 开始的，所以求双亲的位置的方法为 (i + 1)／2  求出来的数还需要减 1
// 因为是从第 0 个位置开始算，综上：(i + 1)／2 - 1
Status CreateBiTree(SqBiTree T){
    
    // 正常来这里是输入的，后面再改，先使用自动生成的
    
    int i = 0;
    
    while (i < 10) {
        
        T[i] = i + 1;
        
        //如果不是根节点，出现父母位置为空，而孩子位置不为空，则有错误
        if(i != 0 && T[(i + 1)/2 - 1] == Nil && T[i] != Nil){
            
            cout<<"出现无双亲的非根节点"<<T[i]<<endl;
            
            exit(ERROR);
        }
        
        i++;
        
    }
    
    while(i < MAX_TREE_SIZE){
        
        T[i++] = Nil;
        
    }

    return OK;
}

Status BiTreeEmpty(SqBiTree T){
    
    if (T[0] == Nil)
        
        return TRUE;
    
    else
        
        return ERROR;

}

// 由二叉树的性质 2 深度为 k 的二叉树至多有 pow(2,k) - 1 个节点 （k >= 1）
int BiTreeDepth(SqBiTree T){
    
    if (BiTreeEmpty(T))
        
        return ERROR;
    
    // 先确定树节点的总个数
    int count,depth = 1;
    
    for(count = MAX_TREE_SIZE - 1; count >= 0; count-- )
        
        if(T[count] != Nil)
            
            break;
    
    count++;
    
    while(1){
        
        if(pow(2, depth) - 1 >= count)
            
            break;
        
        depth++;
    }
    
    return depth;
}
//开始判断树的第一个节点的值是否为空
int BiTreeDepth1(SqBiTree T,int node = 0){
    
    if (T[node] == Nil)
        
        return 0;
    
    int left = 1 + BiTreeDepth1(T, (node + 1) * 2 - 1);
    
    int right = 1 + BiTreeDepth1(T,(node + 1) * 2 + 1 -1);
    
    return right > left ? right:left;
}

// 若二叉树存在返回 T 的根，否则返回 ERROR ;
Status Root(SqBiTree T, TElemType *e){
    
    if (BiTreeEmpty(T))
        
        return ERROR;
    
    * e = T[0];
    
    return OK;
}
// 返回 e(层，本层序号) 的节点的值
// 因为数组是从 0 开始，只需要按照正常的求法，之后在数组中找数时减一个位置就好
// 所以在数组的位置为 第 i 层的节点数，加上该层的第几个节点
// 即：pow(2,e.level) - 1 为第二层节点的个数，+ e.order 再减 1 即可
TElemType Value(SqBiTree T, Postion e){
    
    return T[(int)powl(2,e.level - 1) - 1 + e.order - 1 ];
    
}
// 给 e(层，本层序号) 的结点赋新值 value
// 注：双亲节点为空，该节点的叶子节点必定为空
//    叶子节点不为空，则它的双亲节点一定不为空。
Status AssignValue(SqBiTree T, Postion e,TElemType value){
    
    if(BiTreeEmpty(T))
        
        return ERROR;
    
    int index = ((int)powl(2, e.level - 1) - 1 + e.order ) - 1; // 便于理解
    
    if(value != Nil && T[(index+1) / 2 - 1] == Nil)             // 给没有双亲的节点付非空值
        
        return ERROR;
    
    if (value == Nil && (T[2 * index + 1] != Nil || T[ 2 * index + 1 +1] != Nil)) // 给有孩子的节点赋空值
                                                                          // 正常来说左孩子是 2i,右孩子是 2i+1
                                                                          // 但数组的下标是从 0 开始,需要向后错一个
        
        return ERROR;
    
    T[index] = value;
    
    return OK;
}
// e 是某个节点，返回 e 的双亲
TElemType Parent(SqBiTree T, TElemType e){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
        
        if (T[i] == e)
            
            return T[(i+1)/2 - 1];
    
    return Nil;
}
// 返回 e 的左孩子
TElemType LeftChild(SqBiTree T, TElemType e){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
        
        if (T[i] == e)
            
            return T[2 * i + 1];
    
    return ERROR;
    
}
// 返回 e 的右孩子
TElemType RightChild(SqBiTree T,TElemType e){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
        
        if (T[i] == e)
            
            return T[2 * i + 2];
    
    return ERROR;
}
// 返回 e 的左兄弟
TElemType LeftSibing(SqBiTree T, TElemType e){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
        
        if (T[i] == e && i%2 == 0) // 找到 e 并且是偶数位置
            
            return T[i - 1];
    
    return Nil;
}
// 返回 e 的右兄弟
TElemType RightSibing(SqBiTree T, TElemType e){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
        
        if (T[i] == e && i%2)
            
            return T[i + 1];
    
    return Nil;
}
// 前序遍历调用
void PreTraverse(SqBiTree T,int e){
    
    visit(T[e]);
    
    if (T[2 * e + 1] != Nil)  // 左子树不为空
        
        PreTraverse(T, 2 * e + 1);
    
    if(T[2 * e + 2] != Nil)   // 右子树不为空
        
        PreTraverse(T, 2 * e + 2);
}
// 前序遍历
Status PreOrderTraverse(SqBiTree T){
    
    if(BiTreeEmpty(T))
    
        return ERROR;
    PreTraverse(T, 0);
    
    cout<<endl;
    
    return OK;
}
// 中序遍历调用
void InTraverse(SqBiTree T, int i){
    
    if(T[2 * i + 1]!= Nil)
        
        InTraverse(T, 2 * i + 1);
    
    visit(T[i]);
    
    if (T[2 * i + 2] != Nil)
        
        InTraverse(T, 2 * i + 2);
}
// 中序遍历
Status InOrderTraverse(SqBiTree T){
    
    if(BiTreeEmpty(T))
        
        return  ERROR;
    
    InTraverse(T, 0);
    
    cout<<endl;
    
    return  OK;
}
// 后序遍历调用
void PostTravers(SqBiTree T, int i){
    
    if(T[2 * i + 1] != Nil)
        
        PostTravers(T, 2 * i + 1);
    
    if (T[2 * i + 2] != Nil)
        
        PostTravers(T, 2 * i + 2);
    
       visit(T[i]);
}

// 后序遍历
Status PostOrderTraverse(SqBiTree T){
    
    if(BiTreeEmpty(T))
        
        return  ERROR;
    
    PostTravers(T, 0);
    
    cout<<endl;
    
    return  OK;
}

// 按层，层序号输出二叉树
Status LevelOrderTraverse(SqBiTree T){
    
    if (BiTreeEmpty(T))
        
        return ERROR;
    
    int i,j;
    
    Postion p;
    
    TElemType e;
    
    for (i = 1; i <= BiTreeDepth1(T); i++) {
        
        cout<<"第"<<i<<"层"<<endl;
        
        for(j = 1; j <= powl(2, i - 1); j++){
            
            p.level = i;
            
            p.order = j;
            
            e = Value(T, p);
            
            if (e != Nil)
                
                cout<<j<<":"<<e<<endl;
        }
        
        cout<<endl;
    }
    
    return OK;
}


int main(int argc, const char * argv[]) {
    
    Status i;
    
    Postion p;
    
    TElemType e;
    
    SqBiTree T;
    
    InitBiTree(T);
    
    CreateBiTree(T);
    
    cout<<"建立二叉树后,树空否？(1:是 0:否) 树的深度\n";
    
    cout<<BiTreeEmpty(T)<<" "<<BiTreeDepth(T)<<endl;
    
    i = Root(T, &e);
    
    if (i)
        
        cout<<"二叉树的根为:"<<e<<endl;
    
    else
    
        cout<<"树空"<<endl;
    
    cout<<"层序遍历二叉树"<<endl;
    
    LevelOrderTraverse(T);
    
    cout<<"先序遍历二叉树"<<endl;
    
    PreOrderTraverse(T);
    
    cout<<"中序遍历二叉树"<<endl;
    
    InOrderTraverse(T);
    
    cout<<"后序遍历二叉树"<<endl;
    
    PostOrderTraverse(T);
    
    cout<<"修改结点的层号3本层序号2"<<endl;
    
    p.level = 3;
    
    p.order = 2;
    
    e = Value(T, p);
    
    cout<<"代修改的原值为:"<<e<<endl;
    
    cout<<"输入修改后的值为50"<<endl;
    
    e = 50;
    
    AssignValue(T, p, e);
    
    cout<<"先序遍历二叉树"<<endl;
    
    PreOrderTraverse(T);
    
    cout<<"结点"<<e<<"双亲为:"<<Parent(T,e)<<endl<<"左右孩子分别为 0为没有孩子 ";
    
    cout<<LeftChild(T,e)<<" "<<RightChild(T,e)<<endl;
    
    cout<<"左右兄弟分别为 0为没有兄弟 "<<LeftSibing(T,e)<<" "<<RightSibing(T,e)<<endl;
    
    ClearBiTree(T);
    
    cout<<"清除二叉树后,树空否？(1:是 0:否) 树的深度"<<BiTreeEmpty(T)<<" "<<BiTreeDepth(T)<<endl;
    
    i=Root(T,&e);
    
    if(i)
        cout<<"二叉树的根为："<<e<<endl;
    else
          cout<<"树空"<<endl;
    
    
    return 0;
}
