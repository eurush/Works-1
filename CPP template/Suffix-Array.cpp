/ -- suffix array  ---
struct SA{
    vt<int> p,c,kasai; // {p[] aka SA, c[p[i]] class which pith suff belongs to at an instant} 
    string mainstr;
    SA(string s){
        s+="$"; // ascii['$'] = 36
        mainstr = s;
        int n = (int)s.size();
        p = vect<int>(0,n);
        c = vect<int>(0,n);
        {   // step 1
            vt<pair<char,int>> a;
            for(int i=0;i<n;i++)a.push_back({s[i],i});
            sort(all(a));
            for(int i=0;i<n;i++)p[i]=a[i].SS;
            c[p[0]]=0;
            for(int i=1;i<n;i++)c[p[i]]=c[p[i-1]] + (a[i].FF==a[i-1].FF ? 0 : 1);
        }
        // ------------------- making SA ----------------------
        auto countingsort = [](vt<int>&p,vt<int>&c)->void{
            int n = (int)p.size();
            vt<int> pnew(n);
            vt<int> cnt(n);
            for(int x:c)cnt[x]++;
            vt<int> pos(n,0);
            for(int i=1;i<n;i++)pos[i]=pos[i-1]+cnt[i-1];
            for(int x:p){
                int cl = c[x];
                pnew[pos[cl]]=x;
                pos[cl]++;
            }
            p=pnew;
        };  
        int k=0;
        // vt<pair<pii,int>> a(n);
        while((1<<k)<n){
            // ------------- logarithmic -------------
            // for(int i=0;i<n;i++)a[i]={{c[i],c[(i+(1<<k))%n]},i};
            // sort(all(a));
            // for(int i=0;i<n;i++)p[i]=a[i].SS;
            // for(int i=1;i<n;i++)c[p[i]]=c[p[i-1]] + (a[i].FF==a[i-1].FF ? 0 : 1);

            // ---------------- linear ----------------
            for(int i=0;i<n;i++)p[i]=(p[i]-(1<<k)+n)%n;
            
            countingsort(p,c);
            vt<int> cnew(n);
            cnew[p[0]]=0;
            for(int i=1;i<n;i++){
                pii now = {c[p[i]],c[(p[i]+(1<<k))%n]}; 
                pii prev = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]}; 
                cnew[p[i]] = cnew[p[i-1]] + (now!=prev);
            }
            c=cnew;
            k++;   
        }

    }
    array<int,3> substringsearch(string& now){
        int n = (int)p.size();
        int pos=0,j=0,posmax=n;
        for(char c:now){
            // upperlimit ----------------------
            int step = (1<<20);
            int now=pos;
            for(;step>0;step>>=1){
                if(now+step<posmax && mainstr[(p[now+step]+j)%n]<=c)now+=step;
            }
            // if(mainstr[(p[now]+j)%n]==c)now--;
            posmax=now+1;

            // lowerlimit ---------------------
            step=(1<<20);
            for(;step>0;step>>=1){
                if(pos+step<posmax && mainstr[(p[pos+step]+j)%n]<c)pos+=step;
            }
            if(mainstr[(p[pos]+j)%n]==c)pos--;
            pos++;
            // debug(pos,posmax,j);cout<<endl;
            if(pos==posmax)return {false,pos,posmax};
            j++;
        }
        return {true,pos,posmax};
    }
    // Kasai, Arimura, Arikawa, Lee and Park
    void makekasai(){
        int n = (int)mainstr.size();
        kasai = vect<int>(0,n); // max prefix betwen pi and pi+1
        int k=0;
        for(int i=0;i<n-1;i++){
            int pi = c[i];
            int j = p[pi-1];
            while(j+k<n && i+k<n && mainstr[i+k]==mainstr[j+k])k++;
            kasai[pi-1]=k;
            k=max(k-1,0);
        }

        for(int i=0;i<n;i++)cout<<p[i]<<" ";
            cout<<"\n";
        for(int i=0;i<n-1;i++)cout<<kasai[i]<<" ";
            cout<<"\n";
        // for(int i=0;i<n;i++)cout<<p[i]<<" "<<kasai[i]<<" "<<mainstr.substr(p[i],n-p[i])<<endl;
        //     cout<<"\n";
        
    }
};
