#include <iostream>
#include<fstream>
#include <streambuf>
#include<queue>
typedef char vex_type;
struct G_node
{
    int head, tail, info; //head--相同弧头发出的,tail--到达相同弧尾的,info权重
    G_node* h_link, * t_link;//由h_link连起来的链表弧头相同，t_link连起来的链表到达相同的弧尾
    G_node() : head(0), tail(0), info(0), h_link(nullptr), t_link(nullptr) {};
};
struct G_list
{
    vex_type data;
    G_node* in, * out; //in从节点进入,out从节点发出
    G_list() : data(0), in(nullptr), out(nullptr) {};
};

class Graph
{
public:
    int vex_num, arc_num, * visited;//visited数组用于判断节点是否被访问过
    std::queue<G_list> q;
    G_list* vexs;
    Graph();
    ~Graph();
    int get_num(vex_type& v);//通过名称返回下标
    vex_type get_name(int index);//通过数组下标返回节点的名称
    void insert(int head, int tail, int info);
    void create();
    void show();
    void dfs(int index = 0);
    void bfs(int index = 0);
    void clean_visited() { for (int i = 0; i < vex_num; ++i) visited[i] = 0; };//清空visited数组
};

Graph::Graph()
{

    std::cout << "请输入节点的个数和边的个数" << std::endl;
    std::cin >> vex_num >> arc_num;
    vexs = new G_list[vex_num];

    for (int i = 0; i < vex_num; ++i)
    {
        std::cout << "请输入所有" << vex_num << "个节点的名称:";
        std::cin >> vexs[i].data;
    }
    visited = new int[vex_num];
    for (int i = 0; i < vex_num; ++i)
        visited[i] = 0;
}

Graph::~Graph()
{
    delete[] vexs;
}

int Graph::get_num(vex_type& v)
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
    G_node* p = new G_node();
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
    for (int i = 0; i < vex_num; ++i)
    {
        std::cout << "第" << i + 1 << "个节点 出 边有：";
        for (G_node* p = vexs[i].out; p != nullptr; p = p->h_link)
        {
            std::cout << get_name(p->head) << "->" << get_name(p->tail) << "  ";
        }
        std::cout << "\n";
        std::cout << "第" << i + 1 << "个节点 入 边有：";
        for (G_node* p = vexs[i].in; p != nullptr; p = p->t_link)
        {
            std::cout << get_name(p->head) << "->" << get_name(p->tail) << "  ";
        }
        std::cout << "\n";

    }

}
void Graph::dfs(int index)//因为十字链表有方向，所以只需要一直使用h_link，就能遍历和一个节点相连的所有节点
{
    std::cout << get_name(index) << std::endl;
    visited[index] = 1;
    G_node* p = vexs[index].out;
    while (p)
    {
        int index1 =p->tail;//对和每个节点相连的第一个节点递归使用dfs
        if (!visited[index1])
            dfs(index1);
        p = p->h_link;//回溯到和该节点相邻的其他节点
    }
}

void Graph::bfs(int index)
{
    if (!visited[index])
    {
        visited[index] = 1;
        q.push(vexs[index]);
        while (!q.empty())
        {
            G_node* tmp = q.front().out;//指向队首元素
            int num = get_num(q.front().data);//获取节点在数组中的下标
            std::cout << q.front().data << std::endl;
            while (tmp)
            {
                int index1 = tmp->tail;
                if (!visited[index1])//若没有访问过，把所有和该节点相邻的节点入队
                {
                    q.push(vexs[index1]);
                    visited[index1] = 1;
                }

                tmp =tmp->h_link;

            }
            q.pop();

        }
    }

}


int main()
{
	//这里使用了C++的cin/cout重定向，直接读取文件并输出到文件，如果你不想使用，将下面的部分和结尾部分注释即可


    std::ifstream fin("十字链表测试.txt");//重定向输入为文件
    std::ofstream fout("十字链表测试__out.txt");//重定向输出
    std::streambuf* cin_backup = std::cin.rdbuf(fin.rdbuf());//cin.rdbuf(&)带参数返回原来的buffer,并备份
    std::streambuf* cout_backup = std::cout.rdbuf(fout.rdbuf());


	//主程序
    Graph g;
    g.create();
    std::cout << "--------------------------初始视图--------------------" << std::endl;
    g.show();


    std::cout << "--------------------------bfs--------------------" << std::endl;
    g.clean_visited();
    g.bfs();

    std::cout << "--------------------------dfs--------------------" << std::endl;

    g.clean_visited();
    g.dfs();

	//主程序


	//恢复重定向
    std::cin.rdbuf(cin_backup);//不需要读取时，使用备份恢复cin cout到标准输入输出中
    std::cout.rdbuf(cout_backup);
	//关闭文件读写
    fin.close();
    fout.close();
}
