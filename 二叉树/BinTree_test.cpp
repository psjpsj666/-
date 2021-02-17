#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T> class BinTree;
//二叉链表结点类模板
template<class T>
class BinTreeNode{
	friend class BinTree<T>;
private:
	T data;
	BinTreeNode<T>* leftchild, * rightchild;
public:
	BinTreeNode() {          //无参构造函数
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
//二叉链表类模板
template<class T>
class BinTree {
private:
	BinTreeNode<T>* root;
public:
	BinTree();                        //创建空的二叉树
	~BinTree();                       //析构函数
	bool IsEmpty();                   //判断二叉树是否为空
	BinTreeNode<T>* CreateRoot(const T& x); //以指定元素值创建根结点
	void SetRoot(BinTreeNode<T>* node) {
		root = node;
	}
	void Clear();                     //清空二叉树
	BinTreeNode<T>* GetRoot();        //获取根结点
	//前序递归创建二叉树
//	BinTreeNode<T>* CreateTree(BinTreeNode<T>*tree,T *num,int&index);
	//将一个结点作为指定结点的左孩子插入
	BinTreeNode<T>* InsertLeftChild(BinTreeNode<T>* pNode, const T& x);
	//将一个结点作为指定结点的右孩子插入
	BinTreeNode<T>* InsertRightChild(BinTreeNode<T>* pNode, const T& x);
	//修改指定结点的元素值
	bool ModifyNodeValue(BinTreeNode<T>* pNode, const T& x);
	//获取指定结点的元素值
	bool GetNodeValue(BinTreeNode<T>*pNode,T &x);
	//获取指定结点的左孩子结点
	BinTreeNode<T>* GetLeftChild(BinTreeNode<T>*pNode);
	//获取指定结点的右孩子结点
	BinTreeNode<T>* GetRightChild(BinTreeNode<T>* pNode);
	void PreOrderTraverse(BinTreeNode<T>* pNode);           //按递归方式先序遍历
	void InOrderTraverse(BinTreeNode<T>* pNode);            //按递归方式中序遍历
	void PostOrderTraverse(BinTreeNode<T>* pNode);          //按递归方式后序遍历
	void PreOrderTraverse();                                //按非递归方式先序遍历
	void InOrderTraverse();                                 //按非递归方式中序遍历
	//void PostOrderTraverse();                              //按非递归方式后序遍历
	void LevelOrederTraverse();                             //按非递归方式逐层遍历
	//按非递归方式获取指定结点的父结点
	BinTreeNode<T>* GetParent(BinTreeNode<T>*pNode);
	//删除以指定结点为根结点的子树
	void DeleteSubTree(BinTreeNode<T>* pNode);
	//由DeleteSubTree函数调用按非递归方式删除以指定结点为根的子树
	void DeleteSubTreeNode(BinTreeNode<T>*pNode);
	//按非递归方式根据关键字查找结点
	BinTreeNode<T>* SearchByKey(const T&x);
};

//实现创建空的二叉树
template<class T>
BinTree<T>::BinTree() {
	root = NULL;         //将指向根结点的指针置为空
}

//实现以指定元素值创建根结点
template<class T>
BinTreeNode<T>* BinTree<T>::CreateRoot(const T& x) {
	if (root != NULL) {
		//若原先存在根结点，则直接将根结点的值置为x
		root->data = x;
	}
	else {
		//否则，创建一个新的结点作为根结点
		root = new BinTreeNode<T>(x);
	}
	return root;
}

//判断二叉树是否为空
template<class T>
bool BinTree<T>::IsEmpty() {
	if (root == NULL) { 
		return true;
	}
	else { 
		return false;
	}
}

//获取根结点
template<class T>
BinTreeNode<T>* BinTree<T>::GetRoot() {
	return root;
}

//将一个结点作为指定结点的左孩子插入
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

// 将一个结点作为指定结点的右孩子插入
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

//修改指定结点的元素值
template<class T>
bool BinTree<T>::ModifyNodeValue(BinTreeNode<T>* pNode,const T &x) {
	if (pNode == NULL)
		return false;
	pNode->data = x;
	return true;
}

//获取指定结点的元素值
template<class T>
bool BinTree<T>::GetNodeValue(BinTreeNode<T>* pNode, T& x) {
	if (pNode == NULL)
		return false;
	x = pNode->data;
	return true;
}

//获取指定结点的左孩子结点
template<class T>
BinTreeNode<T>* BinTree<T>::GetLeftChild(BinTreeNode<T>* pNode) {
	if (pNode == NULL)
		return false;
	return pNode->leftchild;
}

//获取指定结点的右孩子结点
template<class T>
BinTreeNode<T>* BinTree<T>::GetRightChild(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return false;
	return pNode->rightchild;
}

//按递归方式先序遍历
template<class T>
void BinTree<T>::PreOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	cout << pNode->data << " ";
	PreOrderTraverse(pNode->leftchild);
	PreOrderTraverse(pNode->rightchild);
}

//按递归方式中序遍历
template<class T>
void BinTree<T>::InOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	InOrderTraverse(pNode->leftchild);
	cout << pNode->data << " ";
	InOrderTraverse(pNode->rightchild);
}

//按递归方式后序遍历
template<class T>
void BinTree<T>::PostOrderTraverse(BinTreeNode<T>* pNode) {
	if (pNode == NULL)return;
	PostOrderTraverse(pNode->leftchild);
	PostOrderTraverse(pNode->rightchild);
	cout << pNode->data << " ";
}

//实现非递归先序遍历
//利用栈实现，栈顶元素即是下一棵要访问的子树的根结点
/*（1）将二叉树的根结点入栈
  （2）将栈顶元素出栈并访问（即先访问根结点），若栈顶元素存在右子树则将右子树根结点入栈，
       若栈顶元素存在左子树则将左子树根结点入栈
  （3）重复步骤（2），直至栈为空
  */
template<class T>
void BinTree<T>::PreOrderTraverse() {
	BinTreeNode<T>* pNode = NULL;
	stack<BinTreeNode<T>*>s;
	if (root == NULL)
		return;
	//将根结点入栈
	s.push(root);
	while (!s.empty()) {
		//栈不为空时循环
		//栈顶元素出栈并访问
		pNode = s.top();
		s.pop();
		cout << pNode->data << " ";
		//若结点存在右子树，则将右子树根结点入栈
		if (pNode->rightchild)
			s.push(pNode->rightchild);
		//若结点存在右子树，则将右子树根结点入栈
		if (pNode->leftchild)
			s.push(pNode->leftchild);
	}
}

//非递归中序遍历
template<class T>
void BinTree<T>::InOrderTraverse() {
	stack<BinTreeNode<T>*>s;
	BinTreeNode<T>* pNode = root;
	if (root == NULL)
		return;
	while (!s.empty()||pNode) {
		//当栈不为空时循环
		if (pNode) {
			s.push(pNode);   //当前结点入栈
			pNode = pNode->leftchild;
		}
		else {
			pNode = s.top();
			s.pop();    //弹出栈顶元素并访问
			cout << pNode->data << " ";
			pNode = pNode->rightchild;
		}
	}
}

//非递归后序遍历


//按非递归方式逐层遍历
/*
（1）将二叉树的根结点入队
（2）将队头元素出队并访问，若队头元素存在左子树则将左子树根结点入队，
     若队头元素存在右子树则将右子树根结点入队
（3）重复步骤（2），直至队列为空
*/
template<class T>
void BinTree<T>::LevelOrederTraverse() {
	queue<BinTreeNode<T>*> q;
	BinTreeNode<T>* pNode=NULL;
	if (root == NULL)
		return;
	q.push(root);
	while (!q.empty()) {
		pNode = q.front();     //取队首结点，并弹出访问
		q.pop();
		cout << pNode->data << " ";
		//若结点存在左子树，则将左子树根结点入队
		if (pNode->leftchild)
			q.push(pNode->leftchild);
		//若队头元素存在右子树则将右子树根结点入队
		if (pNode->rightchild)
			q.push(pNode->rightchild);
	}
}

//获取指定结点的父结点,参考层序遍历算法
template<class T>
BinTreeNode<T>* BinTree<T>::GetParent(BinTreeNode<T>* pNode) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (pNode == root)//若指定结点为根结点
		return NULL;
	if (root == NULL)//若二叉树是空树
		return NULL;
	q.push(root);  //将根结点入队
	while (!q.empty()) {    //当队列不为空时循环
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
删除以指定结点为根的子树，一方面要将子树从二叉树中删除，另一方面要将子树的结点释放
（1）将子树从二叉树中删除是通过将指定结点的双亲结点的指针置空来实现（若删除的是整颗二叉树，
     则应将根结点指针值置空）
（2）将子树中的结点释放，就是采用类似于遍历子树中所有结点的方式将各结点所占据的内存释放。
     因此，同遍历算法一样，删除子树也可以采用递归方式和非递归方式。
*/

//删除以指定结点为根的子树
template<class T>
void BinTree<T>::DeleteSubTree(BinTreeNode<T>* pNode) {
	BinTreeNode<T>* pParentNode = NULL;
	//若指定结点为空，则返回
	if (pNode == NULL)
		return;
	//若将整颗二叉树删除，则令根结点为空
	if (root == pNode)
		root = NULL;
	//否则，若指定结点存在双亲结点，则将双亲结点的左孩子或右孩子置空
	else if ((pParentNode = GetParent(pNode)) != NULL) {
		if (pNode == pParentNode->leftchild)
			pParentNode->leftchild = NULL;
		else
			pParentNode->rightchild = NULL;
	}
	//否则，指定结点不是二叉树中的结点，直接返回
	else return;
	DeleteSubTreeNode(pNode);  //调用DeleteSubTreeNode删除以pNode为根的子树
}

//由DeleteSubTree函数调用按非递归方式删除以指定结点为根的子树
template<class T>
void BinTree<T>::DeleteSubTreeNode(BinTreeNode<T>* pNode) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (pNode == NULL)
		return;
	//按非递归层次遍历的方式删除子树
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

//根据关键字查找结点，实质上就是按照魔种规律遍历二叉树的每一个结点，直到找到与关键字相匹配的结点
template<class T>
BinTreeNode<T>* BinTree<T>::SearchByKey(const T& x) {
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* pCurNode = NULL;
	if (root == NULL)
		return NULL;
	//按非递归层次遍历方式查找结点
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

//清空二叉树
template<class T>
void BinTree<T>::Clear()
{
	DeleteSubTree(root);
}

//析构函数
template<class T>
BinTree<T>::~BinTree() {
	Clear();
}

/*//前序递归创建二叉树
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
	//测试程序
	BinTree<char> s;    //生成空的二叉树
	cout << "===========开始============" << endl;
	cout << "===========判断二叉树是否为空（1为空，0为不空）============" << endl;
	cout << s.IsEmpty() << endl;
	cout << "===========开始插入结点============" << endl;
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
	cout << "===========先序遍历============" << endl;
	s.PreOrderTraverse();
	cout<< "\n===========中序遍历============" << endl;
	s.InOrderTraverse();
	cout << "\n===========后序遍历============" << endl;
	s.PostOrderTraverse(s.GetRoot());
	cout << "\n===========层序遍历============" << endl;
	s.LevelOrederTraverse();
	cout << "\n===========结点C插入左子结点H============" << endl;
	BinTreeNode<char> h('H');
	s.InsertLeftChild(&c,h.Value());
	cout << "===========层序遍历============" << endl;
	s.LevelOrederTraverse();
	cout << "\n===========找到结点E的父结点============" << endl;
	cout << s.GetParent(&e)->Value();
	cout << "\n===========删除结点E为根结点的子树============" << endl;
	s.DeleteSubTree(&e);
	cout << "===========层序遍历============" << endl;
	s.LevelOrederTraverse();
	return 0;
}
