template<class T>
struct SPARSETABLE{
    vt<vt<T>> table;
    function<T(T,T)> apply;
    int n,logw;
    T neut;
    SPARSETABLE(const vt<T>& a,function<T(T,T)> apply,T neut){
        this->apply = apply;
        this->neut = neut;
        this->n = SZ(a);
        this->logw = int(log2(n))+1;
        table = vect<T>(neut,n,logw);
        FOR(i,0,n)table[i][0]=a[i];
        FOR(j,1,logw){
            FOR(i,0,n){
                if(i + (1<<(j-1)) < n){
                    table[i][j]=apply(table[i][j-1],table[i+ (1<<(j-1))][j-1]);
                }
            }
        }
    }
    // [l,r] inclusive and 0idx based -----------------------
    T getO1(int l,int r){ 
        int j = int(log2(r-l+1));
        int l2 = r-(1<<j)+1;
        return apply(table[l][j],table[l2][j]);
    }
    T getOlogn(int l,int r){
        int num = r-l+1;
        T ans=neut;
        for(int i=0;num && l<=r;i++,num>>=1){
            if((num&1)==0)continue;
            int j=(1<<i);
            ans=apply(ans,table[r-j][i]);
            r-=j;
        }
        return ans;
    }
    // ----------------------------------------
    void print(){
        FOR(i,0,n){
            FOR(j,0,logw)if(table[i][j]==neut)cout<<"N ";else cout<<table[i][j]<<" ";
            cout<<"\n";
        }
    }
};
