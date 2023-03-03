// ------------ Kosaraju and 2SAT ---------------
    int n,m;    cin>>n>>m;
    vt<int> in[2*m+2];
    vt<int> out[2*m+2];
 
    // 2sat -----------------------
    auto kosaraju = [&]()->vt<int>{ // need in and out edges
        vt<int> p;
        vt<bool> vis(2*m+2,false);
        vt<int> scc(2*m+2,0);
        function<void(int)> dfs1=[&](int child)->void{
            if(vis[child])return;
            vis[child]=true;
            for(int kid:out[child])dfs1(kid);
            p.pb(child);
        };
        function<void(int,int)> dfs2=[&](int child,int no)->void{
            if(vis[child])return;
            vis[child]=true;
            scc[child]=no;
            for(int kid:in[child])dfs2(kid,no);
        };
        FOR(i,1,2*m+2)if(!vis[i])dfs1(i);
        vis = vect<bool>(false,2*m+2);
        int no=1;
        for(int i=SZ(p)-1;i>=0;i--){
            if(vis[p[i]])continue;
            dfs2(p[i],no);    no++;
        }
        return scc;
    };
    auto  addedge = [&](int p1,int p2,bool np1,bool np2)->void{
        p1 = (2*p1)^np1;
        p2 = (2*p2)^np2;
        int notp1 = p1^1,notp2 = p2^1;
        // in edges notp1->p2 and notp2->p1
        in[notp1].pb(p2);
        in[notp2].pb(p1);
        // out edges just opposite
        out[p2].pb(notp1);
        out[p1].pb(notp2);
    };
    auto twosat = [&]()->vt<int>{
        vt<int> scc = kosaraju();
        // cout<<scc<<endl;
        vt<int> ans(SZ(scc)/2,-1);
        bool sat=true;
        FOR(i,1,SZ(ans)){
            if(scc[2*i]==scc[2*i+1]){ // p and ~p are in same scc
                sat=false;
                break;
            }
            ans[i] = (scc[2*i]<scc[2*i+1]);// if we got p's scc first we assign 1 else 0
        }
        if(!sat)ans.resize(0);
        return ans;
    };
    auto xored = [&](int p1,int p2)->void{ // forcing both switch to be at diff state 
        // (p1 or p2) and (~p1 or ~p2) <==> p1 xor p2
        addedge(p1,p2,false,false);
        addedge(p1,p2,true,true);
    };
    auto bindit = [&](int p1,int p2)->void{// forcing both to be at same state 
        // (p1 or ~p2) and (~p1 or p2) <==> p1 <--> p2
        addedge(p1,p2,false,true);
        addedge(p1,p2,true,false);
    };
