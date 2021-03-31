#include<iostream>
using namespace std;
template<class T>
//shell排序
/*基本思想：
先将排序表分割成d个形如L[i,i+d,i+2d,...,i+kd]的特殊子表，
分别进行直接插入排序，当整个表中的元素已呈“基本有序时”，再对全体
记录进行一次直接插入排序
*/
void ShellSort(T A[],int n)
{
    int i,j;
    int temp;
    for(int dk=n/2;dk>=1;dk=dk/2)
    {
        for(i=dk;i<n;i+=dk)
        {
            temp=A[i];
            /*for(j=i-dk;j>=0&&temp<A[j];j-=dk)
            {
                 A[j+dk]=A[j];
            }*/
            j=i-dk;
            while(j>=0&&temp<A[j])
            {
                A[j+dk]=A[j];
                j-=dk;
            }
            A[j+dk]=temp;
        }
    }
}
int main()
{
    int A[]={2,1,3,5,7,6,4,9,11};
    ShellSort(A,9);
    for(int i=0;i<9;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}