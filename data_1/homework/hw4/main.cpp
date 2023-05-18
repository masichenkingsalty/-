#include<iostream>
#include"../../graph/graph.h"
#include<vector>
using namespace std;

void myprint(int x){
	printf("%d ",x);
}
int main()
{
	Graph g(8);
	g.add(0,1,2);
	g.add(1,2,4);
	g.add(2,1,3);
	g.add(0,2,6);
	g.add(2,4,2);
	g.add(1, 7, 1);
    g.add(2, 6, 7);
    g.add(0, 5, 7);
	
	
	cout << "DFS为: ";
    g.DFS();
    cout << endl;
	
	cout<<"BFS为：";
	g.BFS();
	cout<<endl;
	
	
	vector<int> test;
	g.dijkstra(0,test);
	cout<<"最短路径:"<<endl; 
	for(int i=0;i <test.size();i++){
		myprint(test[i]);
	}
	 cout<<endl;
	 
	cout<<"最小支撑树:"<<endl; 
	g.primMST();
	
}
