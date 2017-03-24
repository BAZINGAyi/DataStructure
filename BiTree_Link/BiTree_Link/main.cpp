#include <iostream>

using namespace std;

#define OK 1

#define ERROR 0

#define TRUE 1

#define FALSE 0

#define MAXSIZE 100

typedef int Status;

typedef char TElemType;

TElemType Nil = ' ';    //  字符型以空格为空

typedef struct BiNode{
    
    TElemType data ;
    
    struct BiNode * leftchild, *rightchild;
    
}BiNode, *BiTree;

// 提供树结点相关
int indexChar = 1;

typedef char MyString[24]; // 0 位置存放串的长度

MyString str;

Status setStringAssign(MyString T, const char *chars){
    
    int i;
    
    if(strlen(chars) > MAXSIZE)
        
        return ERROR;
    
    else{
        
        T[0] = strlen(chars);
        
        for (i = 1; i<=T[0]; i++)
            
            T[i] = *(chars + i - 1);
        
        return OK;
    }

}

// 构造空二叉树T
Status initBiTree(BiTree *T){  // 二级指针的使用
    
    *T = NULL;
    
    return OK;
}

#define DestoryBiTree ClearBiTree
// 若二叉树存在 销毁二叉树T
void DestoryBiTree(BiTree * T){
    
    if(*T){
        
        if((*T)->leftchild)
            
            DestoryBiTree(&(*T)->leftchild);
        
        if((*T)->rightchild)
            
            DestoryBiTree(&(*T)->rightchild);
        
        free(*T);
        
        *T = NULL;
            
    }
}

// 按照前序输入二叉树中节点的值(一个字符)
// #表示空树，构造二叉链表表示二叉树T。
void CreateBiTree(BiTree *T){
    
    TElemType ch;
    
    ch = str[indexChar++];
    
    if(ch == '#')
        
        (*T) = NULL;
    
    else{
        
        *T = (BiTree)malloc(sizeof(BiNode));
        
        if (!(*T))
            
            exit(0);
        
        (*T)->data = ch;
        
        CreateBiTree(&(*T)->leftchild);
        
        CreateBiTree(&(*T)->rightchild);
    
    }
    
}

Status BiTreeEmpty(BiTree T){
    
    if(T)
        
        return FALSE;
    
    else
        
        return TRUE;
}


Status BiTreeDepth(BiTree T){

    if(T == NULL)
        
        return 0;
    
    int leftDepth, rightDepth;
    
    if(T->leftchild)
        
        leftDepth = 1 + BiTreeDepth(T->leftchild);
    
    else
        
        leftDepth = 0;
    
    if(T->rightchild)
        
        rightDepth = 1 + BiTreeDepth(T->rightchild);
    
    else
        
        rightDepth = 0;

    return rightDepth > leftDepth ? rightDepth : leftDepth;
    
}

TElemType Root(BiTree T){
    
    if(BiTreeEmpty(T))
        
        return Nil;
    
    else
        
        return T->data;
    
}

TElemType Value(BiTree p){
    
    if(p != NULL)
    
        return p->data;
    
    return Nil;
}

// 给指针 p 指向的节点赋值
void Assign(BiTree p, TElemType value){

    if(p != NULL)
        
        p->data = value;

}

void PreOrderTraverse(BiTree T){

    if(BiTreeEmpty(T))
        
        return;

    cout<<T->data<<" ";
    
    PreOrderTraverse(T->leftchild);
    
    PreOrderTraverse(T->rightchild);

}

void PostOrderTraverse(BiTree T){
    
    if(BiTreeEmpty(T))
        
        return;
    
    PostOrderTraverse(T->leftchild);
    
    PostOrderTraverse(T->rightchild);
    
    cout<<T->data<<" ";
    
}

void InOrderTraverse(BiTree T){
    
    if(BiTreeEmpty(T))
        
        return;
    
    InOrderTraverse(T->leftchild);
    
    cout<<T->data<<" ";
    
    InOrderTraverse(T->rightchild);
    
}


int main(int argc, const char * argv[]) {
    
    BiTree T;
    
    TElemType e1;
    
    initBiTree(&T);
    
    setStringAssign(str,"ABDH#K###E##CFI###G#J##");
    
    CreateBiTree(&T);
    
    cout<<"构造空二叉树后,树空否？(1:是 0:否)"<<BiTreeEmpty(T)<<" 树的深度=\n"<<BiTreeDepth(T)<<endl;
    
    e1 = Root(T);
    
    cout<<"二叉树的根为: "<<e1<<endl;
    
    cout<<"\n前序遍历二叉树:";
    
    PreOrderTraverse(T);
    
    cout<<"\n中序遍历二叉树:";
    
    InOrderTraverse(T);
   
    cout<<"\n后序遍历二叉树:";
    
    PostOrderTraverse(T);
    
    ClearBiTree(&T);
    
    cout<<"\n清空二叉树后,树空否？(1:是 0:否)"<<BiTreeEmpty(T)<<" 树的深度=\n"<<BiTreeDepth(T)<<endl;
    
    return 0;
}
