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
