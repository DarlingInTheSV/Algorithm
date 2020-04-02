#include<iostream>
#include<vector>
int get_radix(std::vector<int> &p)//先获得所有数中最大数的位数
{
    int max = p[0];
    for (int i = 1; i < p.size();++i)
    {
        if(p[i]>max)
            max = p[i];
    }
    int count;
    for (count = 0; max != 0;max/=10,++count)
        ;
    return count;
}
void radix_sort(std::vector<int> &p)//基数排序，每次循环按某一位的大小进行排序
{
    
    std::vector<int> tmp(p.size());
    int time = get_radix(p);
    int radix = 1;
    for (int k = 0; k < time;++k)
    {
        int count[10]={0};
        for (int i = 0; i < p.size();++i)//统计该位上0-9数字出现的次数，并计入count数组
            ++count[(p[i] / radix) % 10];
        for (int i = 1; i < 10;++i)//将出现次数转化为数组下标，比如0出现1次，1出现3次，则这一位为1的从数组
        //下标为3+1=4，然后再-1(从0开始)，则从3开始，每次-1，最后tmp[3]tmp[2]tmp[1]存放结尾为1的数字，tmp[0]
        //存放尾数为0的数字
            count[i] += count[i - 1];
        for (int i = p.size()-1; i>=0;--i)
        {
            int num = (p[i] / radix) % 10;
            tmp[count[num]-1] = p[i];
            --count[num];
        }
         for (int i = 0; i < p.size();++i)
             p[i] = tmp[i];
        radix *= 10;
    }
}

int main()
{
    using namespace std;
    vector<int> a{0, 11, 55, 44, 99, 77, 22, 66, 98, 65, 43, 32, 21};
    radix_sort(a);
    for (int i = 0; i < a.size(); ++i)
        cout
            << a[i] << " ";

    return 0;
}