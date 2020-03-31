#include<iostream>
#define ElemType int 
typedef struct QueueNode
{
    struct QueueNode *next;
    ElemType data;
} QNode;

class LinkQueue
{
private:
    QNode *head, *tail;

public:
    LinkQueue();
    ~LinkQueue();
    int enqueue(ElemType a);
    ElemType dequeue();
};

LinkQueue::LinkQueue()
{
    head = new QNode;
    if(!head)
        std::cout << "new error!"<<std::endl;
    head->next = NULL;
    head->data = NULL;
    tail = head;
}

LinkQueue::~LinkQueue()
{
    for (QNode *p = head; head != tail;delete p)
    {
        p = head;
        head = head->next;  
    }
    delete head;
    head = tail = NULL;
}
int LinkQueue::enqueue(ElemType a)
{
    QNode *p = new QNode;
    if(!p)
        return 0;
    p->data = a;
    p->next = NULL;
    tail->next = p;
    tail = p;
        std::cout << a<<"enqueue!" << std::endl;

    return 1;
}

ElemType LinkQueue::dequeue()
{
    if(head==tail)
    {
        std::cout << "queue is empty!" << std::endl;
        return NULL;
    }
        
    QNode *p = head->next;
    ElemType tmp = p->data;
    head->next = p->next;
    delete p;
    if(!p->next)
        tail = head;
        std::cout <<tmp<< "dequeue!" << std::endl;

    return tmp;
}
int main()
{
    ElemType a;
    LinkQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();


}
