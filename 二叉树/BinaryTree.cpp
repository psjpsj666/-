#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//�����������
template<class T>
class BinaryTreeNode {
	//friend class BinaryTree<T>;
private:
	T data;   //���洢������
	BinaryTreeNode<T>* left, * right;   //��������������
public:
	BinaryTreeNode() :left(NULL), right(NULL) {}//�޲ι��캯��
	BinaryTreeNode(T info, BinaryTreeNode<T>* l = NULL, BinaryTreeNode<T>* r = NULL) {
		//�������Ĺ��캯��
		data = info; left = l; right = r;
	}
	T value()const { return data; } //����������
	BinaryTreeNode<T>* leftchild()const { return left; }//����������
	BinaryTreeNode<T>* rightchild()const { return right; }//����������
	bool isLeaf() const {	//�ж���ǰ����Ƿ�ΪҶ���,���Ƿ���true
		return (left == NULL) && (right == NULL);
	}
};
enum Tags { Left, Right };  //ö������
template<class T>
class StackElement {
public:
	BinaryTreeNode<T>* pointer;
	Tags tag;
};
//��������
template<class T>
class BinaryTree {
private:
	BinaryTreeNode<T>* root;    //�����
public:
	BinaryTree() :root(NULL) {} //�޲ι��캯��
	~BinaryTree() { DeleteBinaryTree(root); }    //��������
	bool isEmpty();                       //�ж϶������Ƿ�Ϊ��
	BinaryTreeNode<T>* Root() { return root; }  //���ظ����
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current); //���ظ����
	BinaryTreeNode<T>* LefTSibling(BinaryTreeNode<T>* current); //�������ֽ��
	BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current); //�������ֽ��
	void CreateTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);  //��������
	void PreOrder(BinaryTreeNode<T>* root);    //ǰ����������������������ݹ�
	void InOrder(BinaryTreeNode<T>* root);    //������������������������ݹ�
	void PostOrder(BinaryTreeNode<T>* root);    //������������������������ݹ�
	void PreOrderWithoutRecursion(BinaryTreeNode<T>* root);//�ǵݹ�ǰ�����ζ�������������
	void InOrderWithoutRecursion(BinaryTreeNode<T>* root);//�ǵݹ��������ζ�������������
	void PostOrderWithoutRecursion(BinaryTreeNode<T>* root);//�ǵݹ�������ζ�������������
	void LevelOrder(BinaryTreeNode<T>* root);    //����α�����������������
	void DeleteBinaryTree(BinaryTreeNode<T>* root); //ɾ����������������
};
template<class T>
bool BinaryTree<T>::isEmpty() {   //�ж϶������Ƿ�Ϊ��
	return root == NULL;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current) {  //����cuurent���ĸ���� 
	using std::stack;                      //ʹ��STL�е�stack
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);                     //ջ�׼�����
	while (pointer!=NULL) {
		if (current == pointer->leftchild() || current == pointer->rightchild()) {
			return pointer;                //���current��pointer���ӽ���򷵻�
		}
		else if (pointer->rightchild() != NULL) {
			aStack.push(pointer->rightchild());
		}
		else if (pointer->leftchild() != NULL) {
			aStack.push(pointer->leftchild());
		}
		else {
			pointer = aStack.top(); 
			aStack.pop();   //��ȡջ��Ԫ��
		}
	}
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::LefTSibling(BinaryTreeNode<T>* current) { //����current�������ֵܽ��
	BinaryTreeNode<T>* tmp;
	if (current) {
		tmp = Parent(current);
		if (tmp == NULL || current == tmp->leftchild())
		{
			//cout << current->value() << "���������ֵܽ��" << endl;
			return NULL;
		}
		else {
			//cout << current->value() << "���ֵܽ��=" << tmp->leftchild() << endl;
			return tmp->leftchild();
		}
	}
	return NULL;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::RightSibling(BinaryTreeNode<T>* current) {//����current�������ֵܽ��
	if (current) {
		BinaryTreeNode<T>* tmp= Parent(current);
		if (tmp == NULL || current == tmp->rightchild())
		{
			//cout << current->value() << "���������ֵܽ��" << endl;
			return NULL;
		}
		else {
			//cout << current->value() << "���ֵܽ��=" << tmp->rightchild() << endl;
			return tmp->rightchild();
		}
	}
	return NULL;
}

template<class T>
void BinaryTree<T>::CreateTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree) {
	//��������
	//��������leftTree��������rightTree������Ԫ��info����һ���������������info
	//����this��leftTree��rightTree�����ǲ�ͬ��������
	root = new BinaryTreeNode<T>(info, leftTree.root, rightTree.root);
	//leftTree.root = rightTree.root = NULL;                //ԭ�����������ĸ����ָ�գ��������
}

template<class T>
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root) {  //ɾ��������
	if (root) {
		DeleteBinaryTree(root->leftchild());      //�ݹ�ɾ��������
		DeleteBinaryTree(root->rightchild());     //�ݹ�ɾ��������
		delete root;                              //ɾ�������
	}
}

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root) { //�ݹ�ǰ�����������
	if (root != NULL) {
		cout << root->value();
		PreOrder(root->leftchild());
		PreOrder(root->rightchild());
	}
}
template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root) {//�ݹ��������������
	if (root != NULL) {
		InOrder(root->leftchild());
		cout << root->value();
		InOrder(root->rightchild());
	}
}
template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root) {//�ݹ�������������
	if (root != NULL) {
		PostOrder(root->leftchild());
		PostOrder(root->rightchild());
		cout << root->value();
	}
}

template<class T>
void BinaryTree<T>::PreOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//�ǵݹ��ܣ�ǰ�����������
	using std::stack;
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);              //ջ�׼�����
	while (pointer) {
		cout << pointer->value();
		if (pointer->rightchild() != NULL) {
			aStack.push(pointer->rightchild());  //�Һ�����ջ
		}
		if (pointer->leftchild()) {
			pointer = pointer->leftchild();   //����·�½�
		}
		else {
			//������������ϣ�ת�����������
			pointer = aStack.top();
			aStack.pop();
		}
	}
}

template<class T>
void BinaryTree<T>::InOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//�ǵݹ��ܣ��������������
	using std::stack;
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer) {
		if (pointer) {
			aStack.push(pointer);   //��ǰ�����ջ
			pointer = pointer->leftchild();
		}
		else {
			pointer = aStack.top();
			aStack.pop();
			cout << pointer->value();
			pointer = pointer->rightchild();  //ת��������
		}
	}
}

template<class T>
void BinaryTree<T>::PostOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//�ǵݹ��ܣ��������������
	using std::stack;
	StackElement<T> element;
	stack<StackElement<T>>aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer) {
		while (pointer != NULL) {
			//�طǿ�ָ��ѹջ������·�½�
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);      //����־λΪLeft�Ľ��ѹ��ջ��
			pointer = pointer->leftchild();
		}
		element = aStack.top(); aStack.pop();  //��ȡջ��Ԫ�أ�����ջ
		pointer = element.pointer;
		if (element.tag == Left) {
			//������������
			element.tag = Right;   //�ñ�־λΪRight
			aStack.push(element);
			pointer = pointer->rightchild();
		}
		else {     //���������������
			cout << pointer->value();    //���ʵ�ǰ���
			pointer = NULL;            //��pointerָ��Ϊ�գ��Լ�����ջ
		}
	}
}

template<class T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root) {
	//�������������
	using std::queue;
	queue<BinaryTreeNode<T>*>aQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer)aQueue.push(pointer);   //��������
	while (!aQueue.empty()) {
		//���зǿ�
		pointer = aQueue.front();    //ȡ����Ԫ��
		aQueue.pop();
		cout << pointer->value();
		if (pointer->leftchild()) {
			aQueue.push(pointer->leftchild());   //������������
		}
		if (pointer->rightchild())
			aQueue.push(pointer->rightchild());  //������������
	}
}

int main()
{
	//���Գ���
	BinaryTree<char> a, b, c, d, e, f, g, h, i, nulltree;
	d.CreateTree('D', nulltree, nulltree);
	g.CreateTree('G', nulltree, nulltree);
	h.CreateTree('H', nulltree, nulltree);
	i.CreateTree('I', nulltree, nulltree);
	f.CreateTree('F', h, i);
	e.CreateTree('E', g, nulltree);
	b.CreateTree('B', d, e);
	c.CreateTree('C', nulltree, f);
	a.CreateTree('A', b, c);
	
	//ǰ�����
	cout << "ǰ��������ݹ飩: " << endl;
	a.PreOrder(a.Root());				//�ݹ�
	cout << endl;
	cout << "ǰ��������ǵݹ飩: " << endl;
	a.PreOrderWithoutRecursion(a.Root());//�ǵݹ�
	cout << endl;
	
	//�������������
	cout << "����������ݹ飩: " << endl;
	a.InOrder(a.Root());			//�ݹ�
	cout << endl;
	cout << "����������ǵݹ飩: " << endl;
	a.InOrderWithoutRecursion(a.Root());//�ǵݹ�
	cout << endl;

	//�������������
	cout << "����������ݹ飩: " << endl;
	a.PostOrder(a.Root());			//�ݹ�
	cout << endl;
	cout << "����������ǵݹ飩: " << endl;
	a.PostOrderWithoutRecursion(a.Root());//�ǵݹ�	
	cout << endl;

	//�������������
	cout << "�������: " << endl;
	a.LevelOrder(a.Root());
	cout << endl;

	//�����
	cout <<"�����="<< a.Root()->value()<<endl;
	return 0;
}