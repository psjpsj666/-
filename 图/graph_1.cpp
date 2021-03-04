#include<iostream>
#include<queue>
using namespace std;
const int INFINIT = INT_MAX;
const int MAX_VERTEX_NUM = 30;
template<class T>
class AdjGraph
{
private:
	T m_vertex[MAX_VERTEX_NUM];    //顶点集合
	int m_nAdjMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //邻接矩阵
	int m_nVertexNum;              //顶点数目
	int m_nGraphType;              //图的类型（0：无向图，1：有向图）
public:
	AdjGraph(int nGraphType);      //创建图
	//以递归方式从下标为nV的顶点开始对图作深度优先遍历
	bool DFSTraverse(int nV,int);
	//由DFSTraverse调用以递归方式完成图的深度优先遍历
	void DFS(int nV,bool bVisited[]);
	//bool DFSTraverse(int nV);      //以非递归方式对图作深度优先遍历
	bool BFSTraverse(int nV);      //从下标为nV的顶点开始对图作广度优先遍历
	int GetVertexNum();            //获取顶点数目
	int GetFirstEdge(int nV);      //获取与指定顶点nV相关联的第一条边
	//获取与指定边(nV1,nV2)或<nV1,nV2>有相同关联顶点nV1的下一条边
	int GetNextEdge(int nV1,int nV2);
	bool AddOneVertex(const T&vertex);  //添加一个顶点
	bool AddOneEdge(int nV1,int nV2,int nWeight); //添加一条边
	bool GetVertexValue(int nV,T &vertex);        //获取一个顶点中存储的数据
	bool IsEdge(int nV1,int nV2);                 //判断一条边是否存在
	bool SetEdgeWeight(int nV1,int nV2,int nWeight); //设置一条边的权
	bool GetEdgeWeight(int nV1,int nV2,int &nWeight);//获取一条边的权
};
//创建图
template<class T>
AdjGraph<T>::AdjGraph(int nGraphType) {
	int nI, nJ;
	m_nGraphType = nGraphType;
	m_nVertexNum = 0;
	//将任两个结点之间边上的权置为无穷大，初始时没有边
	for (nI = 0; nI < MAX_VERTEX_NUM; nI++)
		for (nJ = 0; nJ < MAX_VERTEX_NUM; nJ++)
			m_nAdjMaxtrix[nI][nJ] = INFINIT;
}
//获取顶点数目
template<class T>
int AdjGraph<T>::GetVertexNum() {
	return m_nVertexNum;
}
//判断一条边是否存在
template<class T>
bool AdjGraph<T>::IsEdge(int nV1, int nV2) {
	//权重为有限值，则表明边存在
	return m_nAdjMaxtrix[nV1][nV2]!=INFINIT;
}
//获取与指定顶点nV相关联的第一条边
template<class T>
int AdjGraph<T>::GetFirstEdge(int nV) {
	int nJ;
	if (nV < 0 || nV >= m_nVertexNum)
		return -1;
	for (nJ = 0; nJ < m_nVertexNum; nJ++) {
		//找到第一条与nV相关联的边
		if (IsEdge(nV, nJ))
			return nJ;
	}
	return -1;
}
//获取与指定边有相同关联顶点nV1的下一条边的nV1外的顶点
template<class T>
int AdjGraph<T>::GetNextEdge(int nV1,int nV2) {
	int nJ;
	if (!IsEdge(nV1, nV2))
		return -1;
	//访问nV2后面的顶点，找到下一条与nV1关联的边
	for (nJ = nV2 + 1; nJ < m_nVertexNum; nJ++) {
		if (IsEdge(nV1, nJ))
			return nJ;
	}
	return -1;
}
//添加一个顶点
template<class T>
bool AdjGraph<T>::AddOneVertex(const T& vertex) {
	if (m_nVertexNum >= MAX_VERTEX_NUM)
		return false;
	m_vertex[m_nVertexNum] = vertex;
	m_nVertexNum++;
	return true;
}
//获取一个顶点中存储的数据
template<class T>
bool AdjGraph<T>::GetVertexValue(int nV, T& vertex) {
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	vertex = m_vertex[nV];
	return true;
}
//添加一条边
template<class T>
bool AdjGraph<T>::AddOneEdge(int nV1, int nV2, int nWeight) {
	//两个定点必须存在，且两个顶点间原先没有边
	if (nV1 < 0 || nV1 >= m_nVertexNum || nV2 < 0 || nV2 >= m_nVertexNum || IsEdge(nV1, nV2))
		return false;
	m_nAdjMaxtrix[nV1][nV2] = nWeight;
	if (m_nGraphType == 0) //无向图
		m_nAdjMaxtrix[nV2][nV1] = nWeight;
	return true;
}
//设置一条边的权
template<class T>
bool AdjGraph<T>::SetEdgeWeight(int nV1, int nV2, int nWeight) {
	if (!IsEdge(nV1, nV2))
		return false;
	m_nAdjMaxtrix[nV1][nV2] = nWeight;
	return true;
}
//获取一条边的权
template<class T>
bool AdjGraph<T>::GetEdgeWeight(int nV1, int nV2, int& nWeight) {
	if (!IsEdge(nV1, nV2))
		return false;
	nWeight = m_nAdjMaxtrix[nV1][nV2];
	return true;
}
//广度优先遍历
template<class T>
bool AdjGraph<T>::BFSTraverse(int nV) {
	queue<int> q;
	int nVisitVertex, nVertex, nBegVertex = nV;
	bool bVisited[MAX_VERTEX_NUM];   //记录一个顶点是否已访问
	T vertex;
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	memset(bVisited,0,sizeof(bVisited));   //各顶点均设置为未访问状态
	while (1)
	{
		q.push(nBegVertex);
		bVisited[nBegVertex] = true;
		while (!q.empty()) {
			nVisitVertex = q.front();
			q.pop();
			GetVertexValue(nVisitVertex,vertex);
			cout << vertex << " ";
			nVertex = GetFirstEdge(nVisitVertex);
			while (nVertex != -1) {
				if (bVisited[nVertex] == false) {
					q.push(nVertex);
					bVisited[nVertex] = true;
				}
				nVertex = GetNextEdge(nVisitVertex,nVertex);
			}
		}
		//如果还有没有访问的顶点，若有则从该顶点开始再做广度优先遍历
		int n = nBegVertex + 1;
		for (; n < m_nVertexNum + nV; n++) {
			if (bVisited[n % m_nVertexNum] == false) {
				nBegVertex = n % m_nVertexNum;
				break;
			}
		}
		if (n == m_nVertexNum + nV) break; //所有顶点都已被访问，退出循环
	}
	return true;
}
//以递归方式从下标为nV的顶点开始对图作深度优先遍历
template<class T>
bool AdjGraph<T>::DFSTraverse(int nV, int) {
	int nBegVertex;
	bool bVisited[MAX_VERTEX_NUM];
	//若下标为nV的顶点不存在，则遍历失败
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	//各顶点均设置为未访问状态
	memset(bVisited,0,sizeof(bVisited));
	//对于图中的每一个顶点，若为未访问状态，则从该顶点开始
	//调用DFS函数对包含该顶点的连通子图进行深度优先遍历
	for (nBegVertex = nV; nBegVertex < m_nVertexNum + nV; nBegVertex++) {
		if (bVisited[nBegVertex % m_nVertexNum] == false)
			DFS(nBegVertex,bVisited);
	}
	return true;
}
//由DFSTraverse调用以递归方式完成图的深度优先遍历
template<class T>
void AdjGraph<T>::DFS(int nV, bool bVisited[]) {
	T vertex;
	int nVertex;
	//先访问当前顶点，并将其状态设置为已访问
	GetVertexValue(nV,vertex);
	cout << vertex << " ";
	bVisited[nV] = true;
	//逐个获取与当前顶点相邻接的顶点，若获取到的顶点未访问
	//则调用DFS函数对包含该顶点的连通子图进行深度优先遍历
	nVertex = GetFirstEdge(nV);
	while (nVertex != -1) {
		if (bVisited[nVertex] == false)
			DFS(nVertex,bVisited);
		nVertex = GetNextEdge(nV,nVertex);
	}
}
int main() {
	AdjGraph<char> graph1(1), graph2(0);
	char c;
	for (c = 'A'; c <= 'E'; c++)//创建有向图
		graph1.AddOneVertex(c);
	graph1.AddOneEdge(0, 1, 2);
	graph1.AddOneEdge(0, 2, 2);
	graph1.AddOneEdge(1, 4, 3);
	graph1.AddOneEdge(2, 0, 5);
	graph1.AddOneEdge(2, 3, 6);
	graph1.AddOneEdge(3, 0, 3);
	cout << "有向图";
	cout << "广度优先遍历结果：";
	graph1.BFSTraverse(0);
	cout << endl;
	cout << "递归深度优先遍历结果：";
	graph1.DFSTraverse(0, 0);
	cout << endl;
	for (c = 'A'; c <= 'E'; c++) //创建无向图
		graph2.AddOneVertex(c);
	graph2.AddOneEdge(0, 1, 2);
	graph2.AddOneEdge(0, 2, 5);
	graph2.AddOneEdge(0, 3, 3);
	graph2.AddOneEdge(1, 4, 3);
	graph2.AddOneEdge(2, 3, 6);
	cout << "无向图";
	cout << "广度优先遍历结果：";
	graph2.BFSTraverse(0);
	cout << endl;
	cout << "递归深度优先遍历结果：";
	graph2.DFSTraverse(0, 0);
	cout << endl;
	return 0;
}