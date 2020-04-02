#include <iostream>
#include <vector>
void SelectSort(std::vector<int> &array)//插入排序，每次和前一个比较直到找到不小于arrary[0]的元素
{
    int j;
    for (int i = 2; i < array.size(); ++i)//arrary[0]中存放的是哨兵，省去了每次比较i是否小于0
    {
        if (array[i] < array[i - 1])
        {
            array[0] = array[i];
            for (j = i - 1; array[j] > array[0]; --j)
                array[j + 1] = array[j];
            array[j + 1] = array[0];
        }
    }
}

void SelectSortWithBinary(std::vector<int> &array)//上面的改进版，使用二分法进行搜索
{
    for (int i = 2; i < array.size(); ++i)
    {
        if (array[i] < array[i - 1])
        {
            array[0] = array[i];
            int head = 1, tail = i - 1;
            while (head <= tail)
            {
                int mid = (head + tail) / 2;
                if (array[0] < array[mid])
                {
                    tail = mid - 1;
                }
                else
                {
                    head = mid + 1;
                }
            }//结束循环后头指针的位置是存放要找的位置（第一个大于哨兵的数）
            for (int j = i - 1; j >= head; --j)//把头指针之前的每个元素的值赋值给前一个，最后把哨兵赋值给它
            {
                array[j + 1] = array[j];
            }
            array[head] = array[0];
        }
    }
}

void ShellSort(std::vector<int> &array, std::vector<int> &steps)//希尔排序要求一个递增序列，每次将整个
//序列分为steps[step]个，每次把元素1,1+steps[step],1+2*steps[step]...看作一组进行排序，而序列本身要越来越小
//最后为1的时候就是对每个元素进行排序（选择排序），在过程中序列逐步有序，递增序列一般使用 2^k-1,例如10个元素{7，3,1}
{
    int j;
    for (int step = 0; step < steps.size(); ++step)
    {
        int factor = steps[step];
        for (int i = factor + 1; i < array.size(); i += factor)
        {
            if (array[i] < array[i - factor])
            {
                array[0] = array[i];
                for (j = i - factor; array[0] < array[j]; j -= factor)
                    array[j + factor] = array[j];
                array[j + factor] = array[0];
            }
        }
    }
}

int main()
{
    using namespace std;
    vector<int> a{0, 11, 55, 44, 99, 77, 22, 66, 98, 65, 43, 32, 21};
    vector<int> shell{7, 3, 1};
    SelectSort(a);
        for (int i = 1; i < a.size(); ++i)
        cout
            << a[i] << " ";
    SelectSortWithBinary(a);
        for (int i = 1; i < a.size(); ++i)
        cout
            << a[i] << " ";
    ShellSort(a, shell);
    for (int i = 1; i < a.size(); ++i)
        cout
            << a[i] << " ";
}