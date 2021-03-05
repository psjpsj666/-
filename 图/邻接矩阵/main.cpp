#include<iostream>
#include"MatrixGraph.h"
using namespace std;
int main() {
	MatrixGraph<char> graph1(1), graph2(0);
	char c;
	for (c = 'A'; c <= 'E'; c++)//创建有向图
		graph1.AddOneVertex(c);
	graph1.AddOneEdge(0, 1, 2);
	graph1.AddOneEdge(0, 2, 2);
	graph1.AddOneEdge(1, 4, 3);
	graph1.AddOneEdge(2, 0, 5);
	graph1.AddOneEdge(2, 3, 6);
	graph1.AddOneEdge(3, 0, 3);
	cout << "有向图\n";
	graph1.Print();

	cout << "广度优先遍历结果：";
	graph1.BFSTraverse(0);
	cout << endl;

	cout << "深度优先遍历结果：";
	graph1.DFSTraverse(0);
	cout << endl;
	bool visited[5] = { false };
	cout << "深度优先遍历结果DFS：";
	graph1.DFS(0,visited);
	cout << endl;

	char T1,T2;
	graph1.GetVertexValue(graph1.FindFirstEdge(0), T1);
	cout << "A的第一邻接点：" << T1<< endl;
	graph1.GetVertexValue(graph1.FindNextEdge(0, graph1.FindFirstEdge(0)),T2);
	cout << "A的第二邻接点：" << T2 << endl;
	
	cout << "有向图边数："<<graph1.EdgeNum()<<endl;

	cout << "\n删除边<2,3>：\n";
	graph1.DeleteEdge(2, 3);
	graph1.Print();
	cout << "删除下标1的顶点：\n";
	graph1.DeleteVertex(1);
	graph1.Print();
	cout << "广度优先遍历结果：";
	graph1.BFSTraverse(0);
	cout << endl;
	cout << "有向图边数：" << graph1.EdgeNum() << endl;
	cout << "深度优先遍历结果：";
	graph1.DFSTraverse(0);

	cout << "\n=======================================" << endl;

	for (c = 'A'; c <= 'E'; c++) //创建无向图
		graph2.AddOneVertex(c);
	graph2.AddOneEdge(0, 1, 2);
	graph2.AddOneEdge(0, 2, 5);
	graph2.AddOneEdge(0, 3, 3);
	graph2.AddOneEdge(1, 4, 3);
	graph2.AddOneEdge(2, 3, 6);
	cout << "\n无向图\n";
	graph2.Print();
	cout << "广度优先遍历结果：";
	graph2.BFSTraverse(0);
	cout << "\n深度优先遍历结果：";
	graph2.DFSTraverse(0);
	cout << "\n无向图边数：" << graph2.EdgeNum() << endl;
	cout << "删除下标1的顶点：\n";
	graph2.DeleteVertex(1);
	graph2.Print();
	cout << "无向图边数：" << graph2.EdgeNum() << endl;
	return 0;
}