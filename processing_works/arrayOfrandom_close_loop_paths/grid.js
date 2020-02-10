int loc(int i,int j){/////////////////gives location of slab in arrayof slab i,j as raw co-orinates
  return i+h*j;
}
class grid{
  int coldefault=100;/////////////////////////////////color of slab R=G=B=100
  ArrayList<slab> s1=new ArrayList<slab>();//////////slab=square on grid (tab koi naam nahi click kiya ye he rakh diya)
  grid(){
    for(int j=0;j<h;j++){
       for(int i=0;i<h;i++){
         s1.add(new slab(i*s,s*j,s));
       }
    }
  }
  void display(){
   for(int j=0;j<h;j++){
     for(int i=0;i<h;i++){
       //int n=int(map(noise(i,j),0,1,0,255));
       s1.get(loc(i,j)).display(255);
     }
    }
    //drawshape();
  }
  void drawshape(){
    int xc=250,yc=250;
    float steps=PI/100;
    for(float theta=0;theta<2*PI;theta+=steps){
       float xoff=map(cos(theta),-1,1,0,maxnoise);////radial chal rahe to along theta
       float yoff=map(sin(theta),-1,1,0,maxnoise);////
       int r=int(map(noise(xoff,yoff),0,1,100,200));///////radius 100 to 200 vary, based on noise(0 to 1) noise=smooth random(aas pas dekh ke value deta hai,andha random nahi dega) 
       int x=int((xc+r*cos(theta)))/s;////////////////////
       int y=int((yc+r*sin(theta)))/s;
       s1.get(loc(x,y)).display(coldefault);
       //println(x+" "+y);
     }
  }
  points firstpoint(){
    for(slab here:s1){
      if(here.col==coldefault){
        here.visited=true;
        return new points(here.posx,here.posy,s);
      }
    }
    return new points(-1,-1,0);
  }
  void makelist(ArrayList<points> p1,int nowx,int nowy){
    if(p1.size()==0){
      points firstloc=firstpoint();///////////////////////firstpoint
      if(firstloc.s==-1){
        println("no point found. . .check image.");
        return;
      }
      p1.add(firstloc);
      nowx=firstloc.xpos;
      nowy=firstloc.ypos;
      //println(nowx+" "+nowy);
    }
    for(int j=-1;j<=1;j++){
      for(int i=-1;i<=1;i++){
        if(nowx+s*i>h*s || nowx+s*i<0 || nowy+s*j>h*s || nowy+s*j<0 || (i==0 && j==0)){////////execpt 4 boundaries every slab checks 8 neighbours 
          continue;
        }
        slab here=s1.get(loc((nowx+s*i)/s,(nowy+j*s)/s));
        if(here.col==coldefault && here.visited==false){
          here.visited=true;//////////////////////////if true then ignore and look for other slab
          p1.add(new points(here.posx,here.posy,s));
          makelist(p1,nowx+s*i,nowy+s*j);/////////////recursion here
        }
      }
    }
    return;//////////////////////////base case ke zaaroorat nahi thi apne aap return hojayega ek bar sab true hogye to
  }
};


