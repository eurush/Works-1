class slab{
  int posx,posy,s,col;//s=size of slab...kya pata kab zaarorat padjaye to yaha bhi aavai rakhliya
  boolean visited;
  slab(int x,int y,int s){
    this.posx=x;
    this.posy=y;
    this.s=s;
    this.visited=false;
    this.col=255;
  }
  void display(int x){
    this.col=x;///////col = color of slab
    fill(x);
    rect(posx,posy,s,s);
  }
};
