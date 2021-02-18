#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T> class BST;
//BST���
template<class T>
class BSTNode {
	friend class BST<T>;
private:
	T data;    //�������
	BSTNode<T>* left, * right;     //��������
public:
	BSTNode():left(NULL),right(NULL){}   //�޲ι��캯��
	BSTNode(const T& x) { data = x; }    //�вι��캯��
	BSTNode(const T &info, BSTNode<T> *l, BSTNode<T> *r):data(info),left(l),right(r){}   //�вι��캯��
	T Value() const{ return data; }  //���ؽ��ֵ
	BSTNode<T>* leftchild() const{ return left; }  //����������
	BSTNode<T>* rightchild()const { return right; }//����������
	void setValue(const T& value) {           //���ý��Ԫ��ֵ
		data = value;
	}
	void Display(int i) {
		cout << "( " << i << "," << data << ")\n";
		if (left)left->Display(2*i+1);
		if (right)right->Display(2*i+2);
	}
};
//BSTģ��
template<class T>
class BST {
private:
	BSTNode<T>* root;                         //�����
public:
	BST() { root = NULL; }                    //���캯��
	~BST() { Clear(root); }                   //��������
	BSTNode<T>* Root() { return root; }       //���ظ����
	bool isEmpty();                           //�ж��Ƿ�Ϊ��
	bool isBST(BSTNode<T>* root);             //�ж��Ƿ�Ϊ����������
	BSTNode<T>* Parent(BSTNode<T>* node);     //���ؽ��node�ĸ����
	bool Insert(BSTNode<T> *node);            //����
	void Remove(BSTNode<T>* node);            //ɾ������
	BSTNode<T>* Search(const T val);          //����
	void PreTravesal(BSTNode<T>* root);       //ǰ�����
	void InTravesal(BSTNode<T>* root);        //�������
	void PostTravesal(BSTNode<T>* root);      //�������
	void PlaneTravesal(BSTNode<T>* root);     //�������
	void Clear(BSTNode<T>* root);             //��ն�����
};
template<class T>
bool BST<T>::isEmpty() {
	//�ж�BST�Ƿ�Ϊ��
	return root == NULL;
}
template<class T>
bool BST<T>::isBST(BSTNode<T>* root) {
	//�ж��Ƿ�ΪBST
	if (root==NULL) {    //����ҲΪBST
		return true; 
	}
	BSTNode<T>* pointer = root;
	if (pointer) {
		if (pointer->left&&pointer->right) {                     //ͬʱ�������Һ��ӽ��
			if (pointer->data > pointer->left->data && pointer->data < pointer->right->data) {
				isBST(pointer->left);
				isBST(pointer->right);
			}
		}
		else if (pointer->left && !pointer->right)               //ֻ�������ӽ��
		{
			if(pointer->data>pointer->left->data)
				isBST(pointer->left);
		}
		else if (!pointer->left && pointer->right)               //ֻ�����Һ��ӽ��
		{
			if (pointer->data < pointer->right->data)
				isBST(pointer->right);
		}
		else return false;
	}
	return true;
}
template<class T>
BSTNode<T>* BST<T>::Parent(BSTNode<T>*node) {    //Ѱ�ҽ��node�ĸ����
	/*stack<BSTNode<T>*> aStack;
	BSTNode<T>* pointer=root;
	aStack.push(NULL);       //ջ�׼�����
	while (pointer) {
		if (node==pointer->left ||node==pointer->right)
		{
			return pointer;
		}
		if (pointer->right != NULL) {
			aStack.push(pointer->right);
		}
		if (pointer->left != NULL) {
			aStack.push(pointer->left);
		}
		else {
			pointer = aStack.top();
			aStack.pop();
		}
	}*/
	queue<BSTNode<T>*>q;
	BSTNode<T>* temp = NULL;
	if (NULL == root)   //��Ϊ��
		return NULL;
	if (node == NULL)     //���Ϊ��
		return NULL;
	q.push(root);
	while (!q.empty()) {
		//�����в�Ϊ��ʱѭ��
		temp = q.front();
		q.pop();                //ȡ����Ԫ��
		if (temp->left == node || temp->right == node)
			return temp;
		if (temp->left)q.push(temp->left);
		if (temp->right)q.push(temp->right);
	}
	return NULL;
}
template<class T>
bool BST<T>::Insert(BSTNode<T>* node) {
	//�ڶ����������в����½��
	//���������������Ϊ�սڵ㣬�����ڵ��Ϊ���ڵ�
	//������������Ϊ�ǿսڵ㣬����Ҫ���ҵ�������ڵ㣬����ԭ����ǴӸ��ڵ㿪ʼ��������ڸ����ұ��ߣ�С�ڸ�������ߣ�ֱ���ҵ����ʽڵ㣬
	if (root == NULL)
	{
		root = node;
		return true;
	}
	if (node == NULL)
		return false;
	BSTNode<T>* pointer, * temp = NULL;
	pointer = root;
	while (pointer) {
		temp = pointer;               //temp�洢�����
		if (node->data == pointer->data)return false;   //����ظ������ܲ���
		else if (node->data > pointer->data) {
			pointer = pointer->right;
		}
		else {
			pointer = pointer->left;
		}
	}
	if (node->data < temp->data) {
		temp->left = node;
	}
	else {
		temp->right = node;
	}
	return true;
	
}
template<class T>
void BST<T>::Remove(BSTNode<T>* node) {
	//ɾ���������еĽ��node
	//����ڵ�û����Ů���޸��丸�ڵ�ָ��ΪNULL��ɾ������
    //����ýڵ�������������޸��丸�׽ڵ��ָ��������ӵ�parentָ�뼴��
    //����ýڵ����Һ���������޸��丸�׽ڵ��ָ������Һ��ӵ�parentָ�뼴��
    //���ͬʱ�����Һ��ӵ����������Ƚϸ��ӣ�һ����2�ַ�������
        //(1)�ýڵ��ұߺ��ӵ���Сֵ�滻�ýڵ㣬�����ڵ�λ�ñ��ֲ���
	    //(2)�ýڵ���ߺ��ӵ����ֵ�滻�ýڵ㣬�����ڵ�λ�ñ��ֲ���
	BSTNode<T>* temp = NULL;
	if (node==NULL)            //ɾ������ǿս��
		return;
	BSTNode<T>* parent = Parent(node);
	if (node->left == NULL) {
		//��ɾ������������������������ĸ������ɾ�����
		if (parent == NULL)   //ɾ�����Ϊ�����
			root = node->right;
		else if (parent->left == node)
			parent->left = node->right;
		else
			parent->right = node->right;
		delete node;        //ɾ���ý��
		node = NULL;
		return;
	}
	else {
		//����������
		temp = node->left;
		while (temp->right)//�����������ҶԳ�������һ�����
			temp = temp->right;
		//��ɾ��������������Ϊtemp��������
		temp->right = node->right;
		//��ɾ�����������������汻ɾ�����
		if (parent == NULL) root = node->left;
		else if (parent->left == node)parent->left = node->left;
		else parent->right = node->left;
		delete node;
		node = NULL;
		return;
	}
}
template<class T>
BSTNode<T>* BST<T>::Search(const T val) {          //����Ԫ��ֵΪval�Ľ��
	BSTNode<T>* pointer = root;
	while (pointer) {
		if (val > pointer->Value()) {
			pointer = pointer->rightchild();
		}
		else if (val < pointer->Value()) {
			pointer = pointer->leftchild();
		}
		else {
			return pointer;
		}
	}
	return NULL;       //û���ҵ�
}
template<class T>
void BST<T>::Clear(BSTNode<T>* root) {
	//��ն�����
	if (root) {
		Clear(root->leftchild());
		Clear(root->rightchild());
		delete root;
	}
}
template<class T>
void BST<T>::PreTravesal(BSTNode<T>* root) {
	//ǰ�����
	BSTNode<T>* pointer = root;
	if (pointer) {
		cout << pointer->Value() << " ";
		PreTravesal(pointer->leftchild());
		PreTravesal(pointer->rightchild());
	}
}
template<class T>
void BST<T>::InTravesal(BSTNode<T>* root) {
	//�������
	BSTNode<T>* pointer = root;
	if (pointer) {
		InTravesal(pointer->leftchild());
		cout << pointer->Value() << " ";
		InTravesal(pointer->rightchild());
	}
}
template<class T>
void BST<T>::PostTravesal(BSTNode<T>* root) {
	//�������
	BSTNode<T>* pointer = root;
	if (pointer) {
		PostTravesal(pointer->leftchild());
		PostTravesal(pointer->rightchild());
		cout << pointer->Value() << " ";
	}
}
template<class T>
void BST<T>::PlaneTravesal(BSTNode<T>* root) {
	//�������
	queue<BSTNode<T>*> aQueue;
	BSTNode<T>* pointer = root;
	if (pointer)aQueue.push(pointer);  //��������
	while (!aQueue.empty()) {
		//���зǿ�
		pointer = aQueue.front();     //ȡ���׽��
		aQueue.pop();
		cout << pointer->Value() << " ";
		if (pointer->leftchild()) {
			aQueue.push(pointer->leftchild());
		}
		if (pointer->rightchild()) {
			aQueue.push(pointer->rightchild());
		}
	}
}
int main()
{
	//����
	BST<int> BT;  //�����޲ι��캯�������ɿյĶ�����
	cout << "=========�ж϶������Ƿ�Ϊ��(1Ϊ�գ�0Ϊ����)=========" << endl;
	cout << BT.isEmpty() << endl;
	cout << "=========����������=========" << endl;
	int ELE[6] = {50,28,5,62,88,45};
	BSTNode<int> Node[6];
	for (int i = 0; i < 6; i++) {
		Node[i].setValue(ELE[i]);
		BT.Insert(&Node[i]);
	}
	Node[0].Display(0);

	cout << "=========ǰ�����=========" << endl;
	BT.PreTravesal(BT.Root());
	cout << "\n=========�������=========" << endl;
	BT.InTravesal(BT.Root());
	cout << "\n=========�������=========" << endl;
	BT.PostTravesal(BT.Root());
	cout << "\n=========�������=========" << endl;
	BT.PlaneTravesal(BT.Root());
	cout << "\n=========�ж϶������Ƿ�Ϊ����������=========" << endl;
	cout << BT.isBST(BT.Root()) << endl;
	cout << "=========����72=========" << endl;
	BSTNode<int> p(72);
	BT.Insert(&p);
	cout << "=========�������=========" << endl;
	BT.PlaneTravesal(BT.Root());
	
	cout << "\n=========���88�ĸ����=========" << endl;
	cout << BT.Parent(&Node[4])->Value();
	cout << "\n=========ɾ��28=========" << endl;
	BT.Remove(&Node[1]);
	cout << "=========�������=========" << endl;
	BT.PlaneTravesal(BT.Root());
	return 0;
}