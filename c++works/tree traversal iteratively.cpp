/*
11
0 1 2 3 4 5 6 7 -1 -1 -1 8
non_negative value=values of nodes
-1 ~= null
how array is defined
{
	parent=(root-1)/2
	child_left=2*root+1
	child_right=2*root+2
}

tree representation:

			  0
		1			2
	 3	   4	 5	   6
  7


*/
#include<iostream>
#include<cmath>
using namespace std;
int give_parent(int i){
	return (i-1)/2;
}
int give_left_child(int i){
	return 2*i+1;
}
int give_right_child(int i){
	return 2*i+2;
}
void preorder(int *tree,int n){
	bool visited[n]{false};
	int root=0,c=0;
	while(c<3){
		if(root>=n || tree[root]==-1){
			if(root<n) visited[root]=true;
			root=give_parent(root);
		}
		if(root==0){
			c++;
		}
		if(visited[root]!=true){
			cout<<tree[root]<<" ";
			visited[root]=true;
			root=give_left_child(root);
		}else if((give_right_child(root)<n && visited[give_right_child(root)]==true) || (give_right_child(root)>=n && give_left_child(root)>=n)){
			root=give_parent(root);
		}else{
			root=give_right_child(root);
		}

	}
}
void inorder(int *tree,int n){
	bool visited[n]{false};
	int root=0,c=0;
	while(c<3){
		if(root>=n || tree[root]==-1){
			if(root<n) visited[root]=true;
			root=give_parent(root);
		}
		if(root==0){
			c++;
		}
		if(visited[root]!=true){
			visited[root]=true;
			root=give_left_child(root);
		}else if((give_right_child(root)<n && visited[give_right_child(root)]==true) || (give_right_child(root)>=n && give_left_child(root)>=n)){
			if((give_right_child(root)>=n && give_left_child(root)>=n))cout<<tree[root]<<" ";
			root=give_parent(root);
		}else{
			cout<<tree[root]<<" ";
			root=give_right_child(root);
		}

	}
}
void postorder(int *tree,int n){
	bool visited[n]{false};
	int root=0,c=0;
	while(c<3){
		if(root>=n || tree[root]==-1){
			if(root<n) visited[root]=true;
			root=give_parent(root);
		}
		if(root==0){
			c++;
		}
		if(visited[root]!=true){
			
			visited[root]=true;
			root=give_left_child(root);
		}else if((give_right_child(root)<n && visited[give_right_child(root)]==true) || (give_right_child(root)>=n && give_left_child(root)>=n)){
			cout<<tree[root]<<" ";
			root=give_parent(root);
		}else{
			root=give_right_child(root);
		}

	}
}
int main(){
	int n;
	cin>>n;
	int nnow=n;
	double x=log2(n+1);
	int x1=log2(n+1);
	if(x-x1!=0){
		n=pow(2,x1+1);
	}else{
		n=pow(2,x1);
	}
	int tree[n-1];
	fill(tree,tree+n-1,-1);
	for(int i=0;i<=nnow;i++){
		cin>>tree[i];
	}
	cout<<"preorder : ";
	preorder(tree,nnow);
	cout<<endl<<"postorder : ";
	postorder(tree,nnow);
	cout<<endl<<"inorder : ";
	inorder(tree,nnow);
	return 0;
}