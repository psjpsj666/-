#include<iostream>
using namespace std;
template<class T>
//冒泡排序
//一次冒泡会将最大的元素放置到最终的位置上
void BubbleSort(T A[],int n)
{
   for(int i=0;i<n-1;i++){
       bool flag=false;
       for(int j=n-1;j>i;j--)
       {
           if(A[j-1]>A[j])
           {
               swap(A[j-1],A[j]);
               flag=true;
           }
       }
       if(flag==false)return;
   }
}
int main()
{
    int A[]={2,1,3,5,7,6,4,9,11};
    BubbleSort(A,9);
    for(int i=0;i<9;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}