#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
class Heap
{
private:
    vector<int> data;
    int len;

public:
    Heap() {};
    Heap(vector<int> a);
    ~Heap() {};
    void HeapAdjust(int s, int f);
    void HeapCreate();
    void HeapSort();
    void show();
    void swap(int a, int b);
};
Heap::Heap(vector<int> a)
{
    data = a;
    len = a.size();
}
void Heap::swap(int a, int b)//这里不能使用algorithm中的swap需要自己写
{
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}
void Heap::HeapAdjust(int s, int f)//向下调整堆，因为数组从0开始，所以下标为s的元素左右儿子下标分别为 s * 2 + 1, s * 2 + 2
{
    int l_child = s * 2 + 1, r_child = s * 2 + 2, max = s;
    if (l_child<f && data[l_child]>data[s])//因为是最大堆，从三者中选出最大的，和s节点交换，并递归调整与其交换的节点
        max = l_child;
    if (r_child<f && data[r_child]>data[max])//这里的f是数组长度，所以数组最大索引是f-1,所以这里不使用=号
        max = r_child;
    if (max != s)
    {
        swap(max, s);
        HeapAdjust(max, f);
    }
}
void Heap::HeapCreate()
{
    for (int i = len / 2-1; i >= 0; --i)//创建一个堆，就是从第一个非叶子节点len / 2-1开始向上到根节点一个个调整
    {
        HeapAdjust(i, len);
    }
}
void Heap::HeapSort()//因为现在已经是最大堆，直接把堆顶元素和数组最后一个元素互换位置，然后调整0到len-1的元素，每次在调整的末尾多一个有序元素，直到根节点时所有元素有序，同理这里len-1是不到达的
{
    for (int j = len - 1; j > 0; --j)
    {
        swap(0, j);
        HeapAdjust(0, j);
    }


}
void Heap::show()
{
    for (auto i : data)
    {
        cout << i << " ";
    }
}

int main()
{
    vector<int> a;
    srand(time(0));
     for (int i = 0; i < 20;++i)
     {
         a.push_back(rand() % 100);
     }
    
    Heap heap(a);
    heap.HeapCreate();
    heap.HeapSort();
    heap.show();
}
