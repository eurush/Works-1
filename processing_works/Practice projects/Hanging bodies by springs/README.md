


### Multiple Bodies connected to Multiple Springs with Fixed Hinge at the Top
- Each and every Spring and Bodies is Identical
- Following variables are globally defined
    1. number of Bodies 
    2. Free Length of Spring
    3. Stiffness of Springs
- Matter.Mouse is connected to p5's Canvas DOMelement using below 2 lines

  ```
  var canvashere = createCanvas(600,600);
  Mouse.create(canvashere.elt);
  ```
  **If Mouse is not interacting then this is one quick Fix**
  
  Maybe Monitor pixel density is different from What Canvas thinks pixel density is which creates unnecessary offsets in Mouse's absolute position, 
  ```
  canvashere._pixelsState._pixelDensity = pixelDensity()
  // pixelDensity() is inbuilt function in p5 that keeps track of your Monitor pixel density
  ```
- You can also change the `stiffness` parameter between Mouse and Pulled_Body by tweaking `mouseoptions` in `function setup()`'
- Left Click to clear Traced Path 

### It should look like this
https://user-images.githubusercontent.com/44106871/131073262-23918b67-02bf-4be7-b67a-622ee1899205.mp4
