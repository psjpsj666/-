#include<iostream>
using namespace std;
template<class T>
//合并两个有序线性表
void Merge(T Array[],T temp[],int low,int mid,int high)
{
    int index1,index2;
    for(int i=low;i<=high;i++)
    {
        temp[i]=Array[i];
    }
    index1=low;
    index2=mid+1;
    int j=low;
    while(index1<=mid&&index2<=high)
    {
        //取较小值放入合并数组
        if(temp[index1]<=temp[index2])
        {
            Array[j++]=temp[index1++];
        }
        else
        {
            Array[j++]=temp[index2++];
        }
    }
    while(index1<=mid)
    {
         Array[j++]=temp[index1++];
    }
    while(index2<=high)
    {
         Array[j++]=temp[index2++];
    }
}
template<class T>
//归并排序
void MergeSort(T A[],int low,int high)
{
    int mid;
    T temp[high-low+1];
    if(low<high)
    {
        mid=(low+high)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        Merge(A,temp,low,mid,high);
    }
  
}
int main()
{
    int A[]={2,1,3,5,7,6,4,9,11};
    MergeSort(A,0,8);
    for(int i=0;i<9;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}