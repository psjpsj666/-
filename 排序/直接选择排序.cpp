#include<iostream>
using namespace std;
template<class T>
//直接选择排序
//选择第i个最小的值，与i上的元素交换
void SelectSort(T A[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int Smallest=i;
        for(int j=i+1;j<n;j++)
        {
            if(A[j]<A[Smallest])
            {
                Smallest=j;
                //swap(A[j],A[Smallest]);
            }
        }
        swap(A[i],A[Smallest]); 
    }
}
/*template<class Record>
void SelectSort(Record Array[], int n) {
	//依次选出第i个小的记录，即剩余记录中最小的那个
	for (int i = 0; i < n - 1; i++)
	{
		//首先假设记录i就是最小的
		int Smallest = i;
		//开始向后扫描所有剩余记录
		for (int j = i + 1; j < n; j++) {
			//如果发现更小的记录，记录它的位置
			if (Array[j] < Array[Smallest])
				Smallest = j;
		}
        //将第i小的记录放在数组中第i个位置
        swap(Array[i],Array[Smallest]);
	}
}*/


int main()
{
    int A[]={66,5,22,4,5,7,6};
    SelectSort(A,7);
    for(int i=0;i<7;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}