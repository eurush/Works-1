#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define TEST int tt; cin>>tt; while(tt--)
#define FF first
#define SS second 
#define all(a) (a).begin(),(a).end()
#define LOWB(a,i,j,x) ( lower_bound((a).begin()+(i), (a).begin()+(j), (x)) - (a).begin()) // a[ptr]>=key
#define UPPB(a,i,j,x) ( upper_bound((a).begin()+(i), (a).begin()+(j), (x)) - (a).begin()) // just greater than key
#define UNIQ(a) (a).erase(unique((a).begin(),(a).end()),(a).end())
// -----------------------------------debugging  --------------------------------------
bool __DEBUGG=false;
template<typename T>
void debug(const T&single){
    if(!__DEBUGG)cout<<"{";
    cout<<single<<"}"; flush(cout);
    __DEBUGG=false;
}
template<typename T,typename...Paras>
void debug(const T& single,const Paras&...vals){
    if(!__DEBUGG)cout<<"{",__DEBUGG=true; 
    cout<<single<<", ";
    debug(vals...);
}
// // ----------------------------------- IO ---------------------------------------------
// //cautiously use operator overloading they are very slow, stream overloading is okay asofnow
 
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); } // base case of 1D vector
template <class T, class... D> auto vect(const T& v, int n, D... m) {       // v remains same as init value
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}
struct NFS {
  NFS() {
    cin.tie(nullptr);   ios::sync_with_stdio(false);    cout << fixed << setprecision(12);
  };
} nfs;
template <class T> static constexpr T inf = numeric_limits<T>::max() / 2;
// template<class T> using ordered_set = tree <T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
typedef long long int int64;
const int MOD=1e7+3,MOD0=998244353;
// ------------------------------------------------------------------------------------------
// #define _ <<" "<<
