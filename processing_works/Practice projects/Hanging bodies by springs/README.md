### Multiple Bodies connected to Multiple Springs with Fixed Hinge at the Top
- Each and every Spring and Bodies is Identical
- You can change number of Bodies, Free Length of Spring and Stiffness of Springs
- Mouse that interacted with matterjs is connected to p5's Canvas element as

  ```
  var canvashere = createCanvas(600,600);
  Mouse.create(canvashere.elt);
  ```
  **If Mouse is not interacting then there might be issue with what your actual pixelDensity is vs What Canvas is assuming**
  ```
  canvashere._pixelsState._pixelDensity = pixelDensity()
  // pixelDensity() is inbuilt function in p5 that keeps track of your pixelDensity
  ```
- You can also change the `stiffness` parameter between Mouse and Pulled_Body by tweaking `mouseoptions` in `function setup()`
