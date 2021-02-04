#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//二叉树结点类
template<class T>
class BinaryTreeNode {
	//friend class BinaryTree<T>;
private:
	T data;   //结点存储的数据
	BinaryTreeNode<T>* left, * right;   //左子树和右子树
public:
	BinaryTreeNode() :left(NULL), right(NULL) {}//无参构造函数
	BinaryTreeNode(T info, BinaryTreeNode<T>* l = NULL, BinaryTreeNode<T>* r = NULL) {
		//带参数的构造函数
		data = info; left = l; right = r;
	}
	T value()const { return data; } //返回数据域
	BinaryTreeNode<T>* leftchild()const { return left; }//返回左子树
	BinaryTreeNode<T>* rightchild()const { return right; }//返回右子树
	bool isLeaf() const {	//判定当前结点是否为叶结点,若是返回true
		return (left == NULL) && (right == NULL);
	}
};
enum Tags { Left, Right };  //枚举类型
template<class T>
class StackElement {
public:
	BinaryTreeNode<T>* pointer;
	Tags tag;
};
//二叉树类
template<class T>
class BinaryTree {
private:
	BinaryTreeNode<T>* root;    //根结点
public:
	BinaryTree() :root(NULL) {} //无参构造函数
	~BinaryTree() { DeleteBinaryTree(root); }    //析构函数
	bool isEmpty();                       //判断二叉树是否为空
	BinaryTreeNode<T>* Root() { return root; }  //返回根结点
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current); //返回父结点
	BinaryTreeNode<T>* LefTSibling(BinaryTreeNode<T>* current); //返回左兄结点
	BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current); //返回右兄结点
	void CreateTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);  //构造新树
	void PreOrder(BinaryTreeNode<T>* root);    //前序遍历二叉树或其子树，递归
	void InOrder(BinaryTreeNode<T>* root);    //中序遍历二叉树或其子树，递归
	void PostOrder(BinaryTreeNode<T>* root);    //后序遍历二叉树或其子树，递归
	void PreOrderWithoutRecursion(BinaryTreeNode<T>* root);//非递归前序周游二叉树或其子树
	void InOrderWithoutRecursion(BinaryTreeNode<T>* root);//非递归中序周游二叉树或其子树
	void PostOrderWithoutRecursion(BinaryTreeNode<T>* root);//非递归后序周游二叉树或其子树
	void LevelOrder(BinaryTreeNode<T>* root);    //按层次遍历二叉树或其子树
	void DeleteBinaryTree(BinaryTreeNode<T>* root); //删除二叉树或其子树
};
template<class T>
bool BinaryTree<T>::isEmpty() {   //判断二叉树是否为空
	return root == NULL;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current) {  //返回cuurent结点的父结点 
	using std::stack;                      //使用STL中的stack
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);                     //栈底监视哨
	while (pointer!=NULL) {
		if (current == pointer->leftchild() || current == pointer->rightchild()) {
			return pointer;                //如果current是pointer的子结点则返回
		}
		else if (pointer->rightchild() != NULL) {
			aStack.push(pointer->rightchild());
		}
		else if (pointer->leftchild() != NULL) {
			aStack.push(pointer->leftchild());
		}
		else {
			pointer = aStack.top(); 
			aStack.pop();   //获取栈顶元素
		}
	}
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::LefTSibling(BinaryTreeNode<T>* current) { //返回current结点的左兄弟结点
	BinaryTreeNode<T>* tmp;
	if (current) {
		tmp = Parent(current);
		if (tmp == NULL || current == tmp->leftchild())
		{
			//cout << current->value() << "不存在左兄弟结点" << endl;
			return NULL;
		}
		else {
			//cout << current->value() << "左兄弟结点=" << tmp->leftchild() << endl;
			return tmp->leftchild();
		}
	}
	return NULL;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::RightSibling(BinaryTreeNode<T>* current) {//返回current结点的右兄弟结点
	if (current) {
		BinaryTreeNode<T>* tmp= Parent(current);
		if (tmp == NULL || current == tmp->rightchild())
		{
			//cout << current->value() << "不存在右兄弟结点" << endl;
			return NULL;
		}
		else {
			//cout << current->value() << "右兄弟结点=" << tmp->rightchild() << endl;
			return tmp->rightchild();
		}
	}
	return NULL;
}

template<class T>
void BinaryTree<T>::CreateTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree) {
	//构造新树
	//由左子树leftTree、右子树rightTree和数据元素info创建一棵新树，根结点是info
	//其中this、leftTree、rightTree必须是不同的三棵树
	root = new BinaryTreeNode<T>(info, leftTree.root, rightTree.root);
	//leftTree.root = rightTree.root = NULL;                //原来两棵子树的根结点指空，避免访问
}

template<class T>
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root) {  //删除二叉树
	if (root) {
		DeleteBinaryTree(root->leftchild());      //递归删除左子树
		DeleteBinaryTree(root->rightchild());     //递归删除右子树
		delete root;                              //删除根结点
	}
}

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root) { //递归前序遍历二叉树
	if (root != NULL) {
		cout << root->value();
		PreOrder(root->leftchild());
		PreOrder(root->rightchild());
	}
}
template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root) {//递归中序遍历二叉树
	if (root != NULL) {
		InOrder(root->leftchild());
		cout << root->value();
		InOrder(root->rightchild());
	}
}
template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root) {//递归后序遍历二叉树
	if (root != NULL) {
		PostOrder(root->leftchild());
		PostOrder(root->rightchild());
		cout << root->value();
	}
}

template<class T>
void BinaryTree<T>::PreOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//非递归框架，前序遍历二叉树
	using std::stack;
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);              //栈底监视哨
	while (pointer) {
		cout << pointer->value();
		if (pointer->rightchild() != NULL) {
			aStack.push(pointer->rightchild());  //右孩子入栈
		}
		if (pointer->leftchild()) {
			pointer = pointer->leftchild();   //沿左路下降
		}
		else {
			//左子树访问完毕，转向访问右子树
			pointer = aStack.top();
			aStack.pop();
		}
	}
}

template<class T>
void BinaryTree<T>::InOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//非递归框架，中序遍历二叉树
	using std::stack;
	stack<BinaryTreeNode<T>*>aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer) {
		if (pointer) {
			aStack.push(pointer);   //当前结点入栈
			pointer = pointer->leftchild();
		}
		else {
			pointer = aStack.top();
			aStack.pop();
			cout << pointer->value();
			pointer = pointer->rightchild();  //转向右子树
		}
	}
}

template<class T>
void BinaryTree<T>::PostOrderWithoutRecursion(BinaryTreeNode<T>* root) {
	//非递归框架，后序遍历二叉树
	using std::stack;
	StackElement<T> element;
	stack<StackElement<T>>aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer) {
		while (pointer != NULL) {
			//沿非空指针压栈，并左路下降
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);      //将标志位为Left的结点压入栈中
			pointer = pointer->leftchild();
		}
		element = aStack.top(); aStack.pop();  //获取栈顶元素，并退栈
		pointer = element.pointer;
		if (element.tag == Left) {
			//从左子树回来
			element.tag = Right;   //置标志位为Right
			aStack.push(element);
			pointer = pointer->rightchild();
		}
		else {     //如果从右子树回来
			cout << pointer->value();    //访问当前结点
			pointer = NULL;            //置pointer指针为空，以继续弹栈
		}
	}
}

template<class T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root) {
	//层序遍历二叉树
	using std::queue;
	queue<BinaryTreeNode<T>*>aQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer)aQueue.push(pointer);   //根结点入队
	while (!aQueue.empty()) {
		//队列非空
		pointer = aQueue.front();    //取队首元素
		aQueue.pop();
		cout << pointer->value();
		if (pointer->leftchild()) {
			aQueue.push(pointer->leftchild());   //左子树进队列
		}
		if (pointer->rightchild())
			aQueue.push(pointer->rightchild());  //右子树进队列
	}
}

int main()
{
	//测试程序
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
	
	//前序遍历
	cout << "前序遍历（递归）: " << endl;
	a.PreOrder(a.Root());				//递归
	cout << endl;
	cout << "前序遍历（非递归）: " << endl;
	a.PreOrderWithoutRecursion(a.Root());//非递归
	cout << endl;
	
	//中序遍历二叉树
	cout << "中序遍历（递归）: " << endl;
	a.InOrder(a.Root());			//递归
	cout << endl;
	cout << "中序遍历（非递归）: " << endl;
	a.InOrderWithoutRecursion(a.Root());//非递归
	cout << endl;

	//后序遍历二叉树
	cout << "后序遍历（递归）: " << endl;
	a.PostOrder(a.Root());			//递归
	cout << endl;
	cout << "后序遍历（非递归）: " << endl;
	a.PostOrderWithoutRecursion(a.Root());//非递归	
	cout << endl;

	//层序遍历二叉树
	cout << "层序遍历: " << endl;
	a.LevelOrder(a.Root());
	cout << endl;

	//根结点
	cout <<"根结点="<< a.Root()->value()<<endl;
	return 0;
}