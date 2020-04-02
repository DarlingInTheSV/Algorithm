#include<iostream>
#include<vector>

void Merge(std::vector<int> &p,int head,int tail,int mid)//归并排序，先不断地进行二分，直到只有两个元素
{
    int i=head,j=mid+1;
    std::vector<int> tmp;
    while(i <= mid && j <= tail)
    {
        if(p[i]<p[j])//从左右子列中找出小的放入数组中
        {
            tmp.push_back(p[i]);
            ++i;
        }
        else
        {
            tmp.push_back(p[j]);
            ++j;
        }
    }
    if(i>mid)//把还有剩余的数组直接全部放入
    {
        while(j<=tail)
        {
            tmp.push_back(p[j]);
            ++j;
        }
            
    }
    else
    {
        while(i<=mid)
        {
            tmp.push_back(p[i]);
            ++i;
        }
            
    }
    for(int i:tmp)//合并成的有序序列，复制到原数组中
        p[head++] = i;
}

void MergeSort(std::vector<int> &p,int head,int tail)//归并排序，先不断地进行二分，直到只有一个元素
{
{
    if(head<tail)
    {
        int mid = (head + tail) / 2;
        MergeSort(p, head, mid);//递归对左子列进行切分
        MergeSort(p, mid + 1, tail);//递归对右子列进行切分
        Merge(p, head, tail,mid);//然后从不断把两个有序序列进行合并
    }
}

int main()
{
    using namespace std;
    vector<int> a{0, 11, 55, 44, 99, 77, 22, 66, 98, 65, 43, 32, 21};
    MergeSort(a, 0, a.size()-1);
        for (int i = 0; i < a.size(); ++i)
        cout
            << a[i] << " ";

        return 0;
}