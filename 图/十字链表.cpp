#include <iostream>
#include<fstream>
#include <streambuf>
typedef char vex_type;
struct G_node
{
    int head, tail, info; //head--相同弧头发出的,tail--相同弧尾发出的,info权重
    G_node *h_link, *t_link;
    G_node() : head(0), tail(0), info(0), h_link(nullptr), t_link(nullptr){};
};
struct G_list
{
    vex_type data;
    G_node *in, *out; //in从节点进入,out从节点发出
    G_list() : data(0), in(nullptr), out(nullptr){};
};

class Graph
{
public:
    int vex_num, arc_num;
    G_list *vexs;
    Graph();
    ~Graph();
    int get_num(vex_type &v);
    vex_type get_name(int index);//通过数组下标返回节点的名称
    void insert(int head, int tail, int info);
    void create();
    void show();
};

Graph::Graph()
{

    std::cout << "请输入节点的个数和边的个数" << std::endl;
    std::cin >> vex_num >> arc_num;
    vexs = new G_list[vex_num];
    for (int i = 0; i < vex_num;++i)
    {
        std::cout << "请输入所有" << vex_num << "个节点的名称:";
        std::cin >> vexs[i].data;
    }
}

Graph::~Graph()
{
    delete[] vexs;
}

int Graph::get_num(vex_type &v)
{
    int i;
    for (i = 0; i < vex_num; ++i)
    {
        if (vexs[i].data == v)
            break;
    }
    return i;
}
vex_type Graph::get_name(int index)
{
    return vexs[index].data;
}
void Graph::insert(int head, int tail, int info) //给定下标，头插法
{
    G_node *p = new G_node();
    p->head = head;
    p->tail = tail;
    p->info = info;
    //头插进入出结点
    p->h_link = vexs[head].out;
    vexs[head].out = p;
    //头插进入入节点
    p->t_link = vexs[tail].in;
    vexs[tail].in = p;
    
}
void Graph::create()
{
    for (int i = 0; i < arc_num; ++i)
    {
        std::cout << "请输入两个节点名称及权重：" << std::endl;
        vex_type a, b;
        int weight;
        std::cin >> a >> b >> weight;
        a = get_num(a);
        b = get_num(b);
        insert(a, b, weight);
    }
}
void Graph::show()
{
    for (int i = 0; i < vex_num;++i)
    {
        std::cout << "第" << i + 1 << "个节点 出 边有：";
        for (G_node *p = vexs[i].out; p != nullptr;p=p->h_link)
        {
            std::cout << get_name(p->head) << "->" << get_name(p->tail)<<"  ";
        }
        std::cout << "\n";
        std::cout << "第" << i + 1 << "个节点 入 边有：";
        for (G_node *p = vexs[i].in; p != nullptr;p=p->t_link)
        {
            std::cout << get_name(p->head) << "->" << get_name(p->tail)<<"  ";
        }
        std::cout << "\n";

    }
        
}

int main()
{
    std::ifstream fin("十字链表测试.txt");//重定向输入为文件
    std::ofstream fout("十字链表测试__out.txt");//重定向输出
    std::streambuf *cin_backup = std::cin.rdbuf(fin.rdbuf());//cin.rdbuf(&)带参数返回原来的buffer,并备份
    std::streambuf *cout_backup = std::cout.rdbuf(fout.rdbuf());

    Graph g;
    g.create();
    g.show();

    std::cin.rdbuf(cin_backup);//不需要读取时，使用备份恢复cin cout到标准输入输出中
    std::cout.rdbuf(cout_backup);

    fin.close();
    fout.close();
}
