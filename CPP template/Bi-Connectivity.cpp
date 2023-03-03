// ---------------------- bi-connectivity -----------------------
// ------ articulation pts and bridges --------


vt<int>up(n+1,0),tin(n+1,0);
int timeit=1;
function<void(int,int)> dfs = [&](int par,int child)->void{
    tin[child]=timeit++;
    up[child] = tin[child];
    int kds=0;  bool arti=false; // this line is for articulation points only
    for(int kid:graph[child])if(kid!=par){
        if(tin[kid])ckmin(up[child],tin[kid]);
        else dfs(child,kid),ckmin(up[child],up[kid]),kds++,arti = arti || (up[kid]>=tin[child]);

    }
    if((arti && child!=1) || (kds>1 && child==1)){
        // its an articulation pt
    }
    if(up[child]>=tin[child] && par>0){
        // child-----par edge is the bridge  
    }
};
// ----- euler cycle ---------
vt<int>path;
void dfs(int child){
 
    for(auto &[kid, cnt] : graph[child]){
        if(cnt){
            cnt--;
            dfs(kid);
        }
    }
    path.pb(child);
}

