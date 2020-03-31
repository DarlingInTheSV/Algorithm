#include<iostream>
#include<stdio.h>
#include<queue>
typedef char ElemType;
typedef struct BNode
{
    ElemType data;
    struct BNode *lchild, *rchild;
} BtNode;

class Btree
{    
public:
    BNode *root;
    Btree();
    ~Btree();
    int create(BtNode *&p);
    int PreOrderTraverse(BtNode *&p);//先序遍历
    int InOrderTraverse(BtNode *&p);//中序遍历
    int PostOrderTraverse(BtNode *&p); //后序遍历
    int LevelOrderTraverse(BtNode *&p);//层次遍历（广度优先遍历）
};
    Btree::Btree()
    {
        root = NULL;
}

Btree::~Btree()
{
}
int Btree::create(BtNode *&p)
{
    std::cout << "请输入数据,输入#结束" << std::endl;
    ElemType c;
    std::cin >> c;
    std::cin.get();//
    if(c=='#')
    {
        p = NULL;
        return 0;
    }
    else
    {
        p = new BtNode;
        p->data = c;
        create(p->lchild);
        create(p->rchild);
        
    }
    return 1;
        
    

}
int Btree::PreOrderTraverse(BtNode *&p)//先序遍历
{
    std::cout << "PreOrderTraverse!" << std::endl;

    if(p)
    {
        std::cout << p->data << std::endl;
        PreOrderTraverse(p->lchild);
        PreOrderTraverse(p->rchild);


    }
    return 1;

}

int Btree::InOrderTraverse(BtNode *&p)//中序遍历
{
    std::cout << "InOrderTraverse!" << std::endl;

    if(p)
    {
        PreOrderTraverse(p->lchild);
        std::cout << p->data << std::endl;
        PreOrderTraverse(p->rchild);


    }
    return 1;

}
    
int Btree::PostOrderTraverse(BtNode *&p)//后序遍历
{
    std::cout << "PostOrderTraverse!" << std::endl;

     if(p)
    {
        PreOrderTraverse(p->lchild);
        
        PreOrderTraverse(p->rchild);
        std::cout << p->data << std::endl;


    }
    return 1;
}
    
int Btree::LevelOrderTraverse(BtNode *&p)//层次遍历（广度优先遍历）
{
    std::cout << "LevelOrderTraverse!" << std::endl;
    std::queue<BtNode *> q;
    BtNode *tmp;
    q.push(p);
    while(!q.empty())
    {
        tmp = q.front();
        std::cout << tmp->data << std::endl;
        if(tmp->lchild)
            q.push(tmp->lchild);
        if(tmp->rchild)
            q.push(tmp->rchild);
        q.pop();
    }
    return 1;
} 

int main()
{
    Btree btree;
    btree.create(btree.root);
    btree.PreOrderTraverse(btree.root);
    btree.InOrderTraverse(btree.root);
    btree.PreOrderTraverse(btree.root);
    btree.LevelOrderTraverse(btree.root);
}