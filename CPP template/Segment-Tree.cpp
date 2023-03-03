// Still Need alot of work to generalize entier template

//1 . This one is working!


// template<class T>
struct NNN{
    int64 val;
    NNN():val(0){}
    NNN(int64 neut):val(neut){}
    static NNN minN(const NNN &e1,const NNN&e2){  return e1.val<e2.val ? e1 : e2; }
    static NNN maxN(const NNN &e1,const NNN&e2){  return e1.val>e2.val ? e1 : e2; }

    NNN& operator +=(const NNN &here){ this->val+=here.val;    return *this;}
    NNN operator +(const NNN &here){NNN ans(this->val); ans.val+=here.val;    return ans;}
    friend ostream& operator<<(ostream& out,const NNN here){    out<<here.val;  return out;}
    friend istream& operator>>(istream& in,NNN& here){    in>>here.val;  return in;}

    NNN& operator=(const NNN &here){  this->val = here.val;  return *this;}
    NNN& operator=(const int64 &here){  this->val = here;  return *this;}
    
    NNN& operator^=(const NNN &here){  this->val ^= here.val;  return *this;}
    NNN& operator^=(const int64 &here){  this->val ^= here;  return *this;}
    NNN operator^(const NNN &here){NNN ans(this->val);  ans.val ^= here.val;  return ans;}
};
struct SEGT{
/*
    Neutral element must have following propery 
        (i) apply(x,neut)=x, 
        (ii) apply(neut,neut)=neut
    Update can be done at pt or in range! and can be done according to function too!
        (i)     set(idx,    val) or    set(l,r,    val) 
        (ii) modify(idx,+-delta) or modify(l,r,+-delta)  
    Query can be done at pt or in range!
        (i) query(idx)
        (ii) query(l,r)

*/
    vt<NNN> tree;
    NNN neut;
    function<NNN(NNN,NNN)> apply;
    int n;
    SEGT(const vt<int64> &a,NNN neut,function<NNN(NNN,NNN)> apply){
        int now=1;  while(now<SZ(a))now<<=1;
        this->n = now*2;
        // debug(this->n);
        this->neut = neut;
        this->tree = vect<NNN>(neut,this->n);
        this->apply = apply;
        FOR(i,this->n/2,SZ(a) + this->n/2)tree[i] = a[i-this->n/2];
        for(int i=this->n/2-1;i>0;i--){
            tree[i] = apply(tree[2*i],tree[2*i+1]);
        }
    }
    // -------------------------1-based indexing ----------------------------------------
    void set(int idx,NNN val){
        idx+=this->n/2-1;
        tree[idx]=val;  idx>>=1;
        while(idx)tree[idx] = apply(tree[2*idx],tree[2*idx+1]),idx>>=1;
    }
    void modify(int idx,NNN delta){
        idx+=this->n/2-1;
        tree[idx]+=delta;  idx>>=1;
        while(idx)tree[idx] = apply(tree[2*idx],tree[2*idx+1]),idx>>=1;
    }
    void set(int l,int r,NNN val){// [l...r]

    }
    void modify(int l,int r,NNN delta){// [l...r]

    }
    // ------------------------------------------------------------------------
    NNN query(int idx){
        NNN ans;


        return ans;
    }
    NNN query(int l,int r,int nowl,int nowr,int idx){ // [l...r]  
        if(nowl>=l && nowr<=r){ // complete overlap
            return tree[idx];
        }
        if(nowl>r || nowr<l){ // not overlap at all
            return neut;
        }
        int mid = (nowl+nowr)>>1;
        NNN left = query(l,r,nowl,mid,2*idx);
        NNN right = query(l,r,mid+1,nowr,2*idx+1);
        return apply(left,right);
    
    }
    NNN query(int l,int r){ return query(l,r,1,this->n/2,1);}
    // -----------------------------------------------------------------
    void print(){
        int i=1;
        while(i<this->n){
            FOR(j,0,i)cout<<tree[i+j]<<" ";
            newline;
            i<<=1;
        }

    }

};




// 2. This one is under contruction. . . . . . . . . . . .


//  ------------------- stupidly complex segt template ------------------
// template<class T>
struct NNN{
    int64 val;
    int64 lazy;
    function<int64(int64,int64)>combine;
    /*
        combine() must be associative, responsible for calculating final val from lazy value
        takeLazy() only affects lazy 
    */
    // ----------------------class functions and constructors -----------------------------
    NNN():val(0),lazy(-1){}
    NNN(int64 neut1,int64 neut2,function<int64(int64,int64)>combine){
        this->val = neut1;    
        this->lazy = neut2;  
        this->combine = combine;
    }
    NNN(int64 neut):val(neut),lazy(neut){}
    NNN(int64 neut,function<int64(int64,int64)>combine):val(neut),lazy(neut),combine(combine){}
    NNN(int64 neut,int64 neut2):val(neut),lazy(neut2){}
    NNN(const NNN& neut) :val(neut.val),lazy(neut.lazy),combine(neut.combine){}
    static NNN minN(const NNN &e1,const NNN&e2){  return e1.val<e2.val ? e1 : e2; }
    static NNN maxN(const NNN &e1,const NNN&e2){  return e1.val>e2.val ? e1 : e2; }
    // -------------------------------------------------------------------------------------
    int64 ombine(int64 v1,int64 v2){return v2==-1 ? v1 : v2;}
    int64 getReady(int l,int r,int idx,NNN neut){
        this->val = this->lazy==-1 ? this->val : (r-l+1)*combine(this->val,this->lazy);
        int64 lazynow = this->lazy;
        this->lazy = neut.val;
        return lazynow;
    }
    void takeLazy(NNN laz,function<int64(int64,int64)>modifylazy){this->lazy = modifylazy(this->lazy,laz.val);}
    void takeLazy(int64 laz,function<int64(int64,int64)>modifylazy){this->lazy = modifylazy(this->lazy,laz);}
    // -------------------------------------------------------------------------------------
    NNN& operator +=(const NNN &here){ this->val+=here.val;    return *this;}
    NNN operator +(const NNN &here){NNN ans(this->val,this->lazy,here.combine); ans.val+=here.val;     return ans;}
    friend ostream& operator<<(ostream& out,const NNN here){    out<<here.val<<" "<<here.lazy;  return out;}
    // friend istream& operator>>(istream& in,NNN& here){    in>>here.val;  return in;}

    NNN& operator=(const NNN &here){
        this->val = here.val,this->lazy = here.lazy;
        if(here.combine!=nullptr)this->combine = here.combine;
        return *this;
    }
    NNN& operator=(const int64 &here){  this->val = here;  return *this;}
    
    // NNN& operator^=(const NNN &here){  this->val ^= here.val;  return *this;}
    // NNN& operator^=(const int64 &here){  this->val ^= here;  return *this;}
    // NNN operator^(const NNN &here){NNN ans(this->val);  ans.val ^= here.val;  return ans;}
};
struct SEGT{
/*

    apply()/merge() and modify() must be associative!
    Neutral element must have following propery 
        (i)     apply(x,neut)=x,        modify(x,neut)=x, 
        (ii)    apply(neut,neut)=neut   modify(neut,neut)=neut
    Update can be done at pt or in range! and can be done according to modify() function too!
        (i)     set(idx, val,modify) 
        (ii)    set(l,r, val,modify), maybe using some function! for individual positions  
    Query can be done at pt or in range!    
        (i)     query(idx)
        (ii)    query(l,r)

*/
    vt<NNN> tree;
    NNN neut,neut2;
    function<NNN(int,int)> apply;
    function<NNN(NNN,NNN)> merge;
    int n;
    SEGT(const vt<int64> &a,NNN neut,NNN neut2,function<NNN(NNN,NNN)> merge,function<int64(int64,int64)> combine){
        int now=1;  while(now<SZ(a))now<<=1;
        this->n = now*2;
        this->neut = neut;
        this->neut2 = neut2;
        this->merge = merge;
        NNN node(neut.val,neut2.val,combine);
        this->tree = vect<NNN>(node,this->n); // imp
        FOR(i,this->n/2,SZ(a) + this->n/2)tree[i] = a[i-this->n/2];
    }
    void setup(function<NNN(int,int)> apply){
        this->apply = apply;
        for(int i=this->n/2-1;i>0;i--){
            tree[i] = apply(2*i,2*i+1);
            // if(tree[i].combine==nullptr)debug(i);
        }
    }
    // -------------------------1-based indexing ----------------------------------------
    void propagate(int l,int r,int idx,function<int64(int64,int64)>modifylazy){
        int64 now = tree[idx].getReady(l,r,idx,this->neut2);
        if(2*idx>=this->n)return;
        tree[2*idx].takeLazy(now,modifylazy);
        tree[2*idx+1].takeLazy(now,modifylazy);
    }
    // works on value directly
    void set(int idx,NNN val,function<NNN(NNN,NNN)>modify){
        idx+=this->n/2-1;
        tree[idx]=modify(tree[idx],val);  idx>>=1;
        while(idx)tree[idx] = apply(2*idx,2*idx+1),idx>>=1;
    }
    // works on lazy values only, [l...r]
    void set(int l,int r,int nowl,int nowr,int idx,NNN val,function<int64(int64,int64)>modifylazy){ 
        if(nowl>=l && nowr<=r){ // complete inside
            tree[idx].takeLazy(val,modifylazy);
            propagate(nowl,nowr,idx,modifylazy);
            return;
        }   
        if(nowl>r || nowr<l)return; // no overlap
        propagate(nowl,nowr,idx,modifylazy);
        int mid = (nowl+nowr)>>1;
        set(l,r,nowl,mid,2*idx,val,modifylazy);
        set(l,r,mid+1,nowr,2*idx+1,val,modifylazy);
        tree[idx] = apply(2*idx,2*idx+1);
    }
    void set(int l,int r,NNN val,function<int64(int64,int64)>modifylazy){set(l,r,1,this->n/2,1,val,modifylazy);}
    // ------------------------------------------------------------------------
    NNN query(int l,int r,int nowl,int nowr,int idx,function<int64(int64,int64)>modifylazy){ // [l...r]  
        if(nowl>=l && nowr<=r){ // complete overlap
            propagate(nowl,nowr,idx,modifylazy);
            return tree[idx];
        }
        if(nowl>r || nowr<l){ // not overlap at all
            return neut;
        }
        propagate(nowl,nowr,idx,modifylazy);
        int mid = (nowl+nowr)>>1;
        NNN left = query(l,r,nowl,mid,2*idx,modifylazy);
        NNN right = query(l,r,mid+1,nowr,2*idx+1,modifylazy);
        return merge(left,right); // merge vs apply
    
    }
    NNN query(int l,int r,function<int64(int64,int64)>modifylazy){ return query(l,r,1,this->n/2,1,modifylazy);}
    // -----------------------------------------------------------------
    void print(){
        int i=1;
        while(i<this->n){
            FOR(j,0,i)cout<<"{"<<tree[i+j]<<"} ";
            newline;
            i<<=1;
        }
    }
};
