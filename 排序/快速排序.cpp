#include <iostream>
#include <vector>
int part(std::vector<int> &a,int head,int tail)//先把第一个元素放入，a[0]中，然后尾指针开始向前直到找到
//第一个小于a[0]的位置，并赋值给头指针位置，然后头指针向后移动找到第一个大于a[0]的，赋值给尾指针，如此循环，直到
//头尾指针重合，然后把a[0]赋值给重合的地方，则头（尾）指针左边都小于它，右边都大于他，并返回重合的位置
{
    a[0] = a[head];
    while(head<tail)
    {
        while(tail>head&&a[tail]>=a[0])
            --tail;
        a[head] = a[tail];
        while(tail>head&&a[head]<=a[0])
            ++head;
        a[tail] = a[head];
    }
    a[head] = a[0];
    return head;
}
void Qsort(std::vector<int> &a,int head,int tail)//递归调用，每次分为左右两个小序列，并分别对两个小序列进行
//排序
{
    
    if(head<tail)
    {
        int pos = part(a, head,tail);
        Qsort(a, head, pos - 1);
        Qsort(a, pos + 1, tail);
    }
}


int main()
{
    using namespace std;
    vector<int> a{0, 11, 55, 44, 99, 77, 22, 66, 98, 65, 43, 32, 21};
    Qsort(a, 1, a.size() - 1);
    for (int i = 1; i < a.size(); ++i)
        cout
            << a[i] << " ";
}