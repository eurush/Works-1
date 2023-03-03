// ------------------- functional graph ---------------------------
// with frwd[] and graph[][] list
vt<bool> visnow(n+1,false);
vt<bool> vis(n+1,false);
vt<int> clr(n+1,0); 
vt<int> clrsz(n+1,0); 
vt<int> height(n+1,0); 
vt<int> now;
vt<int> tin(n+1,0),tout(n+1,0);
vt<int> numberit(n+1,0);
vt<int> superparent(n+1,0);
int timee=0;
function<void(int,int,int,int,int)> dfs = [&](int par,int child,int col,int h,int v)->void{
    vis[child]=true;
    clr[child]=col;
    tin[child]=timee++;
    height[child]=h;
    superparent[child]=v;
    for(int kid:graph[child])if(par!=kid && clr[kid]==0){
        dfs(child,kid,col,h+1,v);
    }
    tout[child]=timee++;
};

for(int i=1,clrnow=1;i<=n;i++)if(!vis[i]){
    int u=i;
    while(!visnow[u])visnow[u]=1,now.push_back(u),u=frwd[u];
    // coloring the loops and taking sz of loop
    clr[u]=clrnow;
    int j=SZ(now)-1;
    int no=1;   
    while(j>=0 && now[j]!=u){
        int v = now[j];
        clr[v]=clrnow;
        no++;
        j--;
    }
    clrsz[clrnow]=no;
    // dfs from loops to setup height and superparent and component nodes by coloring them and numbering
    j = SZ(now)-1;
    timee=0;
    dfs(0,u,clrnow,0,u);
    while(j>=0 && now[j]!=u){
        int v = now[j];
        timee=0;
        dfs(0,v,clrnow,0,v);
        numberit[v]=no--;
        j--;
    }
    numberit[u]=no;
    // clearing now
    while(SZ(now))visnow[now.back()]=0,now.pop_back();
    clrnow++;
}
