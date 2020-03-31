#include <iostream>
class Lnode
{
private:
    friend class Link_list;
    friend class iostream;
    int a, b;
    Lnode *next;

public:
    Lnode();
    Lnode(int _a, int _b);
    void show();
};
void Lnode::show()
{
    std::cout << "(" << a << "," << b << ")"<<std::endl;
}

Lnode::Lnode()
{
    a = 0;
    b = 0;
    next = nullptr;
}
Lnode::Lnode(int _a, int _b)
{
    a = _a;
    b = _b;
    next = nullptr;
}

class Link_list
{
private:
    Lnode *l,*end;
    int len=0;

public:
    Link_list();
    ~Link_list();
    int insert_l(int a,int b); //直接传值，用参数初始化
    int insert_l(int i,int a,int b); //指定位置插入节点
    int find_l(int i,Lnode &c);      //寻找第i个元素
    int delete_l(int i);    //删除第i个元素
    void show();
};

Link_list::Link_list()
{
    l = new Lnode();
    end = l; //头节点和尾指针
}

Link_list ::~Link_list()
{
    for (Lnode *p = l; l->next != nullptr; p = l)
    {
        l = l->next;
        delete p;
    }
}
int Link_list::insert_l(int a,int b)
{
    Lnode *p= new Lnode(a, b);
    end->next = p;
    end = p;
    len++;
    return 1;
}
int Link_list::find_l(int i,Lnode &c)
{
    int j=0;
    Lnode *p;
    if(i>len||i<1)
        return 0;
    else
        {
            for (p = l; j != i;p=p->next,j++)
                ;
            c = *p;
        }
        return 1;
}
int Link_list::delete_l(int i)
{
    int j = 0;
    Lnode *p,*q;
    for (p = l; j < i-1;p=p->next,j++)
        ;
    q = p->next;
    p->next = p->next->next;
    delete q;

    return 1;
}
int Link_list::insert_l(int i,int a,int b)
{
    Lnode *p,*q;
    int j = 0;
    for (p = l; j < i - 1;p=p->next,j++)
        ;
    q = new Lnode(a, b);
    q->next = p->next;
    p->next = q;
    return 1;
}
void Link_list::show()
{
    Lnode *p;
    for (p = l; p->next != nullptr;p=p->next)
        std::cout << "(" << p->a << "," << p->b << ")";
    std::cout << "(" << p->a << "," << p->b << ")"<<std::endl;
}


int main()
{
    Link_list l;
    Lnode l1;
    l.insert_l(2, 2);
    l.insert_l(3, 2);
    l.insert_l(4, 2);
    l.insert_l(5, 2);
    l.insert_l(6, 2);
    l.insert_l(7, 2);
    l.show();
    l.delete_l(2);
    l.show();
    l.insert_l(4, 6, 6);
    l.show();
    l.find_l(4, l1);
    l1.show();

    return 0;
}


