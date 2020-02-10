int s=10,h;      ///// s=here is basically size of each square and h=number of squares in rows and columns
int maxnoise=3; ////////jitna zada hoga utna utna wo close loop kam smooth dekhaiga
ArrayList<points> p1;
grid g1;
void setup(){
  size(500,500);
  h=500/s;
  g1=new grid();
  p1=new ArrayList<points>();
}
void draw(){
  background(255);
  g1.display();///////////////show simple grid
  g1.drawshape();/////////////show that woggly loop
  g1.makelist(p1,0,0);////////make list of points
  for(points here:p1){
    here.display();
  }
}


