#include <iostream>
const int max = 100;
class StackNode
{
private:
    int a; //数据

    friend class Stack;

public:
    StackNode(int b) : a(b){};
    StackNode():a(0){};
};

class Stack
{
private:
    StackNode *bottom, *top;
    int stack_size;

public:
    Stack();
    ~Stack();
    int is_empty();
    int len();
    int gettop();//获取顶端元素
    void clear();//清空栈
    int push(int data);
    int pop();
};

Stack::Stack()
{
    top = bottom = new StackNode[max];
    stack_size = 0;
}

Stack::~Stack()
{
    delete[] bottom;
	top=bottom=nullptr;
	stack_size=0;
}
int Stack::is_empty()
{
    if (top == bottom)
        return 1;
    else
        return 0;
}
int Stack::len()
{
    return stack_size;
}
int Stack::gettop()
{
    return (top-1)->a;//注意top指针指在顶端元素的上面，所以输出时输出top-1的位置
}
void Stack::clear()
{
    top = bottom;//虽然里面是脏数据，但是下次直接覆盖就好了
    stack_size = 0;
}
int Stack::push(int data)
{
    if (stack_size == max)
        return 0;
    else
    {
        top++->a = data;//先写入再自增，位于顶端元素上方
        stack_size++;
        std::cout << data << "has push in" << std::endl;
        return 1;
    }
}
int Stack::pop()
{
    if (this->is_empty())
    {
        std::cout << "stack is empty!" << std::endl;
        return 0;
    }
        
    else
    {
        std::cout << (--top)->a<<std::endl;//先自减再取值
        stack_size--;
        return 1;
    }
}


int main()
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    std::cout << stack.len()<<std::endl;
    std::cout << stack.gettop()<<std::endl;
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    std::cout << stack.len()<<std::endl;
    stack.push(1);
    stack.push(2);
    std::cout << stack.is_empty()<<std::endl;
    stack.clear();
    std::cout << stack.is_empty()<<std::endl;


    




    return 0;
}
