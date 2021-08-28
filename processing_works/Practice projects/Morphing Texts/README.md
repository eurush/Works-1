## Morphing of Text
- Direct application of [Points from text](https://p5js.org/reference/#/p5.Font/textToPoints) functionanlity
- `size_slider` manages Font size and `sample_slider` manages 
- Top input is Initial String and Bottom input is Target String
- Algorithm is fairly simple 
  1. create 2 arrays that containts respective Points of Initial and Target String
  2. One extra array for mapping the indexes of Initial array to the Target array using  `map` function
     ```
     //i is the index of Initial_array 
     var idx = map(i , 0 , Initial_array.length - 1  , 0 ,  Target_array.length-1);
     ```
  3. Now create the Vector difference between `Initial_array[i]` and `Target_array[idx]`, set the Magnitute of that equals to `speed`
  4. Once the Point reaches Target position set the magnitude of difference as 0
- Simulation will run automatically when you will click one of the Input boxes with Updated parameters ( LOL there are only 2 parameters ;) )



## Result should look like this

https://user-images.githubusercontent.com/44106871/131207523-14e635e7-6a24-4e4d-b0da-e5125db167f3.mp4


Bad frameRate (ಥ⌣ಥ) 

     
     
     







