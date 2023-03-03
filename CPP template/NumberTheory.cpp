const long long MD = (1e9+7);
template<long long MOD=MD> struct mdint { 
    int64 d=0;
    mdint () {d=0;}
    mdint (long long _d) : d(_d%MOD){
        if(d<0) d+=MOD;
    };
    friend mdint& operator+=(mdint& a, const mdint& o) {
        a.d+=o.d; if(a.d>=MOD) a.d-=MOD;
        return a;
    }
    friend mdint& operator-=(mdint& a, const mdint& o) {
        a.d-=o.d; if(a.d<0) a.d+=MOD;
        return a;
    }
    friend mdint& operator*=(mdint& a, const mdint& o) {
        return a = mdint((int64)a.d*o.d);
    }
    mdint operator*(const mdint& o) const {
        mdint res = *this;
        res*=o;
        return res;
    }
    mdint operator+(const mdint& o) const {
        mdint res = *this;
        res+=o;
        return res;
    }
    mdint operator-(const mdint& o) const {
        mdint res = *this;
        res-=o;
        return res;
    }
    mdint operator^(long long b) const {
        mdint tmp = 1;
        mdint power = *this;
        while(b) {
            if(b&1) {
                tmp = tmp*power;
            }
            power = power*power;
            b/=2;
        }
        return tmp;
    }
    friend mdint operator/=(mdint& a, const mdint& o) {
        a *= (o^(MOD-2));
        return a;
    }
    mdint operator/(const mdint& o) {
        mdint res = *this;
        res/=o;
        return res;
    }
    bool operator==(const mdint& o) { return d==o.d;}
    bool operator!=(const mdint& o) { return d!=o.d;}
    friend istream& operator>>(istream& c, mdint& a) {return c >> a.d;}
    friend ostream& operator<<(ostream& c, const mdint& a) {return c << a.d;}
};
using  mint = mdint<MD>;

std::vector <int> prime;
bool is_composite[1000000];
void linearsieve (int n) {
  std::fill (is_composite, is_composite + n, false);
  for (int i = 2; i < n; ++i) {
    if (!is_composite[i]) prime.push_back (i);
    for (int j = 0; j < SZ(prime) && i * prime[j] < n; ++j) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

int64 power(int64 x,int y, int p){//x^y %p
    int64 res = 1;
    x = x % p;
    while(y){
        if (y & 1)res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
int64 modInverse(int64 n,int p){
    return power(n, p - 2, p);
}
int64 fac[N]{0},invfac[N]{0};
void nCrModPinit(int p=MOD){
    // keep p>N else invfact[N] will be filled with zeros
    // MOD = 1e9+7 and N is <=1e5 order
    fac[0] = 1;
    for(int i=1;i<N;i++)fac[i] = (fac[i - 1] * i) % p;
    invfac[N-1]=modInverse(fac[N-1],p);
    for(int i=N-2;i>=0;i--)invfac[i]=((i+1)*invfac[i+1])%p;
}
int64 nCrModP(int n,int r,int p=MOD){
    if(n<r || n<0 || r<0)return 0;
    return (fac[n]%p * invfac[r]%p * invfac[n-r]%p)%p;
}
int64 gcd(int64 a,int64 b){
  return b==0 ? a : gcd(b,a%b);
}
int64 gcd2(int64 a,int64 b){
    if(a==0 || b==0)return a==0 ? b : a;
    if(!(a&1 && b&1))return gcd2(a/(1+((a&1)==0)),b/(1+((b&1)==0)));
    return gcd2(min(a,b),(max(a,b)-min(a,b))>>1);
}
int64 lcm(int64 a,int64 b){
  return (a*b)/gcd(a,b);
}
int64 gcdEx (int64 a, int64 b, int64 & x, int64& y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int64 x1=0, y1=0;
    int64 d = gcdEx (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}



auto rotR = [](vt<int>&v,int step,int val,int endpos)->void{
            int pos = endpos-(find(all(v),val)-v.begin())-step-1;
            if(pos<0)pos=0;
            auto end = v.begin();   advance(end,endpos);
            rotate(v.begin(),find(all(v),val)+1,end);
            rotate(v.begin(),v.begin()+pos,end);
        };
void compressvals(vt<int>&a,int off=1){
    int n=SZ(a);
    set<int> b(all(a));
    map<int,int> mapping;
    int val=off;    for(int x:b)mapping[x]=val++;

    FOR(i,0,n)a[i]=mapping[a[i]];
}
