Variables used :
>   - `scl` to manage the resolution of ASCII image, greater the `scl` is lesser will be the resolution of ASCII image
>   
>   - `scl2` to manage the size of scale ASCII image with fixed `scl`, greater the `scl2` larger the image


ie: lesser the `scl` more character it will use to depict ASCII image and `scl2` is just for scaling image


>  - Image of `PImage` type, Available in Processing3.5.4 (used in making of this)
>   
>  - PImage[https://processing.org/reference/PImage.html] ,it allows us to read original image's pixels from `.pixels[index]` array, and 
>  returns color as `color`[https://www.processing.org/tutorials/color/] datatype and by typecasting `color` using `brightness`[https://processing.org/reference/brightness_.html] 
>  keyword we can decide which character to choose to represent that particular part of image   
>  
>  - `arr` is of `String` type, array of chars in decreasing order roughly representing how much filled_up(how many pixels they take on screen to print character)
>   characters are!!

Algorithm:
```
PImage cat;
String arr="&#@%$=+*-.";

//loading "cat1.jpg" into cat variable
//loading pixels to access them in for loops using --> .pixles[index]

for j from 0_to_imageHeight j+=scl:                            
    for i from 0_to_imageWidth i+=scl:                           
        int index = i + j*(imageWidth)
        floar brtns = brightness(cat.pixels[idx]); 
        //  - taking pixel value after every `scl` jumps on x&y axises --> thats how resolution is maintained 
        
        //  - getting pixel value at (i,j) and extracting `brightness` value which varies from 0 to 255, 0 being BLACK and 255 being WHITE )
        
        //  - map the brightness values 0 to 255 --> `arr` index values 0 to arr.length()-1 and Display the chosen character on Screen or on Console
        

```
Thats the whole Algorithm :)



Moving mouse towards left-right will increase whole image size with current resolution, moving mouse up-down will increase the resolution itself
So i have to swipe mouse diagonally to keep image with in window size

https://user-images.githubusercontent.com/44106871/127774850-03d2a7c2-9b38-49cd-ad37-a2454db24d24.mp4

