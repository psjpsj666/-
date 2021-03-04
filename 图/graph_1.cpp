#include<iostream>
#include<queue>
using namespace std;
const int INFINIT = INT_MAX;
const int MAX_VERTEX_NUM = 30;
template<class T>
class AdjGraph
{
private:
	T m_vertex[MAX_VERTEX_NUM];    //���㼯��
	int m_nAdjMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //�ڽӾ���
	int m_nVertexNum;              //������Ŀ
	int m_nGraphType;              //ͼ�����ͣ�0������ͼ��1������ͼ��
public:
	AdjGraph(int nGraphType);      //����ͼ
	//�Եݹ鷽ʽ���±�ΪnV�Ķ��㿪ʼ��ͼ��������ȱ���
	bool DFSTraverse(int nV,int);
	//��DFSTraverse�����Եݹ鷽ʽ���ͼ��������ȱ���
	void DFS(int nV,bool bVisited[]);
	//bool DFSTraverse(int nV);      //�Էǵݹ鷽ʽ��ͼ��������ȱ���
	bool BFSTraverse(int nV);      //���±�ΪnV�Ķ��㿪ʼ��ͼ��������ȱ���
	int GetVertexNum();            //��ȡ������Ŀ
	int GetFirstEdge(int nV);      //��ȡ��ָ������nV������ĵ�һ����
	//��ȡ��ָ����(nV1,nV2)��<nV1,nV2>����ͬ��������nV1����һ����
	int GetNextEdge(int nV1,int nV2);
	bool AddOneVertex(const T&vertex);  //���һ������
	bool AddOneEdge(int nV1,int nV2,int nWeight); //���һ����
	bool GetVertexValue(int nV,T &vertex);        //��ȡһ�������д洢������
	bool IsEdge(int nV1,int nV2);                 //�ж�һ�����Ƿ����
	bool SetEdgeWeight(int nV1,int nV2,int nWeight); //����һ���ߵ�Ȩ
	bool GetEdgeWeight(int nV1,int nV2,int &nWeight);//��ȡһ���ߵ�Ȩ
};
//����ͼ
template<class T>
AdjGraph<T>::AdjGraph(int nGraphType) {
	int nI, nJ;
	m_nGraphType = nGraphType;
	m_nVertexNum = 0;
	//�����������֮����ϵ�Ȩ��Ϊ����󣬳�ʼʱû�б�
	for (nI = 0; nI < MAX_VERTEX_NUM; nI++)
		for (nJ = 0; nJ < MAX_VERTEX_NUM; nJ++)
			m_nAdjMaxtrix[nI][nJ] = INFINIT;
}
//��ȡ������Ŀ
template<class T>
int AdjGraph<T>::GetVertexNum() {
	return m_nVertexNum;
}
//�ж�һ�����Ƿ����
template<class T>
bool AdjGraph<T>::IsEdge(int nV1, int nV2) {
	//Ȩ��Ϊ����ֵ��������ߴ���
	return m_nAdjMaxtrix[nV1][nV2]!=INFINIT;
}
//��ȡ��ָ������nV������ĵ�һ����
template<class T>
int AdjGraph<T>::GetFirstEdge(int nV) {
	int nJ;
	if (nV < 0 || nV >= m_nVertexNum)
		return -1;
	for (nJ = 0; nJ < m_nVertexNum; nJ++) {
		//�ҵ���һ����nV������ı�
		if (IsEdge(nV, nJ))
			return nJ;
	}
	return -1;
}
//��ȡ��ָ��������ͬ��������nV1����һ���ߵ�nV1��Ķ���
template<class T>
int AdjGraph<T>::GetNextEdge(int nV1,int nV2) {
	int nJ;
	if (!IsEdge(nV1, nV2))
		return -1;
	//����nV2����Ķ��㣬�ҵ���һ����nV1�����ı�
	for (nJ = nV2 + 1; nJ < m_nVertexNum; nJ++) {
		if (IsEdge(nV1, nJ))
			return nJ;
	}
	return -1;
}
//���һ������
template<class T>
bool AdjGraph<T>::AddOneVertex(const T& vertex) {
	if (m_nVertexNum >= MAX_VERTEX_NUM)
		return false;
	m_vertex[m_nVertexNum] = vertex;
	m_nVertexNum++;
	return true;
}
//��ȡһ�������д洢������
template<class T>
bool AdjGraph<T>::GetVertexValue(int nV, T& vertex) {
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	vertex = m_vertex[nV];
	return true;
}
//���һ����
template<class T>
bool AdjGraph<T>::AddOneEdge(int nV1, int nV2, int nWeight) {
	//�������������ڣ������������ԭ��û�б�
	if (nV1 < 0 || nV1 >= m_nVertexNum || nV2 < 0 || nV2 >= m_nVertexNum || IsEdge(nV1, nV2))
		return false;
	m_nAdjMaxtrix[nV1][nV2] = nWeight;
	if (m_nGraphType == 0) //����ͼ
		m_nAdjMaxtrix[nV2][nV1] = nWeight;
	return true;
}
//����һ���ߵ�Ȩ
template<class T>
bool AdjGraph<T>::SetEdgeWeight(int nV1, int nV2, int nWeight) {
	if (!IsEdge(nV1, nV2))
		return false;
	m_nAdjMaxtrix[nV1][nV2] = nWeight;
	return true;
}
//��ȡһ���ߵ�Ȩ
template<class T>
bool AdjGraph<T>::GetEdgeWeight(int nV1, int nV2, int& nWeight) {
	if (!IsEdge(nV1, nV2))
		return false;
	nWeight = m_nAdjMaxtrix[nV1][nV2];
	return true;
}
//������ȱ���
template<class T>
bool AdjGraph<T>::BFSTraverse(int nV) {
	queue<int> q;
	int nVisitVertex, nVertex, nBegVertex = nV;
	bool bVisited[MAX_VERTEX_NUM];   //��¼һ�������Ƿ��ѷ���
	T vertex;
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	memset(bVisited,0,sizeof(bVisited));   //�����������Ϊδ����״̬
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
		//�������û�з��ʵĶ��㣬������Ӹö��㿪ʼ����������ȱ���
		int n = nBegVertex + 1;
		for (; n < m_nVertexNum + nV; n++) {
			if (bVisited[n % m_nVertexNum] == false) {
				nBegVertex = n % m_nVertexNum;
				break;
			}
		}
		if (n == m_nVertexNum + nV) break; //���ж��㶼�ѱ����ʣ��˳�ѭ��
	}
	return true;
}
//�Եݹ鷽ʽ���±�ΪnV�Ķ��㿪ʼ��ͼ��������ȱ���
template<class T>
bool AdjGraph<T>::DFSTraverse(int nV, int) {
	int nBegVertex;
	bool bVisited[MAX_VERTEX_NUM];
	//���±�ΪnV�Ķ��㲻���ڣ������ʧ��
	if (nV < 0 || nV >= m_nVertexNum)
		return false;
	//�����������Ϊδ����״̬
	memset(bVisited,0,sizeof(bVisited));
	//����ͼ�е�ÿһ�����㣬��Ϊδ����״̬����Ӹö��㿪ʼ
	//����DFS�����԰����ö������ͨ��ͼ����������ȱ���
	for (nBegVertex = nV; nBegVertex < m_nVertexNum + nV; nBegVertex++) {
		if (bVisited[nBegVertex % m_nVertexNum] == false)
			DFS(nBegVertex,bVisited);
	}
	return true;
}
//��DFSTraverse�����Եݹ鷽ʽ���ͼ��������ȱ���
template<class T>
void AdjGraph<T>::DFS(int nV, bool bVisited[]) {
	T vertex;
	int nVertex;
	//�ȷ��ʵ�ǰ���㣬������״̬����Ϊ�ѷ���
	GetVertexValue(nV,vertex);
	cout << vertex << " ";
	bVisited[nV] = true;
	//�����ȡ�뵱ǰ�������ڽӵĶ��㣬����ȡ���Ķ���δ����
	//�����DFS�����԰����ö������ͨ��ͼ����������ȱ���
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
	for (c = 'A'; c <= 'E'; c++)//��������ͼ
		graph1.AddOneVertex(c);
	graph1.AddOneEdge(0, 1, 2);
	graph1.AddOneEdge(0, 2, 2);
	graph1.AddOneEdge(1, 4, 3);
	graph1.AddOneEdge(2, 0, 5);
	graph1.AddOneEdge(2, 3, 6);
	graph1.AddOneEdge(3, 0, 3);
	cout << "����ͼ";
	cout << "������ȱ��������";
	graph1.BFSTraverse(0);
	cout << endl;
	cout << "�ݹ�������ȱ��������";
	graph1.DFSTraverse(0, 0);
	cout << endl;
	for (c = 'A'; c <= 'E'; c++) //��������ͼ
		graph2.AddOneVertex(c);
	graph2.AddOneEdge(0, 1, 2);
	graph2.AddOneEdge(0, 2, 5);
	graph2.AddOneEdge(0, 3, 3);
	graph2.AddOneEdge(1, 4, 3);
	graph2.AddOneEdge(2, 3, 6);
	cout << "����ͼ";
	cout << "������ȱ��������";
	graph2.BFSTraverse(0);
	cout << endl;
	cout << "�ݹ�������ȱ��������";
	graph2.DFSTraverse(0, 0);
	cout << endl;
	return 0;
}