#include<iostream>
using namespace std;
template<class T>
//快速排序
void QuickSort(T A[],int l,int r)
{
   if(l<r){
       int i=l,j=r;
       int x=A[l]; //初始轴值
       while(i<j)
       {
           //从右向左找第一个小于x的值
           while(i<j&&A[j]>=x)
           {
               j--;
            }
            if(i<j)
            {
                A[i]=A[j];
                i++;
            }
            //从左向右找第一个大于x的值
            while(i<j&&A[i]<x)
            {
                i++;
            }
            if(i<j)
            {
                A[j]=A[i];
                j--;
            }
        }
        //退出时，i等于j。将x填到这个坑中。
        A[i]=x;  
        QuickSort(A,l,i-1);
        QuickSort(A,i+1,r);
   }
}
int main()
{
    int A[]={2,1,3,5,7,6,4,9,11,848,54,65,25};
    QuickSort(A,0,12);
    for(int i=0;i<13;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}