#include<iostream>
const int max = 100;
class data
{

public:
    int n = 0;

};

class queue
{
private:
    data *p;
    int front, rear;

public:
    queue();
    ~queue();
    int get_len();
    int enqueue(int a);
    int dequeue();
    void get_head();
};

queue::queue()
{
    p = new data[100];
    front = rear = 0;//这里没有直接使用指针，而是使用给p指针加减整数表示指针
}

queue::~queue()
{
    delete []p;
}
int queue::get_len()
{
    return (rear - front + max) % max;/*当尾指针的位置低于头指针时，先加上队列大小，表示绝对高度，
                                        再与头指针相减，最后取模，表示循环队列，求得队列中的个数*/
}
int queue::enqueue(int a)
{
    if((rear+1)%max==front) //少使用一个空间位置，用于区别队列为空和为满时头指针和尾指针重合无法分别的情况
    {                       //所以如果尾指针下一个位置是头指针的话，就不再填充那一个空的
        std::cout << "队列已满" << std::endl;
        return 0;
    }
    else
    {
        p[rear].n = a;
        rear = (rear + 1) % max;
        return 1;
    }
        
}
int queue::dequeue()
{
    if(front==rear)
        return 0;
    else
    {
        std::cout << p[front].n << std::endl;
        front = (front + 1) % max;
        return 1;
    }
}
void queue::get_head()
{
    std::cout << p[front].n << std::endl;
}

int main()
{
    queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    std::cout << q.get_len() << std::endl;
    q.get_head();
    q.dequeue();
    q.dequeue();
    std::cout << q.get_len() << std::endl;
    q.dequeue();


}