#pragma once
#ifndef _MatrixGraph_H_
#define _MatrixGraph_H_

#include<iostream>
#include<queue>
#include<stack>

const int MAX_VERTEX_NUM = 30;    //最大顶点数
const int INFINIT = INT_MAX;      //无穷大

 //图的邻接矩阵ADT
template<class T>
class MatrixGraph {
private:
	int VertexNum;                                       //顶点数目
	int WeightMaxtix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //边上权值，邻接矩阵
	T vertex[MAX_VERTEX_NUM];                            //顶点数据集合
	int GraphType;                                       //图的类型标志，0为无向图，1为有向图
public:
	MatrixGraph(int type);                              //构造函数，生成图
	~MatrixGraph() {};                                  //析构函数
	int VertexNumber();                                 //返回顶点个数
	int EdgeNum();                                      //返回边数
	bool IsEdge(int nV1,int nV2);                       //判断顶点nV1和nV2之间是否存在边
	bool IsEmpty();                                     //判断图是否为空
	bool IsFull();                                      //判断图是否已满
	int FindFirstEdge(int nV);                          //返回顶点nV相关联的第一条边
	int FindNextEdge(int nV1,int nV2);                  //获取与指定边(nV1,nV2)或<nV1,nV2>有相同关联顶点nV1的下一条边
	bool AddOneVertex(const T &vertexvalue);            //添加一个顶点
	bool AddOneEdge(int nV1,int nV2,int weight);        //在顶点nV1和nV2之间添加一条带权的边
	bool DeleteVertex(int nV);                          //删除顶点nV
	bool DeleteEdge(int nV1,int nV2);                   //删除边(nV1,nV2)||<nV1,nV2>
	bool GetVertexValue(int nV,T&vertexvalue);          //返回顶点存储的数据
	bool GetEdgeValue(int nV1, int nV2,int &weight);    //返回边的权
	bool SetEdgeValue(int nV1,int nV2,int weight);      //设置边的权
	bool BFSTraverse(int nV);                           //广度优先遍历
	bool DFSTraverse(int nV);                           //深度优先遍历
	void DFS(int nV, bool visited[]);                   //DFSTraverse函数内部调用
	void Print() {
		//打印图中所有结点及权
		for (int n = 0; n < VertexNum; n++) {
			std::cout <<"(" <<n<<","<<vertex[n] << ") ";
		}
		std::cout << "\n";
		std::cout << "  ";
		for (int n = 0; n < VertexNum; n++) {
			std::cout << vertex[n] << " ";
		}
		std::cout << "\n";
		for (int i = 0; i < VertexNum; i++) {
			std::cout << vertex[i] << " ";
			for (int j = 0; j < VertexNum; j++) {
				if(WeightMaxtix[i][j]==INFINIT)
					std::cout << "N"<< " ";
				else
					std::cout << WeightMaxtix[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
};
//构造函数，生成图
template<class T>
MatrixGraph<T>::MatrixGraph(int type) {
	GraphType = type;
	VertexNum = 0;
	// 将任两个结点之间边上的权置为无穷大，初始时没有边
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			WeightMaxtix[i][j]=INFINIT;
}

//返回顶点个数
template<class T>
int MatrixGraph<T>::VertexNumber() {
	return VertexNum;
}

//返回边的个数
template<class T>
int MatrixGraph<T>::EdgeNum() {
	int SumEgde=0;
	for (int i = 0; i < VertexNum; i++) {
		for (int j = 0; j < VertexNum; j++) {
			if (IsEdge(i, j)) {
				SumEgde++;
			}
		}
	}
	if (GraphType == 0)//无向图
		SumEgde = SumEgde / 2;
	return SumEgde;
}

//判断顶点nV1和nV2之间是否存在边
template<class T>
bool MatrixGraph<T>::IsEdge(int nV1, int nV2) {
	//权重为有限值，则表明边存在
	return WeightMaxtix[nV1][nV2] != INFINIT;
}

//返回顶点nV相关联的第一条边
template<class T>
int MatrixGraph<T>::FindFirstEdge(int nV) {
	//判断顶点nV是否存在
	if (nV < 0 || nV >= MAX_VERTEX_NUM) 
		return -1;
	for (int i = 0; i < VertexNum; i++) {
		if (IsEdge(nV, i))   //存在边
			return i;
	}
	return -1;
}

//获取与指定边(nV1,nV2)或<nV1,nV2>有相同关联顶点nV1的下一条边
template<class T>
int MatrixGraph<T>::FindNextEdge(int nV1,int nV2) {
	if (!IsEdge(nV1, nV2))  
		return -1;
	for (int i = nV2 + 1; i < VertexNum; i++) {
		if (IsEdge(nV1, i))
			return i;
	}
	return -1;
}

//添加一个顶点
template<class T>
bool MatrixGraph<T>::AddOneVertex(const T& vertexvalue) {
	if (VertexNum >= MAX_VERTEX_NUM) 
		return false;
	vertex[VertexNum] = vertexvalue;
	VertexNum++;
	return true;
}

//添加一条边
template<class T>
bool MatrixGraph<T>::AddOneEdge(int nV1, int nV2, int weight) {
	if (nV1 < 0 || nV1 >= MAX_VERTEX_NUM || nV2 < 0 || nV2 >= MAX_VERTEX_NUM || IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = weight;
	if(GraphType==0)  //无向图
		WeightMaxtix[nV2][nV1] = weight;
	return true;
}

//判断图是否为空
template<class T>
bool MatrixGraph<T>::IsEmpty() {
	return VertexNum == 0;
}

//判断图是否已满
template<class T>
bool MatrixGraph<T>::IsFull() {
	return VertexNum == MAX_VERTEX_NUM;
}

//删除顶点nV
template<class T>
bool MatrixGraph<T>::DeleteVertex(int nV) {
	if (nV < 0 || nV >= MAX_VERTEX_NUM||IsEmpty())
		return false;
	for (int i = nV; i < VertexNum-1; i++) 
	{
		vertex[i] = vertex[i + 1];
		
		for (int j = nV; j < VertexNum-1; j++)
		{
			WeightMaxtix[i][j] = WeightMaxtix[i+1][j+1];
		}
	}
	if (nV > 0) {
		for (int i= 0; i < nV; i++) {
			for (int j = nV; j < VertexNum-1; j++) {
				WeightMaxtix[i][j] = WeightMaxtix[i][j+1];
			}
		}
		for (int k = nV; k < VertexNum - 1; k++) {
			for (int l= 0; l< nV; l++) {
				WeightMaxtix[k][l] = WeightMaxtix[k+1][l];
			}
		}
	}
	for(int m=0;m<VertexNum;m++)
		WeightMaxtix[VertexNum-1][m] = WeightMaxtix[m][VertexNum-1] = NULL;
	vertex[VertexNum-1] = NULL;
	VertexNum--;
	return true;
}

//删除边
template<class T>
bool MatrixGraph<T>::DeleteEdge(int nV1, int nV2) {
	if (!IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = INFINIT;
	if (GraphType == 0)//无向图
		WeightMaxtix[nV2][nV1] = INFINIT;
	return true;
}

//返回顶点存储的数据
template<class T>
bool MatrixGraph<T>::GetVertexValue(int nV,T&vertexvalue) {
	if (nV < 0 || nV >= MAX_VERTEX_NUM) 
		return false;
	vertexvalue = vertex[nV];
	return true;
}

//返回边的权
template<class T>
bool MatrixGraph<T>::GetEdgeValue(int nV1, int nV2, int& weight) {
	if (!IsEdge(nV1, nV2))
		return false;
	weight = WeightMaxtix[nV1][nV2];
	return true;
}

//设置边的权
template<class T>
bool MatrixGraph<T>::SetEdgeValue(int nV1, int nV2, int weight) {
	if (!IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = weight;
	return true;
}

//广度优先遍历
template<class T>
bool MatrixGraph<T>::BFSTraverse(int nV) {
	std::queue<int> q;
	int VisitVertex, Vertex, BegVertex = nV;
	T vertexvalue;
	bool Visited[MAX_VERTEX_NUM];  //记录顶点是否已访问
	if (nV < 0 || nV >= VertexNum)
		return false;
	memset(Visited,0,sizeof(Visited));
	while (1) {
		q.push(BegVertex);
		Visited[BegVertex] = true;
		while (!q.empty()) 
		{
			VisitVertex = q.front();
			q.pop();
			GetVertexValue(VisitVertex,vertexvalue);
			std::cout << vertexvalue << " ";
			Vertex = FindFirstEdge(VisitVertex);
			while (Vertex != -1) {
				if (Visited[Vertex] == false) {
					q.push(Vertex);
					Visited[Vertex] = true;
				}
				Vertex = FindNextEdge(VisitVertex,Vertex);
			}
		}
		//如果还有没有访问的顶点，若有则从该顶点开始再做广度优先遍历
		int n = BegVertex + 1;
		for (; n < VertexNum + nV; n++) {
			if (Visited[n % VertexNum] == false) {
				BegVertex = n % VertexNum;
				break;
			}
		}
		if (n == VertexNum + nV) break;
	}
	return true;
}

//深度优先遍历
template<class T>
bool MatrixGraph<T>::DFSTraverse(int nV) {
	bool Visited[MAX_VERTEX_NUM];
	if (nV < 0 || nV >= VertexNum)
		return false;
	//各顶点均设置为未访问状态
	memset(Visited,0,sizeof(Visited));
	//对于图中的每一个顶点，若为未访问状态，则从该顶点开始
	//调用DFS函数对包含该顶点的连通子图进行深度优先遍历
	for (int i = nV; i < VertexNum + nV; i++) {
		if (Visited[i % VertexNum] == false)
			DFS(i,Visited);
	}
	return true;
}
//DFSTraverse内部调用函数
template<class T>
void MatrixGraph<T>::DFS(int nV, bool Visited[]) {
	std::cout << vertex[nV]<<" ";
	Visited[nV] = true;
	//逐个获取与当前顶点相邻接的顶点，若获取到的顶点未访问
	//则调用DFS函数对包含该顶点的连通子图进行深度优先遍历
	int ver = FindFirstEdge(nV);
	while (ver != -1) {
		if (Visited[ver] ==false)
			DFS(ver,Visited);
		ver = FindNextEdge(nV,ver);
	}
}
#endif

