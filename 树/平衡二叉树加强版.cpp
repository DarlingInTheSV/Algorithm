#include <algorithm>
#include <iostream>
#include<cstdlib>
#include <stdlib.h>
class AVL_Node
{
private:
    int data, height;
    AVL_Node *l_child, *r_child;
    friend class AVL_tree;

public:
    AVL_Node();
    ~AVL_Node();
};

AVL_Node::AVL_Node()
{
    data = 0;
    height = 1;
    l_child = nullptr;
    r_child = nullptr;
}

AVL_Node::~AVL_Node()
{

}

class AVL_tree
{
private:
public:
    AVL_Node *root;
    AVL_tree();
    ~AVL_tree();
    int update_height(AVL_Node *&p);//更新节点高度，左右子树中最大高度+1
    int get_height(AVL_Node *p);//获取高度，如果是空返回0，这个函数主要就是为了null时返回0不使程序出错
    int insert(int a, AVL_Node *&p);
    int l_rotate(AVL_Node *&p);//左旋
    int r_rotate(AVL_Node *&p);//右旋
    int get_balance_factor(AVL_Node *&p);//计算平衡因子，通过左右儿子的高度差+1表示
    int delete_node(int a,AVL_Node *&p);//删除指定值的节点
    int search(int a, AVL_Node *p);
    int traverse(AVL_Node *&p);
    int get_min(AVL_Node *p);
    int get_max(AVL_Node *p);
    int destory(AVL_Node *&p);
};

AVL_tree::AVL_tree()
{
    root = new AVL_Node;
}

AVL_tree::~AVL_tree()
{
}
int AVL_tree::get_height(AVL_Node *p)//有效防止访问null指针的成员
{
    if (!p)
        return 0;
    else
        return p->height;
}
int AVL_tree::update_height(AVL_Node *&p)
{
    if (p)
        return 0;
    else
        return std::max(get_height(p->l_child), get_height(p->r_child)) + 1;
}
int AVL_tree::l_rotate(AVL_Node *&p)
{
    AVL_Node *right = p->r_child;
    p->r_child = right->l_child;
    right->l_child = p;
    update_height(right);
    update_height(p);
    p = right;
    return 1;
}
int AVL_tree::r_rotate(AVL_Node *&p)
{
    AVL_Node *left = p->l_child;
    p->l_child = left->r_child;
    update_height(p);
    update_height(left);
    p = left;
    return 1;
}
int AVL_tree::get_balance_factor(AVL_Node *&p)
{
    return (get_height(p->l_child)-get_height(p->r_child));
}
int AVL_tree::get_max(AVL_Node *p)//最大值，一直向右
{
    while(p->r_child)
        p = p->r_child;
    return p->data;
}
int AVL_tree::get_min(AVL_Node *p)
{
    while(p->l_child)
        p = p->l_child;
    return p->data;
}
int AVL_tree::insert(int a, AVL_Node *&p)
{
    if (!p)//空指针，叶子节点
    {
        p = new AVL_Node;
        p->data = a;
        return 1;
    }
    else
    {
        if (a < p->data)//左子树
        {
            insert(a, p->l_child);
            update_height(p);
            if (get_balance_factor(p) == 2) //不平衡
            {
                if (get_balance_factor(p->l_child) == 1) //LL型
                    r_rotate(p);
                else //LR型
                {
                    l_rotate(p->l_child);//左旋左子树，右旋根节点
                    r_rotate(p);
                }
            }
        }
        else
        {
            insert(a, p->r_child);
            update_height(p);
            if (get_balance_factor(p) == -2) //不平衡
            {
                if (get_balance_factor(p->r_child) == -1) //RR型
                    l_rotate(p);
                else //RL型
                {
                    r_rotate(p->r_child);//右旋右子树，左旋根节点
                    l_rotate(p);
                }
            }
        }
    }
    return 1;
}
int AVL_tree::traverse(AVL_Node *&p)
{
    if (!p)
    {
        
        return 0;

    }
        
    else
    {
        traverse(p->l_child);
        std::cout << p->data <<"  ";
        traverse(p->r_child);
        return 1;
    }
}
int AVL_tree::search(int a, AVL_Node *p)
{
    if (!p)
    {
        std::cout << "\n未查找到指定数据:" <<a<< std::endl;
        return 0;
    }
    else
    {
        if(a<p->data)
            search(a,p->l_child);
        else if (a>p->data)
            search(a, p->r_child);
        else
            std::cout << "找到指定数据:" << a<<std::endl;
    }
    return 1;
}
int AVL_tree::delete_node(int a,AVL_Node *&p)
{
    if(!p)
    {
        std::cout << "\n未查询到要删除的节点:" <<a<< std::endl;
        return 0;
    }
        
    else if(p->data==a)//找到要删除的节点
    {
        if((!p->l_child)&&(!p->r_child))//两个子树都不空
        {
            if(get_height(p->l_child)>get_height(p->r_child))//选择高度更高的子树来选择要删除的元素
            {
                p->data = get_max(p->l_child);//左子树最大值替换要删除的节点
                delete_node( p->data,p->l_child);//最后删除对应的节点
            }
            else
            {
                p->data = get_min(p->r_child);//右子树最小值替换要删除的节点
                delete_node( p->data,p->r_child);
            }
        }
        else//两子树不都空，直接删除
        {
            AVL_Node *tmp = p;
            p = p->l_child ? p->l_child : p->r_child;
            delete tmp;
        }
    }
    else if(a<p->data)//查找值小于节点值，继续递归
    {
        delete_node(a, p->l_child);
        if (get_balance_factor(p) == -2) //不平衡
            {
                if (get_balance_factor(p->l_child) == -1) //RR型
                    l_rotate(p);
                else //RL型
                {
                    r_rotate(p->l_child);
                    l_rotate(p);
                }
            }
        else
            update_height(p);
    }
    else
    {
      delete_node(a, p->r_child);
        if (get_balance_factor(p) == 2) //不平衡
            {
                if (get_balance_factor(p->l_child) == 1) //LL型
                    r_rotate(p);
                else //LR型
                {
                    l_rotate(p->l_child);
                    r_rotate(p);
                }
            }
        else //平衡
            update_height(p);  
    }
    return 1;
}

int AVL_tree::destory(AVL_Node * &p)
{
    if(p)
    {
        destory(p->l_child);
        destory(p->r_child);
        delete p;
        p = nullptr;
        return 1;
    }
    else
        return 0;
}

int main()
{
    AVL_tree t;
    t.insert(1, t.root);
    t.insert(12, t.root);
    t.insert(52, t.root);
    t.insert(17, t.root);
    t.insert(21, t.root);
    t.insert(8, t.root);
    t.insert(52, t.root);
    t.insert(33, t.root);
    t.insert(75, t.root);

    t.traverse(t.root);
    t.search(2,t.root);
    t.search(12,t.root);
    t.search(52,t.root);
    std::cout << "删除节点：17" << std::endl;
    t.delete_node(17, t.root);
    t.traverse(t.root);
    t.delete_node(100, t.root);
    t.traverse(t.root);

    std::cout << "\n销毁平衡二叉树：" << std::endl;
    t.destory(t.root);
    t.traverse(t.root);



//生成随机数排序
    // for (int i = 0; i < 100;i++)
    // {
    //     t.insert(rand()%1000, t.root);
    // }
    // t.traverse(t.root);


}
