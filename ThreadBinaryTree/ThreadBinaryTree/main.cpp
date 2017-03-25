#include <iostream>

using namespace std;

#include "string.h"

#include "math.h"

#include "stdlib.h"

#define MAXSIZE 100

#define OK 1

#define ERROR 0

#define TRUE 1

#define FALSE 0

typedef int Status;

typedef char TElemType;

typedef enum{Link, Thread} PointerTag;

typedef struct BiThrNode{
    
    TElemType data;
    
    struct BiThrNode * leftChild, *rightChild;
    
    PointerTag leftTag, rightTag;
    
}BiThrNode, *BiThrTree;

TElemType Nil = '#';  // 字符型以空格符为结束

Status visit(TElemType e){
    
    printf("%c ", e);
    
    return OK;
}

// 前序输入二叉线索树中结点的值，构造二叉线索树T
// 0/' '表示空结点
Status CreateBiThrTree(BiThrTree * T){
    
    TElemType c;
    
    scanf("%c",&c);
    
    if(c == Nil)
        
        *T = NULL;
    
    else{
        
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        
        if(!*T)
            
            exit(0);
        
        (*T)->data = c;
        
        CreateBiThrTree(&(*T)->leftChild);
        
        if((*T)->leftChild)      // 如果有左孩子
            
            (*T)->leftTag = Link;
        
        CreateBiThrTree(&(*T)->rightChild);
        
        if((*T)->leftChild)      // 如果有右孩子
            
            (*T)->rightTag = Link;
    }
    
    return OK;
    
}


BiThrTree pre ; // 全局变量，始终指向刚刚访问过的节点
//  中序遍历进行中序线索化
void InThreading(BiThrTree p){
    
    if(p){
        
        InThreading(p->leftChild);
        
        if(!p->leftChild){       // 左子树为空，线索化二叉树
            
            p->leftTag = Thread; // 更改标志位
            
            p->leftChild = pre;  // 指向前驱
            
        }
        
        if(!pre->rightChild){
            
            pre->rightTag = Thread;  // 更改标志位
            
            pre->rightChild = p;     // 设置后继
        
        }
        
        pre = p;                     //  保持 pre 指向的是p的前驱 因为接下来线索化是 p 的右子树
    
        InThreading(p->rightChild);
        
    }

}

// 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点
Status InOrderThreading(BiThrTree * Thr, BiThrTree T){

    *Thr = (BiThrTree)malloc(sizeof(BiThrNode));
    
    if (!(*Thr))
        
        exit(0);
    
    (*Thr)->leftTag = Link;     // 头结点初始化
    
    (*Thr)->rightTag = Thread;
    
    (*Thr)->rightChild = (*Thr);
    
    if(!T)
        
        (*Thr)->leftChild = *Thr; //  空树
    
    else{
        
        (*Thr)->leftChild = T;     // 头结点的左子树域指向二叉树
        
        pre = (*Thr);
        
        InThreading(T);
        
        pre->rightChild = *Thr;   // 中序遍历的最后一个结点指向头结点
        
        pre->rightTag = Thread;
        
        (*Thr)->rightChild = pre; // 头节点的右子树域指向中序遍历后的最后一个结点
    }

    return OK;
}

// 中序遍历二叉线索树
// 寻找后继的过程，也就是寻找右子树的过程
Status InOrderTraverse_Thr(BiThrTree T){

    BiThrTree p;
    
    p = T->leftChild;
    
    while(p != T){
        
        while(p->leftTag == Link)
            
            p = p->leftChild;
        
        if(!(visit(p->data)))
            
            return ERROR;
        
        while(p->rightTag == Thread && p->rightChild != T){ // 这里都是有后继指针的结点
        
            p = p->rightChild;
            
            visit(p->data);
        
        }
        
        p = p->rightChild;  // 循环中断证明 p 结点有右子树，下一个结点应该是对这个右子树遍历的第一个结点
    }
    
    return OK;

}


int main(int argc, const char * argv[]) {
    
    BiThrTree H,T;
    
    printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
    
    CreateBiThrTree(&T); /* 按前序产生二叉树 */
    
    InOrderThreading(&H,T); /* 中序遍历,并中序线索化二叉树 */
    
    printf("中序遍历(输出)二叉线索树:\n");
    
    InOrderTraverse_Thr(H); /* 中序遍历(输出)二叉线索树 */
    
    printf("\n");
    
    return 0;
}
