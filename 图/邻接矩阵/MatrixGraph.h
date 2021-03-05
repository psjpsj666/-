#pragma once
#ifndef _MatrixGraph_H_
#define _MatrixGraph_H_

#include<iostream>
#include<queue>
#include<stack>

const int MAX_VERTEX_NUM = 30;    //��󶥵���
const int INFINIT = INT_MAX;      //�����

 //ͼ���ڽӾ���ADT
template<class T>
class MatrixGraph {
private:
	int VertexNum;                                       //������Ŀ
	int WeightMaxtix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //����Ȩֵ���ڽӾ���
	T vertex[MAX_VERTEX_NUM];                            //�������ݼ���
	int GraphType;                                       //ͼ�����ͱ�־��0Ϊ����ͼ��1Ϊ����ͼ
public:
	MatrixGraph(int type);                              //���캯��������ͼ
	~MatrixGraph() {};                                  //��������
	int VertexNumber();                                 //���ض������
	int EdgeNum();                                      //���ر���
	bool IsEdge(int nV1,int nV2);                       //�ж϶���nV1��nV2֮���Ƿ���ڱ�
	bool IsEmpty();                                     //�ж�ͼ�Ƿ�Ϊ��
	bool IsFull();                                      //�ж�ͼ�Ƿ�����
	int FindFirstEdge(int nV);                          //���ض���nV������ĵ�һ����
	int FindNextEdge(int nV1,int nV2);                  //��ȡ��ָ����(nV1,nV2)��<nV1,nV2>����ͬ��������nV1����һ����
	bool AddOneVertex(const T &vertexvalue);            //���һ������
	bool AddOneEdge(int nV1,int nV2,int weight);        //�ڶ���nV1��nV2֮�����һ����Ȩ�ı�
	bool DeleteVertex(int nV);                          //ɾ������nV
	bool DeleteEdge(int nV1,int nV2);                   //ɾ����(nV1,nV2)||<nV1,nV2>
	bool GetVertexValue(int nV,T&vertexvalue);          //���ض���洢������
	bool GetEdgeValue(int nV1, int nV2,int &weight);    //���رߵ�Ȩ
	bool SetEdgeValue(int nV1,int nV2,int weight);      //���ñߵ�Ȩ
	bool BFSTraverse(int nV);                           //������ȱ���
	bool DFSTraverse(int nV);                           //������ȱ���
	void DFS(int nV, bool visited[]);                   //DFSTraverse�����ڲ�����
	void Print() {
		//��ӡͼ�����н�㼰Ȩ
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
//���캯��������ͼ
template<class T>
MatrixGraph<T>::MatrixGraph(int type) {
	GraphType = type;
	VertexNum = 0;
	// �����������֮����ϵ�Ȩ��Ϊ����󣬳�ʼʱû�б�
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			WeightMaxtix[i][j]=INFINIT;
}

//���ض������
template<class T>
int MatrixGraph<T>::VertexNumber() {
	return VertexNum;
}

//���رߵĸ���
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
	if (GraphType == 0)//����ͼ
		SumEgde = SumEgde / 2;
	return SumEgde;
}

//�ж϶���nV1��nV2֮���Ƿ���ڱ�
template<class T>
bool MatrixGraph<T>::IsEdge(int nV1, int nV2) {
	//Ȩ��Ϊ����ֵ��������ߴ���
	return WeightMaxtix[nV1][nV2] != INFINIT;
}

//���ض���nV������ĵ�һ����
template<class T>
int MatrixGraph<T>::FindFirstEdge(int nV) {
	//�ж϶���nV�Ƿ����
	if (nV < 0 || nV >= MAX_VERTEX_NUM) 
		return -1;
	for (int i = 0; i < VertexNum; i++) {
		if (IsEdge(nV, i))   //���ڱ�
			return i;
	}
	return -1;
}

//��ȡ��ָ����(nV1,nV2)��<nV1,nV2>����ͬ��������nV1����һ����
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

//���һ������
template<class T>
bool MatrixGraph<T>::AddOneVertex(const T& vertexvalue) {
	if (VertexNum >= MAX_VERTEX_NUM) 
		return false;
	vertex[VertexNum] = vertexvalue;
	VertexNum++;
	return true;
}

//���һ����
template<class T>
bool MatrixGraph<T>::AddOneEdge(int nV1, int nV2, int weight) {
	if (nV1 < 0 || nV1 >= MAX_VERTEX_NUM || nV2 < 0 || nV2 >= MAX_VERTEX_NUM || IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = weight;
	if(GraphType==0)  //����ͼ
		WeightMaxtix[nV2][nV1] = weight;
	return true;
}

//�ж�ͼ�Ƿ�Ϊ��
template<class T>
bool MatrixGraph<T>::IsEmpty() {
	return VertexNum == 0;
}

//�ж�ͼ�Ƿ�����
template<class T>
bool MatrixGraph<T>::IsFull() {
	return VertexNum == MAX_VERTEX_NUM;
}

//ɾ������nV
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

//ɾ����
template<class T>
bool MatrixGraph<T>::DeleteEdge(int nV1, int nV2) {
	if (!IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = INFINIT;
	if (GraphType == 0)//����ͼ
		WeightMaxtix[nV2][nV1] = INFINIT;
	return true;
}

//���ض���洢������
template<class T>
bool MatrixGraph<T>::GetVertexValue(int nV,T&vertexvalue) {
	if (nV < 0 || nV >= MAX_VERTEX_NUM) 
		return false;
	vertexvalue = vertex[nV];
	return true;
}

//���رߵ�Ȩ
template<class T>
bool MatrixGraph<T>::GetEdgeValue(int nV1, int nV2, int& weight) {
	if (!IsEdge(nV1, nV2))
		return false;
	weight = WeightMaxtix[nV1][nV2];
	return true;
}

//���ñߵ�Ȩ
template<class T>
bool MatrixGraph<T>::SetEdgeValue(int nV1, int nV2, int weight) {
	if (!IsEdge(nV1, nV2))
		return false;
	WeightMaxtix[nV1][nV2] = weight;
	return true;
}

//������ȱ���
template<class T>
bool MatrixGraph<T>::BFSTraverse(int nV) {
	std::queue<int> q;
	int VisitVertex, Vertex, BegVertex = nV;
	T vertexvalue;
	bool Visited[MAX_VERTEX_NUM];  //��¼�����Ƿ��ѷ���
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
		//�������û�з��ʵĶ��㣬������Ӹö��㿪ʼ����������ȱ���
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

//������ȱ���
template<class T>
bool MatrixGraph<T>::DFSTraverse(int nV) {
	bool Visited[MAX_VERTEX_NUM];
	if (nV < 0 || nV >= VertexNum)
		return false;
	//�����������Ϊδ����״̬
	memset(Visited,0,sizeof(Visited));
	//����ͼ�е�ÿһ�����㣬��Ϊδ����״̬����Ӹö��㿪ʼ
	//����DFS�����԰����ö������ͨ��ͼ����������ȱ���
	for (int i = nV; i < VertexNum + nV; i++) {
		if (Visited[i % VertexNum] == false)
			DFS(i,Visited);
	}
	return true;
}
//DFSTraverse�ڲ����ú���
template<class T>
void MatrixGraph<T>::DFS(int nV, bool Visited[]) {
	std::cout << vertex[nV]<<" ";
	Visited[nV] = true;
	//�����ȡ�뵱ǰ�������ڽӵĶ��㣬����ȡ���Ķ���δ����
	//�����DFS�����԰����ö������ͨ��ͼ����������ȱ���
	int ver = FindFirstEdge(nV);
	while (ver != -1) {
		if (Visited[ver] ==false)
			DFS(ver,Visited);
		ver = FindNextEdge(nV,ver);
	}
}
#endif

