#include<iostream>
#include<unordered_map>
#include<list>
#include<queue>
#define infinity 1000
using namespace std;
class GRAPH
{
	unordered_map<int,list<int>> graph;
	int cities=0;
	int least=infinity;

	queue<int> give_min_parents(int *distances,int top)
	{
		queue<int> new_paths;
		for(auto here:graph[top]){
			if(distances[here]<least){
				while(new_paths.empty()!=true){
					new_paths.pop();
				}
				new_paths.push(here);
				least=distances[here];
			}else{
				if((distances[here]==least)){
					new_paths.push(here);
				}
			}
		}
		return new_paths;
	}

	void mark_activated(queue<pair<int,int>> &activated_paths,queue<int> here,int top)
	{
		while(here.empty()!=true)
		{
			activated_paths.push(make_pair(top,here.front()));
			here.pop();
		}
	}
	void print_activated_paths(queue<pair<int,int>> activated_paths)
	{
		while(activated_paths.empty()!=true)
		{
			cout<<activated_paths.front().first<<"<-->"<<activated_paths.front().second<<"\n";
			activated_paths.pop();
		}
	}
	int num_of_paths(int *distances,int endpos)
	{
		queue<pair<int,int>> activated_paths;
		queue<int> helper;
		helper.push(endpos);
		while(helper.empty()!=true)
		{
			int top=helper.front();
			if(distances[top]==0){
				break;
			}
			helper.pop();
			queue<int> here=give_min_parents(distances,top);
			mark_activated(activated_paths,here,top);
			while(here.empty()!=true){
				helper.push(here.front());
				here.pop();
			}
		}
		print_activated_paths(activated_paths);
		cout<<"test="<<activated_paths.size()<<endl;
		return helper.size();
	}
public:
	void addedge(int u,int v,bool twoway=true)
	{
		if(graph[u].size()==0){
			cities++;
		}
		if(graph[v].size()==0){
			cities++;
		}
		graph[u].push_back(v);
		if(twoway==true){
			graph[v].push_back(u);
		}
	}
	void print_graph()
	{
		for(auto j:graph){
			cout<<j.first<<"->";
			for(auto i:j.second){
				cout<<i<<" ";
			}
			cout<<"\n";
		}
	}
	int nodes()
	{
		return cities;
	}
	void bfs(int endpos,int startpos=1)
	{
		bool visited[cities+1];
		visited[startpos]=true;
		int distances[cities+1]{-1};
		distances[startpos]=0;
		queue<int> turn;
		turn.push(startpos);

		while(turn.empty()!=true)
		{
			int top=turn.front();
			turn.pop();
			for(auto here:graph[top])
			{
				if(visited[here]==false)
				{
					visited[here]=true;
					distances[here]=distances[top]+1;
					turn.push(here);
				}
				else
				{
					distances[here]=min(distances[top]+1,distances[here]);
				}
			}
		}
		for(int i=1;i<=cities;i++)
		{
			cout<<"from "<<startpos<<" to "<<i<<"="<<distances[i]<<"\n";
		}
		cout<<"min distance="<<distances[endpos]<<endl;
		int number_of_paths=num_of_paths(distances,endpos);
		cout<<"paths="<<number_of_paths<<endl;
	}
};
int main()
{
	GRAPH g1;
	g1.addedge(1,2);
	g1.addedge(1,3);
	g1.addedge(1,4);
	g1.addedge(2,3);
	g1.addedge(3,4);
	g1.addedge(3,5);
	g1.addedge(4,5);
	g1.addedge(4,6);
	g1.addedge(5,6);
	cout<<g1.nodes()<<endl;
	g1.print_graph();
	g1.bfs(6,2);
	return 0; 
}