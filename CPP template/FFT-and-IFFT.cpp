int rev(int n, int log) {
  int ret = 0;
  for (int i = 0; i < log; i++) {
    if (n & (1 << i)) ret |= 1 << (log - i - 1);
  }
  return ret;
}
// during multiplication erase extra zeros at back else things go MLE or TLE!
void fft(vector<complex<double>> &a, bool invert=false) { // everything is complex number
  int n = (int) a.size();
  int log = 0;
  while (1 << log < n) log++;
  for (int i = 0; i < n; i++) if (i < rev(i, log)) swap(a[i], a[rev(i, log)]);
  for (int len = 2; len <= n; len += len) {
    double ang = 2 * pi / len * (invert ? -1 : 1);
    complex<double> wn(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      complex<double> w(1);
      for (int j = 0; j < len / 2; j++) {
        complex<double> u = a[i + j];
        complex<double> v = a[i + j + len / 2];
        a[i + j] = u + w * v;
        a[i + j + len / 2] = u - w * v;
        w *= wn;
      }
    }
  
  }
  if (invert) for (int i = 0; i < n; i++) a[i] /= n;
}

// ---------------------------------------- Old code -------------------------------------------------
template<class T>
vt<CN<double>> fft(const vt<T>&a,int n,const CN<double>& w){
    if(n==1)return vt<CN<double>>{CN<double>(a[0])};
    vt<T> aeven,aodd;
    FOR(i,0,n){
        if(i&1)aodd.pb(a[i]);
        else aeven.pb(a[i]);
    }
    vt<CN<double>> k1 = fft<T>(aeven,n/2,w*w);
    vt<CN<double>> k2 = fft<T>(aodd,n/2,w*w);
    vt<CN<double>> res(n);
    FOR(i,0,n){
        res[i] = k1[i%(n/2)] + pow(w,i)*k2[i%(n/2)];
    }
    return res;
}
template<class T>
vt<CN<double>> fft(vt<T>&a){
    int nss = 1;
    while(nss<SZ(a))nss*=2;
    a.resize(2*nss);
    CN<double> w = exp((2.0*pi*1i)/(1.0*SZ(a)));
    return fft(a,SZ(a),w);
}
vt<CN<double>> ifft(const vt<CN<double>> &a,int n,const CN<double>& w){
    if(n==1)return vt<CN<double>>{CN<double>(a[0])};
    vt<CN<double>> aeven,aodd;
    FOR(i,0,n){
        if(i&1)aodd.pb(a[i]);
        else aeven.pb(a[i]);
    }
    vt<CN<double>> k1 = ifft(aeven,n/2,w*w);
    vt<CN<double>> k2 = ifft(aodd,n/2,w*w);
    vt<CN<double>> res(n);
    FOR(i,0,n){
        res[i] = (k1[i%(n/2)] + pow(w,i)*k2[i%(n/2)]);
    }
    return res;
}
template<class T>
vt<T> ifft(vt<CN<double>>&a){
    int nss = 1;
    while(nss<SZ(a))nss*=2;
    a.resize(nss);
    CN<double> w = exp((-2.0*pi*1i)/(1.0*SZ(a)));
    vt<CN<double>> iffthere = ifft(a,SZ(a),w);
    vt<T> ans;    for(auto x : iffthere)ans.pb(x.real()/(1.0*SZ(a)));
    return ans;
}
