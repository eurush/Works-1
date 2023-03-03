#include "./plots/pbPlots.hpp"
#include "./plots/supportLib.hpp"
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
using namespace std;





//  ========================   "IMAGE" WRAPPER ON TOP OF PBPLOTS   ===================================

struct IMAGE{
// INBUILT PATTERNS----------------------------------------------------------------------------------


  string line_patterns[5] = { "dotted",  "dashed",  "dotdash", "longdash", "solid"};
  string point_patterns[6] = {"triangles", "dots", "crosses","circles", "filled triangles" ,  "pixels"};



// IMPORTANT VARIABLES-------------------------------------------------------------------------------


  RGBABitmapImageReference *mainImage;
  vector<ScatterPlotSeries *>curve_settings;
  ScatterPlotSettings *graph_settings;
  int cnt=0,numberofCurves=0;
  vector<double>  *pngdata;



// CONSTRUCTOR AND BY-DEFAULT SETTINGS--------------------------------------------------------------
  

  IMAGE(int w,int h){
      this->mainImage = CreateRGBABitmapImageReference();
      this->graph_settings = GetDefaultScatterPlotSettings();
      


      // GRAPH DEFAULT SETTINGS-----------------------------------:
      
      graph_settings->width = w;
      graph_settings->height = h;
      graph_settings->autoBoundaries = true;
      graph_settings->autoPadding = true;
      graph_settings->xLabel = toVector(L"X-axis");
      graph_settings->yLabel = toVector(L"Y-axis");
      graph_settings->title  = toVector(L"No Title Given");
  }



// GRAPH REPRESENTATION SETTINGS --------------------------------------------------------------------
  


  void change_Title(string name){
    std::wstring namehere = std::wstring(name.begin(), name.end());
    this->graph_settings->title = toVector(namehere.c_str());
  }
  void change_xLabel(string name){
    std::wstring namehere = std::wstring(name.begin(), name.end());
    this->graph_settings->xLabel = toVector(namehere.c_str());
  }
  void change_yLabel(string name){
    std::wstring namehere = std::wstring(name.begin(), name.end());
    this->graph_settings->yLabel = toVector(namehere.c_str());
  }
  void put_Curve_in_Graph(){
    for(auto curves: curve_settings){
      this->graph_settings->scatterPlotSeries->push_back(curves);
    }
    DrawScatterPlotFromSettings(this->mainImage,this->graph_settings);
  }

// CURVE REPRESENTATION SETTINGS --------------------------------------------------------------------


  void change_Line_type(int line_no,int i){
    line_no = line_no%6;
    std::wstring namehere = std::wstring(this->line_patterns[line_no].begin(), this->line_patterns[line_no].end());
    this->curve_settings[i]->lineType = toVector(namehere.c_str());
  }


  void give_Curve(vector<double> &xs,vector<double> &ys,int r=0.4,int g=0.4,int b=0.4,int alpha=1,int thic=2,string name="solid" ){
    std::wstring namehere = std::wstring(name.begin(), name.end());
    this->curve_settings .push_back( GetDefaultScatterPlotSeriesSettings());
    this->curve_settings[this->numberofCurves]->xs = &xs;
    this->curve_settings[this->numberofCurves]->ys = &ys;
    this->curve_settings[this->numberofCurves]->linearInterpolation = true;
    this->curve_settings[this->numberofCurves]->lineType = toVector(namehere.c_str());
    this->curve_settings[this->numberofCurves]->lineThickness = 2;
    this->curve_settings[this->numberofCurves]->color = CreateRGBAColor(r,g,b,alpha);//GetGray(0.4);
    this->numberofCurves++;
  }



// FINAL .PNG IMAGE FILE AND DESTRUCTOR---------------------------------------------------------------


  void image_to_png(){
    this->pngdata = ConvertToPNG(this->mainImage->image);
    string namehere = "Comparision.png";
    WriteToFile(this->pngdata,namehere);
    ++this->cnt;
  }

  ~IMAGE(){
    DeleteImage(this->mainImage->image);
  }

};





//  ========================================  TIMER  ===================================================


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




//  ===============================  RANDOM NUMBER GENERATOR ========================================
// USING MERSENNE TWISTER (PRNG) AS 32bit UINT OUTPUT 


auto seed = chrono::steady_clock::now().time_since_epoch().count();
int fixseed = 1;

mt19937 mt_rng(seed);


int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(mt_rng);
}






// ================================  SORTING AND BENCH MARKING   =====================================
// selection, merge, quick, heap, radix, shell, inbuilt _____ Sortings
//    ✔         ✔      ✔     ✔      ✔      ✔       ✔       


struct SORTING{
  vector<double> xs,xs2;
  vector<double> ys[7];
  int n=40;
  double a,r;


// ----------------------------  CONSTRUCTOR   ---------------------------------- 
  SORTING(double a,double r){
    this->a = a;
    this->r = r;
    for(int i=0;i<=n;i++){
      xs.push_back(int(a*pow(r,i))*1.0f);
      if(i<=n*0.66)xs2.push_back(int(a*pow(r,i))*1.0f);
    }
  }



//  ----------------------------  INBUILT SORT  ---------------------------------
  void sort_inbuilt(){
    cout<<"Onto Inbuilt sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ---------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------
        
        TIMER timer;
        sort(values.begin(),values.end());

      }//--------------------TIMED SCOPE  END --------------------------------
      
      ys[0].push_back(global_dura);
      values.clear();
    }//----------------------- END OF LOOP   --------------------------------->
    cout<<". . .Inbuilt sort DONE\n\n";
  }





// ------------------------------  MERGE SORT  -----------------------------------

  void merge(vector<int>&array, int const left, int const mid, int const right)
  {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
      *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)leftArray[i] = array[left + i];

    for (auto j = 0; j < subArrayTwo; j++)rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, 
      indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left; 
    
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
      if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
      }else {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
      }
      indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
      indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
      indexOfMergedArray++;
    }
  }

  void mergeSort(vector<int>&array, int const begin, int const end){
    if (begin >= end)return;
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
  }

  void sort_merge(){
    cout<<"Onto Merge sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        mergeSort(values, 0, values.size() - 1);

      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[1].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Merge sort DONE\n\n";
  }





//  ---------------------------  QUICK SORT  ------------------------------------

  int partition (vector<int> &arr, int low, int high)
  {
    int pivot = arr[high];
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++){
      if (arr[j] < pivot){
        i++;
        swap(arr[i], arr[j]);
      }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
  }
  void quickSort(vector<int> &arr, int low, int high){
    if (low < high){
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
    }
  }
  void sort_quick(){

    cout<<"Onto Quick sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        quickSort(values,0,values.size()-1);

      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[2].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Quick sort DONE\n\n";
  }




//-----------------------------  HEAP SORT  ---------------------------------------  



  void heapify(vector<int> &arr, int n, int i){
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < n && arr[l] > arr[largest])
      largest = l;

    if (r < n && arr[r] > arr[largest])
      largest = r;

    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
  }

  void heapSort(vector<int> &arr, int n){
    for (int i = n / 2 - 1; i >= 0; i--)heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
      swap(arr[0], arr[i]);
      heapify(arr, i, 0);
    }
  }

  void sort_heap(){
    cout<<"Onto Heap sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        heapSort(values,values.size());
        

      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[3].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Heap sort DONE\n\n";
  
  }






// -----------------------------  RADIX SORT  --------------------------------
 

  int getMax(vector<int>& arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++){
      if (arr[i] > mx)mx = arr[i];
    }
    return mx;
  }

  void countSort(vector<int>& arr, int n, int exp){
    int output[n]; 
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
      output[count[(arr[i] / exp) % 10] - 1] = arr[i];
      count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)arr[i] = output[i];
  }

  void radixsort(vector<int>& arr, int n){
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)countSort(arr, n, exp);
  }

  void sort_radix(){
    cout<<"Onto Radix sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        radixsort(values,values.size());
        
      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[4].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Radix sort DONE\n\n";
  
  }



// -----------------------------  SHELL SORT  --------------------------------


  int shellSort(vector<int>& arr, int n)
  {
    for (int gap = n/2; gap > 0; gap /= 2){
      for (int i = gap; i < n; i += 1){
        int temp = arr[i];
          int j;    
        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)arr[j] = arr[j - gap];
        arr[j] = temp;
      }
    }
    return 0;
  }

 void sort_shell(){
    cout<<"Onto Shell sort. . .\n";
    vector<int> values;
    for(int N:xs){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        shellSort(values,values.size());    

      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[5].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Shell sort DONE\n\n";
  
  }



//  ----------------------------- SELECTION SORT  --------------------------------

  void selectionSort(vector<int> &arr, int n)
  {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
      min_idx = i;
      for (j = i+1; j < n; j++)
      if (arr[j] < arr[min_idx])min_idx = j;
      swap(arr[min_idx], arr[i]);
    }
  }

  void sort_selection(){
    cout<<"Onto Selection sort. . .\n";
    vector<int> values;
    for(int N:xs2){//--------- START OF LOOP ------------------------------->
      for(int i=N-1;i>=0;i--){
        values.push_back(randint(1,1e9));
      }

      {//--------------------TIMED SCOPE START------------------------------
        TIMER timer;

        selectionSort(values,values.size());
      
      }//--------------------TIMED SCOPE  END ------------------------------
      
      ys[6].push_back(global_dura);
      values.clear();
    
    }//----------------------- END OF LOOP   --------------------------->
    cout<<". . .Selection sort DONE\n\n";
  
  }


};



// ===================================  MAIN FUNCTION  ==============================================
int main(){
  
// NECESSARY DATA NEEDED-----------------------------------
  IMAGE  img1(1000,600);
  SORTING s1(10.0,1.33351);

  






  cout<<"COMPILING RESOURCES DONE.\n\n";

  // PROCESS-----------------------------------------------

  s1.sort_inbuilt();
  s1.sort_merge();
  s1.sort_quick();
  s1.sort_heap();
  s1.sort_radix();
  s1.sort_shell();
  s1.sort_selection();
  



  // ADDING CURVES;----------------------------------------
  
  img1.give_Curve(s1.xs,s1.ys[0],1,0,0,1,2,"dotdash");
  img1.give_Curve(s1.xs,s1.ys[1],0,1,0,1,2,"dotdash");
  img1.give_Curve(s1.xs,s1.ys[2],0,0,1,1,2,"dotdash");
  img1.give_Curve(s1.xs,s1.ys[3],1,1,0,1,2,"dotdash");
  img1.give_Curve(s1.xs,s1.ys[4],0,1,1,1,2,"dotdash");
  img1.give_Curve(s1.xs,s1.ys[5],1,0,1,1,2,"dotdash");
  img1.give_Curve(s1.xs2,s1.ys[6],0,0,0,1,2,"dotdash");





  

  // GRAPH SETTINGS----------------------------------------
  img1.change_Title("In TIME vs N");
  img1.change_xLabel("N - no. of elements");
  img1.change_yLabel("T - in MilliSeconds");






 

  // RUN ONCE ---------------------------------------------
  img1.put_Curve_in_Graph();
  int yoff = 5,xoff=100,dely=15,delyx = 170;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Red  : inbuilt "),GetBlack()); yoff+=dely;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Green: merge   "),GetBlack());yoff+=dely;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Blue : quick "),GetBlack());yoff+=dely;
  yoff=5; xoff+=delyx;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Yellow  : heap "),GetBlack());yoff+=dely;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Sky Blue: radix "),GetBlack());yoff+=dely;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Purple  : Shell "),GetBlack());yoff+=dely;
  DrawText(img1.mainImage->image,xoff,yoff,toVector(L"Black   : Selection "),GetBlack());yoff+=dely;
  img1.image_to_png();
  cout<<"DONE"<<endl;
  return 0;
}
