std::mt19937 mt_rng(std::chrono::steady_clock::now().time_since_epoch().count());
int64 randint(int64 a, int64 b) {
    return std::uniform_int_distribution<int64>(a, b)(mt_rng);
}
std::random_device rd; 
int a=0,b=1000;
auto randint = bind(uniform_int_distribution<int>(a,b),std::mt19937{rd()});



// consts
const int MOD=1e9+7,MOD1=998244353,MOD32 = 2147483647,LOG9=31,LOG6=21;
const int64 INFF = inf<int64>;
const int N=2e5+1;
// traversing cells
const int dx4[4]={-1, 0, 1, 0}, dy4[4]={0, 1, 0, -1};
const int dx8[8]={-1, -1, 0, 1, 1, 1, 0, -1}, dy8[8]={0, 1, 1, 1, 0, -1, -1, -1};
// knight moves
const int dxK[8] = {-1, +1, +2, +2, +1, -1, -2, -2},dyK[8] = {-2, -2, -1, +1, +2, +2, +1, -1};
// traveling neighbours around 2x2 cell
const int dx[12] = {0,1,2,2,2,2,1,0,-1,-1,-1,-1},dy[12] = {-1,-1,-1,0,1,2,2,2,2,1,0,-1};
// algorithms
clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

double global_dura;
struct TIMER{
  std::chrono::time_point<std::chrono::steady_clock> start,end;
  std::chrono::duration<double> duration;
  TIMER(){
    start = std::chrono::steady_clock::now();
  }

  ~TIMER(){
    end = std::chrono::steady_clock::now();
    duration = end-start;
    double in_ms = duration.count()*1000.0f;
    global_dura = in_ms;
  }
};
