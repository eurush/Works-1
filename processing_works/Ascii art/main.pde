PImage cat,cat2;
int scl=3;
int scl2=5;
ArrayList<Character> ans;
String arr="&#@%$=+*-.";
void setup(){
  size(1200,600);
  background(255);
  cat = loadImage("cat2.jpg");
  cat2 = createImage(cat.width,cat.height,RGB);
  ans = new ArrayList<Character>();
}
void draw(){
  background(255);
  scl2 = int(map(mouseX,0,width,1,20));
  scl = int(map(mouseY,0,height,1,20));
  cat.loadPixels();
  textSize(scl2);
  for(int j=0;j<cat.height;j+=scl){
    for(int i=0;i<cat.width;i+=scl){
        int idx = i +j*cat.width;
        //color c1 = cat.pixels[idx];
        float c1 = brightness(cat.pixels[idx]);
        char char1 = arr.charAt(int(map(c1,0,255,0,arr.length()-1)));
        fill(0);
        strokeWeight(4);
        text(char1,(i*scl2)/scl,(scl2*j)/scl);
    }
  }
}
