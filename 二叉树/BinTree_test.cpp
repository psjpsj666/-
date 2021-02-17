#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T> class BinTree;
//������������ģ��
template<class T>
class BinTreeNode{
	friend class BinTree<T>;
private:
	T data;
	BinTreeNode<T>* leftchild, * rightchild;
public:
	BinTreeNode() {          //�޲ι��캯��
		leftchild = rightchild = NULL;
	}
	BinTreeNode(const T& info) {
		data = info;
		leftchild = rightchild = NULL;
	}
	BinTreeNode(const T& x, BinTreeNode<T>* L, BinTreeNode<T>* R) {
		data = x;
		leftchild = L;
		rightchild = R;
	}
	T Value() { return data; }
	void SetValue(const T& x) { data = x; }
	void SetLeft(BinTreeNode<T>* node) { leftchild = node; }
	void SetRight(BinTreeNode<T>* node) { rightchild = node; }
};
//����������ģ��
template<class T>
class BinTree {
public:
	BinTreeNode<T>* root;
public:
	BinTree();                        //�����յĶ�����
	~BinTree();                       //��������
	bool IsEmpty();                   //�ж϶������Ƿ�Ϊ��
	BinTreeNode<T>* CreateRoot(const T& x); //��ָ��Ԫ��ֵ���������
	void SetRoot(BinTreeNode<T>* node) {
		root = node;
	}
	void Clear();                     //��ն�����
	BinTreeNode<T>* GetRoot();        //��ȡ�����
	//ǰ��ݹ鴴��������
//	BinTreeNode<T>* CreateTree(BinTreeNode<T>*tree,T *num,int&index);
	//��һ�������Ϊָ���������Ӳ���
	BinTreeNode<T>* InsertLeftChild(BinTreeNode<T>* pNode, const T& x);
	//��һ�������Ϊָ�������Һ��Ӳ���
	BinTreeNode<T>* InsertRightChild(BinTreeNode<T>* pNode, const T& x);
	//�޸�ָ������Ԫ��ֵ
	bool ModifyNodeValue(BinTreeNode<T>* pNode, const T& x);
	//��ȡָ������Ԫ��ֵ
	bool GetNodeValue(BinTreeNode<T>*pNode,T &x);
	//��ȡָ���������ӽ��
	BinTreeNode<T>* GetLeftChild(BinTreeNode<T>*pNode);
	//��ȡָ�������Һ��ӽ��
	BinTreeNode<T>* GetRightChild(BinTreeNode<T>* pNode);
	void PreOrderTraverse(BinTreeNode<T>* pNode);           //���ݹ鷽ʽ�������
	void InOrderTraverse(BinTreeNode<T>* pNode);            //���ݹ鷽ʽ�������
	void PostOrderTraverse(BinTreeNode<T>* pNode);          //���ݹ鷽ʽ�������
	void PreOrderTraverse();                                //���ǵݹ鷽ʽ�������
	void InOrderTraverse();                                 //���ǵݹ鷽ʽ�������
	//void PostOrderTraverse();                              //���ǵݹ鷽ʽ�������
	void LevelOrederTraverse();                             //���ǵݹ鷽ʽ������
	//���ǵݹ鷽ʽ��ȡָ�����ĸ����
	BinTreeNode<T>* GetParent(BinTreeNode<T>*pNode);
	//ɾ����ָ�����Ϊ����������
	void DeleteSubTree(BinTreeNode<T>* pNode);
	//��DeleteSubTree�������ð��ǵݹ鷽ʽɾ����ָ�����Ϊ��������
	void DeleteSubTreeNode(BinTreeNode<T>*pNode);
	//���ǵݹ鷽ʽ���ݹؼ��ֲ��ҽ��
	BinTreeNode<T>* SearchByKey(const T&x);
};

//ʵ�ִ����յĶ�����
template<class T>
BinTree<T>::BinTree() {
	root = NULL;         //��ָ�������ָ����Ϊ��
}

//ʵ����ָ��Ԫ��ֵ���������
template<class T>
BinTreeNode<T>* BinTree<T>::CreateRoot(const T& x) {
	if (root != NULL) {
		//��ԭ�ȴ��ڸ���㣬��ֱ�ӽ�������ֵ��Ϊx
		root->data = x;
	}
	else {
		//���򣬴���һ���µĽ����Ϊ�����
		root = new BinTreeNode<T>(x);
	}
	return root;
}

//�ж϶������Ƿ�Ϊ��
template<class T>
bool BinTree<T>::IsEmpty() {
	if (root == NULL) { 
		return true;
	}
	else { 
		return false;
	}
}

//��ȡ�����
template<class T>
BinTreeNode<T>* BinTree<T>::GetRoot() {
	return root;
}

//��һ�������Ϊָ���������Ӳ���
template<class T>
BinTreeNode<T>* BinTree<T>::InsertLeftChild(BinTreeNode<T>* pNode, const T& x) {
	BinTreeNode<T>* pNewNode;
	if (pNode == NULL)
		return NULL;
	pNewNode = new BinTreeNode<T>(x);
	if (pNewNode == NULL)
		return NULL;
	pNode->leftchild = pNewNode;
	return pNewNode;
}

// ��һ�������Ϊָ�������Һ��Ӳ���
template<class T>
BinTreeNode<T>*BinTree<T>::InsertRightChild(BinTreeNode<T>*pNode, const T & x) {
	BinTreeNode<T>* pNewNode;
	if (pNode == NULL)
		return NULL;
	pNewNode = new BinTreeNode<T>(x);
	if (pNewNode == NULL)
		return NULL;
	pNode->rightchild = pNewNode;
	return pNewNode;
}

//�޸�ָ������Ԫ��ֵ
template<class T>
bool BinTree<T>::ModifyNodeValue(BinTreeNode<T>* pNode,const T &x) {
	if (pNode == NULL)
		return false;
	pNode->data = x;
	return true;
}

//��ȡָ������Ԫ��ֵ
template<class T>
bool BinTree<T>::GetNodeValue(BinTreeNode<T>* pNode, T& x) {
	if (pNode == NULL)
		return false;
	x = pNode->data;
	return true;
}

//��ȡָ���������ӽ��
template<class T>
BinTreeNode<T>* BinTree<T>::GetLeftChild(BinTreeNode<T>* pNode) {
	if (pNode == NULL)
		return false;
	return pNode->leftchild;
}

//��ȡָ�������Һ��ӽ��
template<class T>
BinTreeNode<T>* BinTree<T>::GetRightChild(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return false;
	return pNode->rightchild;
}

//���ݹ鷽ʽ�������
template<class T>
void BinTree<T>::PreOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	cout << pNode->data << " ";
	PreOrderTraverse(pNode->leftchild);
	PreOrderTraverse(pNode->rightchild);
}

//���ݹ鷽ʽ�������
template<class T>
void BinTree<T>::InOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	InOrderTraverse(pNode->leftchild);
	cout << pNode->data << " ";
	InOrderTraverse(pNode->rightchild);
}

//���ݹ鷽ʽ�������
template<class T>
void BinTree<T>::PostOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	PostOrderTraverse(pNode->leftchild);
	PostOrderTraverse(pNode->rightchild);
	cout << pNode->data << " ";
}

//ʵ�ַǵݹ��������
//����ջʵ�֣�ջ��Ԫ�ؼ�����һ��Ҫ���ʵ������ĸ����
/*��1�����������ĸ������ջ
  ��2����ջ��Ԫ�س�ջ�����ʣ����ȷ��ʸ���㣩����ջ��Ԫ�ش������������������������ջ��
       ��ջ��Ԫ�ش������������������������ջ
  ��3���ظ����裨2����ֱ��ջΪ��
  */
template<class T>
void BinTree<T>::PreOrderTraverse() {
	BinTreeNode<T>* pNode = NULL;
	stack<BinTreeNode<T>*>s;
	if (root == NULL)
		return;
	//���������ջ
	s.push(root);
	while (!s.empty()) {
		//ջ��Ϊ��ʱѭ��
		//ջ��Ԫ�س�ջ������
		pNode = s.top();
		s.pop();
		cout << pNode->data << " ";
		//�������������������������������ջ
		if (pNode->rightchild)
			s.push(pNode->rightchild);
		//�������������������������������ջ
		if (pNode->leftchild)
			s.push(pNode->leftchild);
	}
}

//�ǵݹ��������
template<class T>
void BinTree<T>::InOrderTraverse() {
	stack<BinTreeNode<T>*>s;
	BinTreeNode<T>* pNode = root;
	if (root == NULL)
		return;
	while (!s.empty()||pNode) {
		//��ջ��Ϊ��ʱѭ��
		if (pNode) {
			s.push(pNode);   //��ǰ�����ջ
			pNode = pNode->leftchild;
		}
		else {
			pNode = s.top();
			s.pop();    //����ջ��Ԫ�ز�����
			cout << pNode->data << " ";
			pNode = pNode->rightchild;
		}
	}
}

//�ǵݹ�������


//���ǵݹ鷽ʽ������
/*
��1�����������ĸ�������
��2������ͷԪ�س��Ӳ����ʣ�����ͷԪ�ش������������������������ӣ�
     ����ͷԪ�ش�������������������������
��3���ظ����裨2����ֱ������Ϊ��
*/
template<class T>
void BinTree<T>::LevelOrederTraverse() {
	queue<BinTreeNode<T>*> q;
	BinTreeNode<T>* pNode=NULL;
	if (root == NULL)
		return;
	q.push(root);
	while (!q.empty()) {
		pNode = q.front();     //ȡ���׽�㣬����������
		q.pop();
		cout << pNode->data << " ";
		//��������������������������������
		if (pNode->leftchild)
			q.push(pNode->leftchild);
		//����ͷԪ�ش�������������������������
		if (pNode->rightchild)
			q.push(pNode->rightchild);
	}
}

//��ȡָ�����ĸ����,�ο���������㷨
template<class T>
BinTreeNode<T>* BinTree<T>::GetParent(BinTreeNode<T>* pNode) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (pNode == root)//��ָ�����Ϊ�����
		return NULL;
	if (root == NULL)//���������ǿ���
		return NULL;
	q.push(root);  //����������
	while (!q.empty()) {    //�����в�Ϊ��ʱѭ��
		pCurNode = q.front();
		q.pop();
		if (pCurNode->leftchild == pNode || pCurNode->rightchild == pNode)
			return pCurNode;
		if (pCurNode->leftchild)
			q.push(pCurNode->leftchild);
		if (pCurNode->rightchild)
			q.push(pCurNode->rightchild);
	}
	return NULL;
}

/*
ɾ����ָ�����Ϊ����������һ����Ҫ�������Ӷ�������ɾ������һ����Ҫ�������Ľ���ͷ�
��1���������Ӷ�������ɾ����ͨ����ָ������˫�׽���ָ���ÿ���ʵ�֣���ɾ���������Ŷ�������
     ��Ӧ�������ָ��ֵ�ÿգ�
��2���������еĽ���ͷţ����ǲ��������ڱ������������н��ķ�ʽ���������ռ�ݵ��ڴ��ͷš�
     ��ˣ�ͬ�����㷨һ����ɾ������Ҳ���Բ��õݹ鷽ʽ�ͷǵݹ鷽ʽ��
*/

//ɾ����ָ�����Ϊ��������
template<class T>
void BinTree<T>::DeleteSubTree(BinTreeNode<T>* pNode) {
	BinTreeNode<T>* pParentNode = NULL;
	//��ָ�����Ϊ�գ��򷵻�
	if (pNode == NULL)
		return;
	//�������Ŷ�����ɾ������������Ϊ��
	if (root == pNode)
		root = NULL;
	//������ָ��������˫�׽�㣬��˫�׽������ӻ��Һ����ÿ�
	else if ((pParentNode = GetParent(pNode)) != NULL) {
		if (pNode == pParentNode->leftchild)
			pParentNode->leftchild = NULL;
		else
			pParentNode->rightchild = NULL;
	}
	//����ָ����㲻�Ƕ������еĽ�㣬ֱ�ӷ���
	else return;
	DeleteSubTreeNode(pNode);  //����DeleteSubTreeNodeɾ����pNodeΪ��������
}

//��DeleteSubTree�������ð��ǵݹ鷽ʽɾ����ָ�����Ϊ��������
template<class T>
void BinTree<T>::DeleteSubTreeNode(BinTreeNode<T>* pNode) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (pNode == NULL)
		return;
	//���ǵݹ��α����ķ�ʽɾ������
	q.push(pNode);
	while (!q.empty()) {
		pCurNode = q.front();
		q.pop();
		if (pCurNode->leftchild)
			q.push(pCurNode->leftchild);
		if (pCurNode->rightchild)
			q.push(pCurNode->rightchild);
		delete pCurNode;
	}
}

//���ݹؼ��ֲ��ҽ�㣬ʵ���Ͼ��ǰ���ħ�ֹ��ɱ�����������ÿһ����㣬ֱ���ҵ���ؼ�����ƥ��Ľ��
template<class T>
BinTreeNode<T>* BinTree<T>::SearchByKey(const T& x) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (root == NULL)
		return NULL;
	//���ǵݹ��α�����ʽ���ҽ��
	while (!q.empty()) {
		pCurNode = q.front();
		q.pop();
		if (pCurNode->data == x)
			return pCurNode;
		if (pCurNode->leftchild)
			q.push(pCurNode->leftchild);
		if (pCurNode->rightchild)
			q.push(pCurNode->rightchild);
	}
	return NULL;
}

//��ն�����
template<class T>
void BinTree<T>::Clear()
{
	DeleteSubTree(root);
}

//��������
template<class T>
BinTree<T>::~BinTree() {
	Clear();
}

/*//ǰ��ݹ鴴��������
template<class T>
BinTreeNode<T>* BinTree<T>::CreateTree(BinTreeNode<T>* node, T *num, int& index) {
	if (num[index] == NULL)
		return NULL;
	else {
		node = new BinTreeNode<T>;
		node->data = num[index];
		node->leftchild = CreateTree(node->leftchild,num,++index);
		node->rightchild = CreateTree(node->rightchild,num,++index);
	}
	return node;
}*/
int main() {
	//���Գ���
	BinTree<char> s;    //���ɿյĶ�����
	cout << "===========��ʼ============" << endl;
	cout << "===========�ж϶������Ƿ�Ϊ�գ�1Ϊ�գ�0Ϊ���գ�============" << endl;
	cout << s.IsEmpty() << endl;
	cout << "===========��ʼ������============" << endl;
	//BinTreeNode<char> g('G', NULL, NULL), e('E', &g, NULL), d('D', NULL, NULL), f('F', NULL, NULL), c('C', NULL, &f), b('B', &d, &e), a('A', &b, &c);
	BinTreeNode<char> a, b, c, d, e, f, g;
	a.SetValue('A'); 
	b.SetValue('B');
	c.SetValue('C');
	d.SetValue('D');
	e.SetValue('E');
	f.SetValue('F');
	g.SetValue('G');
	a.SetLeft(&b); a.SetRight(&c);
	b.SetLeft(&d); b.SetRight(&e);
	c.SetLeft(NULL); 
	c.SetRight(&f);
	d.SetLeft(NULL); d.SetRight(NULL);
	e.SetLeft(&g); e.SetRight(NULL);
	s.SetRoot(&a);
	cout << s.GetRoot()->Value() << endl;
	cout << "===========�������============" << endl;
	s.PreOrderTraverse();
	cout<< "\n===========�������============" << endl;
	s.InOrderTraverse();
	cout << "\n===========�������============" << endl;
	s.PostOrderTraverse(s.GetRoot());
	cout << "\n===========�������============" << endl;
	s.LevelOrederTraverse();
	cout << "\n===========���C�������ӽ��H============" << endl;
	BinTreeNode<char> h('H');
	s.InsertLeftChild(&c,h.Value());
	cout << "===========�������============" << endl;
	s.LevelOrederTraverse();
	cout << "\n===========�ҵ����E�ĸ����============" << endl;
	cout << s.GetParent(&e)->Value();
	cout << "\n===========ɾ�����EΪ����������============" << endl;
	s.DeleteSubTree(&e);
	cout << "===========�������============" << endl;
	s.LevelOrederTraverse();
	return 0;
}