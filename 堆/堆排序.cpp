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
void Heap::swap(int a, int b)
{
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}
void Heap::HeapAdjust(int s, int f)
{
    int l_child = s * 2 + 1, r_child = s * 2 + 2, max = s;
    if (l_child<f && data[l_child]>data[s])
        max = l_child;
    if (r_child<f && data[r_child]>data[max])
        max = r_child;
    if (max != s)
    {
        swap(max, s);
        HeapAdjust(max, f);
    }
}
void Heap::HeapCreate()
{
    for (int i = len / 2-1; i >= 0; --i)
    {
        HeapAdjust(i, len);
    }
}
void Heap::HeapSort()
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
