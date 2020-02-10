class points{
   int xpos,ypos,s;///////////////size of slab...kya pata kab zaarorat padjaye to aavai rakhliya
   points(int x,int y,int s){
     this.xpos=x;
     this.ypos=y;
     this.s=s;
   }
   int location(){
     return xpos+h*ypos;
   }
   void display(){
     fill(255);
     ellipse(this.xpos+this.s/2,this.ypos+this.s/2,this.s,this.s);
     //println(this.xpos+s/2+" "+this.ypos+this.s/2);
   }
};

