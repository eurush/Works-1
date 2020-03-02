#include<iostream>
#include<list>
#include<queue>
#define infinity 1000000
using namespace std;
class GRAPH{
	list<pair<int,int>>* graph;
	int n;
public:
	GRAPH(int n):graph(new list<pair<int,int>>[n+1]),n(n){}
	void addEdge(int u,int v,int dist,bool ok=true){
		graph[u].push_back(make_pair(v,dist));
		if(ok==true){	
			graph[v].push_back(make_pair(u,dist));
		}
	}
	void dijktra(int start=1){
		bool visited[n+1]{true};
		int distance[n+1];
		for(int i=0;i<=n;i++){
			distance[i]=infinity;
		}
		distance[start]=0;
		queue<int> parent;
		parent.push(start);
		visited[start]=true;
		while(parent.empty()!=true){
			int here=parent.front();
			parent.pop();
			for(pair<int,int> i:graph[here]){
				if(visited[i.first]!=true){
					visited[i.first]=true;
					parent.push(i.first);
				}
				if(distance[here]>distance[i.first]+i.second){
					parent.push(here);
				}
				distance[here]=min(distance[here],distance[i.first]+i.second);
				if(distance[i.first]>distance[here]+i.second){
					parent.push(i.first);
				}
				distance[i.first]=min(distance[i.first],distance[here]+i.second);
			}
		}
		for(int i=1;i<=n;i++){
			if(i!=start){
				if(distance[i]!=infinity){
					cout<<distance[i]<<" ";
				}else{
					cout<<-1<<" ";
				}
			}
		}
		cout<<endl;
	}
};
int main(){
	int t;
	cin>>t;
	while(t--){
		int nodes,edges;
		cin>>nodes>>edges;
		GRAPH g1(nodes);
		for(int i=0;i<edges;i++){
			int u,v,dist;
			cin>>u>>v>>dist;
			g1.addEdge(u,v,dist);
		}
		int start;
		cin>>start;
		g1.dijktra(start);
	}
	return 0;
}