#include<iostream>
using namespace std;
//最小堆类模板
template<class T>
class MinHeap {
private:
	T* heapArray;            //存储数据
	int CurrentSize;         //当前大小
	int MaxSize;             //最大容量
	void CreatHeap();        //建最小堆
public:
	MinHeap();                  //构造函数
	virtual ~MinHeap();         //析构函数
	bool isLeaf(int pos)const;  //判断是否为叶结点
	int leftchild(int pos)const;//返回左孩子结点
	int rightchild(int pos)const;//返回右孩子结点
	int parent(int pos)const;    //返回父结点
	bool Remove(int pos, T& node);//删除给定结点
	bool insert(const T &newnode);//插入结点
	T& RemoveMin();               //从堆顶删除最小值
	void SiftUp(int pos);         //从pos向上开始调整
	void SiftDown(int pos);      //从pos向下开始调整
	void Print();                //输出最小堆数据
};
template<class T>
void MinHeap<T>::CreatHeap() {
	//建最小堆
	 //反复调用筛选函数,从第一个分支结点heapArray[CurrentSize/2-1]开始，自底向上逐步把子树调整成堆
	for (int i = CurrentSize / 2 - 1; i >= 0; i--) {
		SiftDown(i);
	}
}
template<class T>
MinHeap<T>::MinHeap() {
	//构造函数
	CurrentSize = 0;
	MaxSize = 100;
	heapArray = new T[MaxSize];
}
template<class T>
MinHeap<T>::~MinHeap() {
	//析构函数
	delete[]heapArray;
}
template<class T>
bool MinHeap<T>::isLeaf(int pos)const {
	//判断结点是否为叶结点
	if (pos>=CurrentSize/2&&pos<CurrentSize)return true;
	else return false;
}
template<class T>
int MinHeap<T>::leftchild(int pos)const {
	//返回结点的左孩子结点
	if (pos>=0&&pos<CurrentSize/2)
	{
		cout<< 2 * pos + 1;
		return 2 * pos + 1;
	}
	else
	{
		cout <<"找不到结果" << endl;
		return -1;
	}
}
template<class T>
int MinHeap<T>::rightchild(int pos)const {
	//返回结点的左孩子结点
	if (heapArray[2 * pos + 2] != NULL)
	{
		cout << 2 * pos + 2;
		return 2 * pos + 2;
	}
	else
	{
		cout << "找不到结果" << endl;
		return -1;
	}
}
template<class T>
int MinHeap<T>::parent(int pos)const {
	//返回结点的父结点
	if (pos <= 0&&pos>CurrentSize) {
		cout << "输入下标有误,不存在父结点" << endl;
		return -1;
	}
	else {
		return (pos - 1) / 2;
	}
}
template<class T>
bool MinHeap<T>::insert(const T& newnode) {
	//插入新结点
	if (CurrentSize == MaxSize)
	{
		cout << "堆已满" << endl;
		return false;
	}
	heapArray[CurrentSize] = newnode;
	SiftUp(CurrentSize);    //向上调整
	CurrentSize++;
	return true;
}
template<class T>
bool MinHeap<T>::Remove(int pos, T& node) {
	//删除结点
	if (CurrentSize == 0) {
		cout << "堆为空" << endl;
		return false;
	}
	if (pos < 0 || pos >= CurrentSize) return false;
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--CurrentSize];
	if (heapArray[parent(pos) > heapArray[pos]]) {
		//若删除结点处父结点大于子结点，则向上调整
		SiftUp(pos);
	}
	else SiftDown(pos);  //否则，向下调整
	node = temp;
	return true;
}
template<class T>
void MinHeap<T>::SiftDown(int pos) {
	//筛选法向下调整
	int i = pos;              //标识父结点
	int j = 2 * i + 1;        //标识关键值较小的子结点
	T temp = heapArray[i];    //保存父结点
	while (j < CurrentSize) {
		if (j<CurrentSize - 1 && heapArray[j]>heapArray[j + 1])
			j++;              //j值指向较小的子结点
		if (temp > heapArray[j]) {
			heapArray[i] = heapArray[j];
			i = j;
			j = 2 * j + 1;    //向下继续比较
		}
		else {
			break;
		}
	}
	heapArray[i] = temp;
}
template<class T>
void MinHeap<T>::SiftUp(int pos) {
	//筛选法向上调整
	int temppos = pos;
	//不是父子结点直接swap
	T temp = heapArray[temppos];
	while (temppos > 0 && heapArray[parent(temppos)] > temp) {
		heapArray[temppos] = heapArray[parent(temppos)];
		temppos = parent(temppos);
	}
	heapArray[temppos] = temp;    //找到最终位置
}
template<class T>
T& MinHeap<T>::RemoveMin() {
	//从堆顶删除最小值
	if (CurrentSize == 0) {
		cout << "堆已空" << endl;
	}
	T temp = heapArray[0];
	heapArray[0] = heapArray[--CurrentSize];
	SiftDown(0);
	return temp;
}
template<class T>
void MinHeap<T>::Print() {
	//输出最小堆所有数据
	for (int i = 0; i < CurrentSize; i++) {
		cout <<"(" <<i<<","<<heapArray[i] << ") ";
	}
}
int main() {
	//测试程序
	MinHeap<int> h;       //生成最大容量为100的堆
	int Array[] = {10,25,58,55,68,42,56,15,26 };
	cout << "开始插入数据：" << endl;
	int n = sizeof(Array)/sizeof(Array[0]);
	for (int i = 0; i < n; i++) {
		h.insert(Array[i]);
	}
	cout << "最小堆为：";
	h.Print();
	cout << endl << "下标为4的结点的父结点下标：" << h.parent(4) << endl;
	cout << "插入数据35：";
	h.insert(35);
	h.Print();
	cout <<endl<< "删除下标为4的结点：";
	int temp;
	h.Remove(4,temp);
	h.Print();
	cout<<endl << "删除最小值：";
	h.RemoveMin();
	h.Print();
	cout <<endl<< "判断下标5的结点的左子结点下标：";
	h.leftchild(5);
	cout << "判断下标5的结点的右子结点下标：";
	h.rightchild(5);
	return 0;
}