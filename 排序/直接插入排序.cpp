#include<iostream>
using namespace std;
template<class T>
//直接插入排序
void InsertSort(T A[],int n){
    int i,j;
    T temp;        //临时变量
    for(int i=1;i<n;i++)
    {
        temp=A[i];
        j=i-1;
        while(j>=0&&temp<A[j]){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
}
int main()
{
    int A[]={2,1,3,5,7,6};
    InsertSort(A,6);
    for(int i=0;i<6;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}