#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T> class BST;
//BST结点
template<class T>
class BSTNode {
	friend class BST<T>;
private:
	T data;    //结点数据
	BSTNode<T>* left, * right;     //左右子树
public:
	BSTNode():left(NULL),right(NULL){}   //无参构造函数
	BSTNode(const T& x) { data = x; }    //有参构造函数
	BSTNode(const T &info, BSTNode<T> *l, BSTNode<T> *r):data(info),left(l),right(r){}   //有参构造函数
	T Value() const{ return data; }  //返回结点值
	BSTNode<T>* leftchild() const{ return left; }  //返回左子树
	BSTNode<T>* rightchild()const { return right; }//返回右子树
	void setValue(const T& value) {           //设置结点元素值
		data = value;
	}
	void Display(int i) {
		cout << "( " << i << "," << data << ")\n";
		if (left)left->Display(2*i+1);
		if (right)right->Display(2*i+2);
	}
};
//BST模板
template<class T>
class BST {
private:
	BSTNode<T>* root;                         //根结点
public:
	BST() { root = NULL; }                    //构造函数
	~BST() { Clear(root); }                   //析构函数
	BSTNode<T>* Root() { return root; }       //返回根结点
	bool isEmpty();                           //判断是否为空
	bool isBST(BSTNode<T>* root);             //判断是否为二叉搜索树
	BSTNode<T>* Parent(BSTNode<T>* node);     //返回结点node的父结点
	bool Insert(BSTNode<T> *node);            //插入
	void Remove(BSTNode<T>* node);            //删除操作
	BSTNode<T>* Search(const T val);          //查找
	void PreTravesal(BSTNode<T>* root);       //前序遍历
	void InTravesal(BSTNode<T>* root);        //中序遍历
	void PostTravesal(BSTNode<T>* root);      //后序遍历
	void PlaneTravesal(BSTNode<T>* root);     //层序遍历
	void Clear(BSTNode<T>* root);             //清空二叉树
};
template<class T>
bool BST<T>::isEmpty() {
	//判断BST是否为空
	return root == NULL;
}
template<class T>
bool BST<T>::isBST(BSTNode<T>* root) {
	//判断是否为BST
	if (root==NULL) {    //空树也为BST
		return true; 
	}
	BSTNode<T>* pointer = root;
	if (pointer) {
		if (pointer->left&&pointer->right) {                     //同时存在左右孩子结点
			if (pointer->data > pointer->left->data && pointer->data < pointer->right->data) {
				isBST(pointer->left);
				isBST(pointer->right);
			}
		}
		else if (pointer->left && !pointer->right)               //只存在左孩子结点
		{
			if(pointer->data>pointer->left->data)
				isBST(pointer->left);
		}
		else if (!pointer->left && pointer->right)               //只存在右孩子结点
		{
			if (pointer->data < pointer->right->data)
				isBST(pointer->right);
		}
		else return false;
	}
	return true;
}
template<class T>
BSTNode<T>* BST<T>::Parent(BSTNode<T>*node) {    //寻找结点node的父结点
	/*stack<BSTNode<T>*> aStack;
	BSTNode<T>* pointer=root;
	aStack.push(NULL);       //栈底监视哨
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
	if (NULL == root)   //树为空
		return NULL;
	if (node == NULL)     //结点为空
		return NULL;
	q.push(root);
	while (!q.empty()) {
		//当队列不为空时循环
		temp = q.front();
		q.pop();                //取队首元素
		if (temp->left == node || temp->right == node)
			return temp;
		if (temp->left)q.push(temp->left);
		if (temp->right)q.push(temp->right);
	}
	return NULL;
}
template<class T>
bool BST<T>::Insert(BSTNode<T>* node) {
	//在二叉搜索树中插入新结点
	//如果二叉树查找树为空节点，则插入节点就为根节点
	//如果二叉查找树为非空节点，就需要先找到待插入节点，查找原则就是从根节点开始，如果大于根就右边走，小于根就左边走，直到找到合适节点，
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
		temp = pointer;               //temp存储父结点
		if (node->data == pointer->data)return false;   //结点重复，不能插入
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
	//删除二叉树中的结点node
	//如果节点没有子女，修改其父节点指针为NULL，删除即可
    //如果该节点有左孩子情况，修改其父亲节点的指针和其左孩子的parent指针即可
    //如果该节点有右孩子情况，修改其父亲节点的指针和其右孩子的parent指针即可
    //如果同时有左右孩子的情况，情况比较复杂，一般有2种方法处理
        //(1)用节点右边孩子的最小值替换该节点，其他节点位置保持不变
	    //(2)用节点左边孩子的最大值替换该节点，其他节点位置保持不变
	BSTNode<T>* temp = NULL;
	if (node==NULL)            //删除结点是空结点
		return;
	BSTNode<T>* parent = Parent(node);
	if (node->left == NULL) {
		//被删结点无左子树，则将其右子树的根代替该删除结点
		if (parent == NULL)   //删除结点为根结点
			root = node->right;
		else if (parent->left == node)
			parent->left = node->right;
		else
			parent->right = node->right;
		delete node;        //删除该结点
		node = NULL;
		return;
	}
	else {
		//左子树不空
		temp = node->left;
		while (temp->right)//在左子树中找对称序的最后一个结点
			temp = temp->right;
		//被删除结点的右子树作为temp的右子树
		temp->right = node->right;
		//被删除结点的左子树根代替被删除结点
		if (parent == NULL) root = node->left;
		else if (parent->left == node)parent->left = node->left;
		else parent->right = node->left;
		delete node;
		node = NULL;
		return;
	}
}
template<class T>
BSTNode<T>* BST<T>::Search(const T val) {          //查找元素值为val的结点
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
	return NULL;       //没有找到
}
template<class T>
void BST<T>::Clear(BSTNode<T>* root) {
	//清空二叉树
	if (root) {
		Clear(root->leftchild());
		Clear(root->rightchild());
		delete root;
	}
}
template<class T>
void BST<T>::PreTravesal(BSTNode<T>* root) {
	//前序遍历
	BSTNode<T>* pointer = root;
	if (pointer) {
		cout << pointer->Value() << " ";
		PreTravesal(pointer->leftchild());
		PreTravesal(pointer->rightchild());
	}
}
template<class T>
void BST<T>::InTravesal(BSTNode<T>* root) {
	//中序遍历
	BSTNode<T>* pointer = root;
	if (pointer) {
		InTravesal(pointer->leftchild());
		cout << pointer->Value() << " ";
		InTravesal(pointer->rightchild());
	}
}
template<class T>
void BST<T>::PostTravesal(BSTNode<T>* root) {
	//后序遍历
	BSTNode<T>* pointer = root;
	if (pointer) {
		PostTravesal(pointer->leftchild());
		PostTravesal(pointer->rightchild());
		cout << pointer->Value() << " ";
	}
}
template<class T>
void BST<T>::PlaneTravesal(BSTNode<T>* root) {
	//层序遍历
	queue<BSTNode<T>*> aQueue;
	BSTNode<T>* pointer = root;
	if (pointer)aQueue.push(pointer);  //根结点入队
	while (!aQueue.empty()) {
		//队列非空
		pointer = aQueue.front();     //取队首结点
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
	//测试
	BST<int> BT;  //调用无参构造函数，生成空的二叉树
	cout << "=========判断二叉树是否为空(1为空，0为不空)=========" << endl;
	cout << BT.isEmpty() << endl;
	cout << "=========二叉树插入=========" << endl;
	int ELE[6] = {50,28,5,62,88,45};
	BSTNode<int> Node[6];
	for (int i = 0; i < 6; i++) {
		Node[i].setValue(ELE[i]);
		BT.Insert(&Node[i]);
	}
	Node[0].Display(0);

	cout << "=========前序遍历=========" << endl;
	BT.PreTravesal(BT.Root());
	cout << "\n=========中序遍历=========" << endl;
	BT.InTravesal(BT.Root());
	cout << "\n=========后序遍历=========" << endl;
	BT.PostTravesal(BT.Root());
	cout << "\n=========层序遍历=========" << endl;
	BT.PlaneTravesal(BT.Root());
	cout << "\n=========判断二叉树是否为二叉搜索树=========" << endl;
	cout << BT.isBST(BT.Root()) << endl;
	cout << "=========插入72=========" << endl;
	BSTNode<int> p(72);
	BT.Insert(&p);
	cout << "=========层序遍历=========" << endl;
	BT.PlaneTravesal(BT.Root());
	
	cout << "\n=========结点88的父结点=========" << endl;
	cout << BT.Parent(&Node[4])->Value();
	cout << "\n=========删除28=========" << endl;
	BT.Remove(&Node[1]);
	cout << "=========层序遍历=========" << endl;
	BT.PlaneTravesal(BT.Root());
	return 0;
}