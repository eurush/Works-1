#include<iostream>
#include<vector>
#include<queue>
#define M_BIT(i) ((i+1)%2)
using namespace std;
const int frame_size=5, request_length=11,N=2e5;   
vector<queue<int>> lookup;
int page_requests[N]={1,3,5,7,2,5,6,8,9,4,2};
bool currently_in_use[N]{false};
int HIT=0;
void setup(){
	queue<int> a;
	int n=frame_size+1;
	while(n--)lookup.push_back(a);
}
void clear_R_bits(int current_page){
	bool presence=false;
	while(!lookup[2].empty()){
		int page_tmp=lookup[2].front();
		if(page_tmp!=current_page)lookup[0].push(page_tmp);
		else presence=true;
		lookup[2].pop();
	}
	if(presence)lookup[2].push(current_page);
	presence=false;
	while(!lookup[3].empty()){
		int page_tmp=lookup[3].front();
		if(page_tmp!=current_page)lookup[1].push(page_tmp);
		else presence=true;
		lookup[3].pop();
	}
	if(presence)lookup[1].push(current_page);
}
bool NRU_replacement(int current_page,int priority){
	if(currently_in_use[current_page])return false;
	for(int i=0;i<4;i++){
		if(!lookup[i].empty()){
			currently_in_use[lookup[i].front()]=false;
			lookup[i].pop();
			break;
		}
	}
	lookup[priority].push(current_page);
	return true;
}
void print_all_frames(){
	vector<queue<int>> tmp_lookup=lookup;
	for(int i=0;i<4;i++){
		// cout<<"R="<<i/2<<",M="<<(i&1)<<" [";
		while(!tmp_lookup[i].empty()){
			cout<<tmp_lookup[i].front()<<",";
			tmp_lookup[i].pop();
		}
		// cout<<"]<>";
	}
	cout<<"\n";
}
void algorithm_NRU(){
	setup();
	int frame_remains=frame_size;
	for(int i=0;i<request_length;i++){
		bool hit=false;
		if(frame_remains>0){
			int R=1,M=M_BIT(i);
			if(!currently_in_use[page_requests[i]]){
				lookup[2*R+M].push(page_requests[i]);
				currently_in_use[page_requests[i]]=true;
				HIT++;
				frame_remains--;
				print_all_frames();
			}
			// cout<<"("<<i<<","<<page_requests[i]<<")";
		}else{
			int R=1,M=M_BIT(i);
			int current_page=page_requests[i];
			hit=NRU_replacement(current_page,(2*R+M));
			if(hit)HIT++;
			clear_R_bits(current_page);
			// cout<<"("<<i<<","<<page_requests[i]<<")";
		}
		if(hit)print_all_frames();
	}
}
int main(){
	cout<<"Priorities keep changing as R bits are being cleared periodically\n";
	cout<<"Frame size = "<<frame_size<<"\nLOW priority ----> HIGH priority\n";
	algorithm_NRU();
	cout<<"Fault Rate = "<<HIT<<"/"<<request_length<<" = "<<(HIT*1.0)/request_length<<"\n";
	return 0;
}
