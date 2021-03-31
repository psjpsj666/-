#include<iostream>
using namespace std;
template<class T>
//折半插入排序
void BInsertSort(T A[],int n)
{
    int i,j;
    int temp;
    int low,mid,high;
    for(int i=0;i<n;i++)
    {
        temp=A[i];
        low=0;high=i;
        while(low<=high)
        {
            mid=(low+high)/2;
            if(A[mid]>temp)
            {
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        j=i-1;
        while(j>=high+1&&temp<A[j])
        {
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
}
int main()
{
    int A[]={2,1,3,5,7,6,4};
    BInsertSort(A,7);
    for(int i=0;i<7;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}