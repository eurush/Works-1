## COMPARING SORTING ALGORITHMS 
> **In-built sort** vs **Selection** vs **Merge** vs **Quick** vs **Heap** vs **Radix** vs **Shell**

### What has been used in implementing Comparisions

1. Used [pbPlots](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.8.0) and Wrap its functionalities in **`struct IMAGE;`**
   - It have 3 parts: 
     - Graph Settings, settings up the graph itself on which curves will appear 
       - Changing Title of X-axis, Y-axix and Title of Canvas (aka Graph paper)
       - Putting Curves into Canvas using `graph_settings->scatterPlotSeries->push_back(curves);`
       - Canvas of type `RGBABitmapImageReference *`and Graph/Curves are of type `ScatterPlotSettings *` and its `DrawScatterPlotFromSettings` function's responsibility
         to put Graph settings onto Canvas by taking Cavas and Graph.
     - Curve Settings, how curve streaks will look
       - Curve appear like `"dotted"` or `"solid"` lines or its madeof `"triangles"` or `"dots"` 
       - Curves are also of type `ScatterPlotSeries *` are stored onto `curve_settings` which is vector of type `ScatterPlotSeries *` and Curve gets created by `GetDefaultScatterPlotSeriesSettings()`
         and we change Curve settings before putting Curves onto Canvas
     - Converting .PNG Image file
       - PNG_data is of type`vector<double>`
       - using [pbPlots](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.8.0)'s function `WriteToFile(pngdata,"image.png");` to write all binary data using `fsteam` to form
         `.png` image file
2. **`struct TIMER;`** using `<chrono>` library utilities 
   - Using time point to type `::steady_clock` and `::duration` to measure difference between to `start` and `end` time points
   - TIMER starts in `constructor` and stops in `destructor`
   - Using this we can tag any scope to measure its Completion time
3. [`mt19937`](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine) engine
   - `mt19937` of `std::uint_fast32_t` result type by default (result type can be of `UIntType` type) and seed of `long` type equals to `chrono::steady_clock::now().time_since_epoch().count();` 
   -  `uniform_int_distribution<int>(1, 1e9)(mt_rng)` is used to give integer with equaly likely probability
   - [Mersenne Twister](https://en.wikipedia.org/wiki/Mersenne_Twister)
4. All sorting algorithms and TIMER are used within **`struct SORTING;`**
5. In `int main()`, an instance of `struct IMAGE;` call following functions
   - `.give_Curve(xs,ys,R,G,B,A,Thicness,"curve-line-type");` gives Curve to `curve_settings` which is array of curves 
   - `put_Curve_in_Graph();` that puts all Curves onto Canvas
   - `.image_to_png();` which gives final image
6. Final executable produced using `g++ cppfile.cpp -o  cppfile ./plots/pbPlots.cpp ./plots/supportLib.cpp -lm` and 'lm' is for including 'math' library


## Final Result

Writing Text on Canvas using `DrawText(canvas->Image_ptr, position in x, position in y, Text ptr , Color ptr)` function of `void` return type

Text of `vector<wchar_t> *text`

Color with Red, Blue, Green and Alpha of `RGBA *color` type


![image1](https://user-images.githubusercontent.com/44106871/132960273-8110015c-f4ff-4f5c-8a17-1462879b9a7b.png)

     
