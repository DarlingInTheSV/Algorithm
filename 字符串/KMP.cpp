#include<iostream>
#include<cstring>
int * get_next(char T[],int lenth)//获取next数组
{
    int j = 0;
    int *next = new int[lenth];
    next[0] = 0;//首位置0
    for (int i = 1; i < lenth;)//j从0开始，i从1开始，如果两个相等，next[i]位置等于j+1的值，然后i,j分别加1
    {
        if(T[i]==T[j])
        {
            next[i] = ++j;
            i++;
        }
        else //否则的话，不匹配，则j的值为前一个值对应的next数组的值（既最大匹配的前后缀的长度（也是最大匹配下一个的下标））
        {
            if(j!=0)
                j = next[j-1];
            else
                next[i++] = 0;
        }
    }
    return next;
}
int KMS(char T[],char S[],int next[],int t_lenth,int s_lenth) //KMS算法
{
    int i = 0, j = 0;
    while(i<s_lenth&&j<t_lenth) //i指向要匹配的字符，j指向模板
    {
        if(T[j]==S[i])  //如果匹配就自增1
        {
            j++;
            i++;
        }
        else //不匹配的话从next数组中找出j-1对应的值，并付给j，j从新的位置开始，而i不动
        {
            if(j!=0)
                j = next[j - 1];
            else
                i++;
        }
    }
    if(j==t_lenth) //如果匹配结束后正好匹配了模板的所有，则匹配成功，否则失败
        return i-t_lenth;
    else
        return 0;
}

int main()
{
    char S[] = "abcdacbcdbcaccdbabdac";
    char T[] = "ccd";
    int s_lenth = strlen(S);
    const int t_lenth = strlen(T);
    int *next = get_next(T, t_lenth);
    std::cout<<KMS(T, S, next, t_lenth, s_lenth);
}