#include<iostream>
#include"MatrixGraph.h"
using namespace std;
int main() {
	MatrixGraph<char> graph1(1), graph2(0);
	char c;
	for (c = 'A'; c <= 'E'; c++)//��������ͼ
		graph1.AddOneVertex(c);
	graph1.AddOneEdge(0, 1, 2);
	graph1.AddOneEdge(0, 2, 2);
	graph1.AddOneEdge(1, 4, 3);
	graph1.AddOneEdge(2, 0, 5);
	graph1.AddOneEdge(2, 3, 6);
	graph1.AddOneEdge(3, 0, 3);
	cout << "����ͼ\n";
	graph1.Print();

	cout << "������ȱ��������";
	graph1.BFSTraverse(0);
	cout << endl;

	cout << "������ȱ��������";
	graph1.DFSTraverse(0);
	cout << endl;
	bool visited[5] = { false };
	cout << "������ȱ������DFS��";
	graph1.DFS(0,visited);
	cout << endl;

	char T1,T2;
	graph1.GetVertexValue(graph1.FindFirstEdge(0), T1);
	cout << "A�ĵ�һ�ڽӵ㣺" << T1<< endl;
	graph1.GetVertexValue(graph1.FindNextEdge(0, graph1.FindFirstEdge(0)),T2);
	cout << "A�ĵڶ��ڽӵ㣺" << T2 << endl;
	
	cout << "����ͼ������"<<graph1.EdgeNum()<<endl;

	cout << "\nɾ����<2,3>��\n";
	graph1.DeleteEdge(2, 3);
	graph1.Print();
	cout << "ɾ���±�1�Ķ��㣺\n";
	graph1.DeleteVertex(1);
	graph1.Print();
	cout << "������ȱ��������";
	graph1.BFSTraverse(0);
	cout << endl;
	cout << "����ͼ������" << graph1.EdgeNum() << endl;
	cout << "������ȱ��������";
	graph1.DFSTraverse(0);

	cout << "\n=======================================" << endl;

	for (c = 'A'; c <= 'E'; c++) //��������ͼ
		graph2.AddOneVertex(c);
	graph2.AddOneEdge(0, 1, 2);
	graph2.AddOneEdge(0, 2, 5);
	graph2.AddOneEdge(0, 3, 3);
	graph2.AddOneEdge(1, 4, 3);
	graph2.AddOneEdge(2, 3, 6);
	cout << "\n����ͼ\n";
	graph2.Print();
	cout << "������ȱ��������";
	graph2.BFSTraverse(0);
	cout << "\n������ȱ��������";
	graph2.DFSTraverse(0);
	cout << "\n����ͼ������" << graph2.EdgeNum() << endl;
	cout << "ɾ���±�1�Ķ��㣺\n";
	graph2.DeleteVertex(1);
	graph2.Print();
	cout << "����ͼ������" << graph2.EdgeNum() << endl;
	return 0;
}