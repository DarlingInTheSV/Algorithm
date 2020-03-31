#include<iostream>
const int max = 100;
class TreeNode  //二叉树节点
{
private:
    char data;
    TreeNode* l_child, * r_child;//左右节点
    friend class Btree;

public:
    TreeNode();
    TreeNode(char _data);
    ~TreeNode();

};

TreeNode::TreeNode()
{
    data = 0;
    r_child = l_child = nullptr;
}
TreeNode::TreeNode(char _data)
{
    data = _data;
    r_child = l_child = nullptr;
}

TreeNode::~TreeNode()
{
}
class queue
{
private:
    TreeNode** p;//这里队列里面放指针，所以头指针是指向指针的指针
    int front, rear;

public:
    queue();
    ~queue();
    int enqueue(TreeNode* p);
    TreeNode* dequeue();
    int get_len();
};

queue::queue()
{
    p = new TreeNode * [max]; //p指向指针数组首元素
    front = rear = 0;//这里没有直接使用指针，而是使用给p指针加减整数表示指针
}

queue::~queue()
{
    delete[]p;
}

int queue::enqueue(TreeNode* q)
{
    if ((rear + 1) % max == front) //少使用一个空间位置，用于区别队列为空和为满时头指针和尾指针重合无法分别的情况
    {                       //所以如果尾指针下一个位置是头指针的话，就不再填充那一个空的
        std::cout << "队列已满" << std::endl;
        return 0;
    }
    else
    {
        p[rear] = q;
        rear = (rear + 1) % max;
        return 1;
    }

}
TreeNode* queue::dequeue()
{
    if (front == rear)
        return 0;
    else
    {
        TreeNode* tmp = p[front];//返回指针数组的值
        front = (front + 1) % max;
        return tmp;
    }
}
int queue::get_len()
{
    return (rear - front + max) % max;/*当尾指针的位置低于头指针时，先加上队列大小，表示绝对高度，
                                        再与头指针相减，最后取模，表示循环队列，求得队列中的个数*/
}

class Btree
{
private:
    TreeNode* r;

public:
    Btree();
    int create1(const char* &s, TreeNode* &p);
    /*这个是递归函数，因为首次使用需要根节点，但C++不能用成员变量作为函数参数的默认值，而且要修改左右节点的话
    必须使用引用，还有我使用输入的字符串初始化节点的值，在每次读完一个后必须使得指针前进一个位置，也必须使用引用
    如果不用的话，每次递归读进去的s都是一个拷贝，也就是每次都从开头读其。而且不能对输入的原始字符串修改，所以我
    多用了一个函数create2(),他来接受用户输入，并产生一个拷贝，用于create1修改，并且赋给第一次初值r(根节点指针)*/   
    int create2(const char* s);
    int search();
    ~Btree();
};
Btree::Btree()
{
    r = nullptr;
}

int Btree::create1(const char* &s, TreeNode* &p)
{
   
    if (*s != '#')
    {
        p = new TreeNode(*s);
        create1(++s, p->l_child);
        create1(++s, p->r_child);
    }
    else
    {
        p = nullptr;
        return 0;
    }
    
    return 1;
}
int Btree::create2(const char* s)
{
    Btree::create1(s, r);
    return 1;
}

Btree::~Btree()
{
}
int Btree::search()//输出每一层的各个节点（从左到右），使用队列完成，每找到一个节点，把他不为空的左右子节点入队
{
    queue queue;
    queue.enqueue(r);
    while(queue.get_len())
    {
        TreeNode* tmp = queue.dequeue();
        std::cout << tmp->data << std::endl;
        if (tmp->l_child)
            queue.enqueue(tmp->l_child);
        if (tmp->r_child)
            queue.enqueue(tmp->r_child);

    }
    return 1;

}

int main()
{
    const char* s = "ABC##DE#G##F###";
    Btree btree;
    btree.create2(s);
    btree.search();
}

