#include<iostream>
using namespace std;
//��С����ģ��
template<class T>
class MinHeap {
private:
	T* heapArray;            //�洢����
	int CurrentSize;         //��ǰ��С
	int MaxSize;             //�������
	void CreatHeap();        //����С��
public:
	MinHeap();                  //���캯��
	virtual ~MinHeap();         //��������
	bool isLeaf(int pos)const;  //�ж��Ƿ�ΪҶ���
	int leftchild(int pos)const;//�������ӽ��
	int rightchild(int pos)const;//�����Һ��ӽ��
	int parent(int pos)const;    //���ظ����
	bool Remove(int pos, T& node);//ɾ���������
	bool insert(const T &newnode);//������
	T& RemoveMin();               //�ӶѶ�ɾ����Сֵ
	void SiftUp(int pos);         //��pos���Ͽ�ʼ����
	void SiftDown(int pos);      //��pos���¿�ʼ����
	void Print();                //�����С������
};
template<class T>
void MinHeap<T>::CreatHeap() {
	//����С��
	 //��������ɸѡ����,�ӵ�һ����֧���heapArray[CurrentSize/2-1]��ʼ���Ե������𲽰����������ɶ�
	for (int i = CurrentSize / 2 - 1; i >= 0; i--) {
		SiftDown(i);
	}
}
template<class T>
MinHeap<T>::MinHeap() {
	//���캯��
	CurrentSize = 0;
	MaxSize = 100;
	heapArray = new T[MaxSize];
}
template<class T>
MinHeap<T>::~MinHeap() {
	//��������
	delete[]heapArray;
}
template<class T>
bool MinHeap<T>::isLeaf(int pos)const {
	//�жϽ���Ƿ�ΪҶ���
	if (pos>=CurrentSize/2&&pos<CurrentSize)return true;
	else return false;
}
template<class T>
int MinHeap<T>::leftchild(int pos)const {
	//���ؽ������ӽ��
	if (pos>=0&&pos<CurrentSize/2)
	{
		cout<< 2 * pos + 1;
		return 2 * pos + 1;
	}
	else
	{
		cout <<"�Ҳ������" << endl;
		return -1;
	}
}
template<class T>
int MinHeap<T>::rightchild(int pos)const {
	//���ؽ������ӽ��
	if (heapArray[2 * pos + 2] != NULL)
	{
		cout << 2 * pos + 2;
		return 2 * pos + 2;
	}
	else
	{
		cout << "�Ҳ������" << endl;
		return -1;
	}
}
template<class T>
int MinHeap<T>::parent(int pos)const {
	//���ؽ��ĸ����
	if (pos <= 0&&pos>CurrentSize) {
		cout << "�����±�����,�����ڸ����" << endl;
		return -1;
	}
	else {
		return (pos - 1) / 2;
	}
}
template<class T>
bool MinHeap<T>::insert(const T& newnode) {
	//�����½��
	if (CurrentSize == MaxSize)
	{
		cout << "������" << endl;
		return false;
	}
	heapArray[CurrentSize] = newnode;
	SiftUp(CurrentSize);    //���ϵ���
	CurrentSize++;
	return true;
}
template<class T>
bool MinHeap<T>::Remove(int pos, T& node) {
	//ɾ�����
	if (CurrentSize == 0) {
		cout << "��Ϊ��" << endl;
		return false;
	}
	if (pos < 0 || pos >= CurrentSize) return false;
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--CurrentSize];
	if (heapArray[parent(pos) > heapArray[pos]]) {
		//��ɾ����㴦���������ӽ�㣬�����ϵ���
		SiftUp(pos);
	}
	else SiftDown(pos);  //�������µ���
	node = temp;
	return true;
}
template<class T>
void MinHeap<T>::SiftDown(int pos) {
	//ɸѡ�����µ���
	int i = pos;              //��ʶ�����
	int j = 2 * i + 1;        //��ʶ�ؼ�ֵ��С���ӽ��
	T temp = heapArray[i];    //���游���
	while (j < CurrentSize) {
		if (j<CurrentSize - 1 && heapArray[j]>heapArray[j + 1])
			j++;              //jֵָ���С���ӽ��
		if (temp > heapArray[j]) {
			heapArray[i] = heapArray[j];
			i = j;
			j = 2 * j + 1;    //���¼����Ƚ�
		}
		else {
			break;
		}
	}
	heapArray[i] = temp;
}
template<class T>
void MinHeap<T>::SiftUp(int pos) {
	//ɸѡ�����ϵ���
	int temppos = pos;
	//���Ǹ��ӽ��ֱ��swap
	T temp = heapArray[temppos];
	while (temppos > 0 && heapArray[parent(temppos)] > temp) {
		heapArray[temppos] = heapArray[parent(temppos)];
		temppos = parent(temppos);
	}
	heapArray[temppos] = temp;    //�ҵ�����λ��
}
template<class T>
T& MinHeap<T>::RemoveMin() {
	//�ӶѶ�ɾ����Сֵ
	if (CurrentSize == 0) {
		cout << "���ѿ�" << endl;
	}
	T temp = heapArray[0];
	heapArray[0] = heapArray[--CurrentSize];
	SiftDown(0);
	return temp;
}
template<class T>
void MinHeap<T>::Print() {
	//�����С����������
	for (int i = 0; i < CurrentSize; i++) {
		cout <<"(" <<i<<","<<heapArray[i] << ") ";
	}
}
int main() {
	//���Գ���
	MinHeap<int> h;       //�����������Ϊ100�Ķ�
	int Array[] = {10,25,58,55,68,42,56,15,26 };
	cout << "��ʼ�������ݣ�" << endl;
	int n = sizeof(Array)/sizeof(Array[0]);
	for (int i = 0; i < n; i++) {
		h.insert(Array[i]);
	}
	cout << "��С��Ϊ��";
	h.Print();
	cout << endl << "�±�Ϊ4�Ľ��ĸ�����±꣺" << h.parent(4) << endl;
	cout << "��������35��";
	h.insert(35);
	h.Print();
	cout <<endl<< "ɾ���±�Ϊ4�Ľ�㣺";
	int temp;
	h.Remove(4,temp);
	h.Print();
	cout<<endl << "ɾ����Сֵ��";
	h.RemoveMin();
	h.Print();
	cout <<endl<< "�ж��±�5�Ľ������ӽ���±꣺";
	h.leftchild(5);
	cout << "�ж��±�5�Ľ������ӽ���±꣺";
	h.rightchild(5);
	return 0;
}