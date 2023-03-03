// ------------------------ XOR basis ------------------------
    struct BASIS{ 
    vector<int>basis; // basis[i] = mask with HSB as i
    BASIS(int n) : basis(vect<int>(0,n)){}
    void add(int val){
        int n = (int)basis.size();
        for(int i=n-1;i>=0;i--)if((val>>i)&1){
            if(basis[i]==0){basis[i]=val;;return;}
            else val^=basis[i];
        }
        return;
    }
    bool canhave(int val){ // same as add function!
        int n = (int)basis.size();
        for(int i=n-1;i>=0;i--)if((val>>i)&1){
            if(basis[i]==0);//basis[i]=val;
            else val^=basis[i];
        }        
        return (val==0);
    }
    int minxor(int val){ // same as add function!
        int n = (int)basis.size();
        for(int i=n-1;i>=0;i--)if((val>>i)&1){
            if(basis[i]==0);//basis[i]=val;
            else val^=basis[i];    
        }        
        return (val); 
    }
    int maxxor(int val){ // same as minxor ...
        int n = (int)basis.size();
        for(int i=n-1;i>=0;i--)if(((val>>i)&1)==0){ // just this diff
            if(basis[i]==0);//basis[i]=val;
            else val^=basis[i];    
        }        
        return (val);
    }
};
