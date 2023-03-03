// ------- rolling hash ----------
struct RollingHash { 
    vector<int64> p, pre;
    RollingHash(const string& s) {
        const int64 P = 342325337;
        int n = SZ(s);
        p.resize(n + 1);
        pre.resize(n + 1);
        p[0] = 1;
        for (int i = 0; i < n; ++i) {
            pre[i + 1] = (pre[i] * P + (s[i] - 'a'))%MOD;
            p[i + 1] = (p[i] * P)%MOD;
        }
    }
    int64 query(int L, int R) {
        return (MOD+pre[R] - (pre[L] * p[R - L])%MOD)%MOD;
    }
};

auto kmp = [](const string&s)->vector<int>{
        auto p = vect<int>(0,(int)s.size()+1);
        p[0]=-1;
        for(int i=1;i<(int)s.size()+1;i++){
            int k = p[i-1];
            while (k>=0 and s[i-1]!=s[k]) k=p[k];
            p[i]=k+1; 
        }
        return p;
    };


void manacher(string s, vector<int>& odd, vector<int>& even) { 
    int n = (int)s.size();  
    // for even center +1 to right
    odd.resize(n);
    even.resize(n);
    int L = 0, R = -1;
    for (int i = 0; i < n; ++i) {
        int k = (i > R) ? 1 : min(odd[L + R - i], R - i) + 1;
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        odd[i] = --k;
        if (R < i + k) {
            L = i - k;
            R = i + k;
        }
    }
    L = 0; R = -1;
    for (int i = 0; i < n; ++i) {
        int k = (i > R) ? 1 : min(even[L + R - i + 1], R - i + 1) + 1;
        while (i - k >= 0 && i + k - 1 < n && s[i - k] == s[i + k - 1]) k++;
        even[i] = --k;
        if (R < i + k - 1) {
            L = i - k;
            R = i + k - 1;
        }
    }
    for(char x:s)cout<<x<<" ";
        cout<<endl;
    for(int x:odd)cout<<x<<" ";
        cout<<endl;
    for(int x:even)cout<<x<<" ";
        cout<<endl;
}
