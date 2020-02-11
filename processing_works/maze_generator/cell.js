class cell{
  int size=cell_size;
  int xpos,ypos;
  boolean visited;
  boolean left,right,top,bottom;
   cell(int x,int y){
     this.left=true;
     this.right=true;
     this.top=true;
     this.bottom=true;
     this.xpos=x;
     this.ypos=y;
     this.visited=false;
  }
  void display(){
    if(left==true){
      strokeWeight(2);
      line(xpos,ypos,xpos,ypos+size);
    }
    if(right==true){
      strokeWeight(2);
      line(xpos+size,ypos,xpos+size,ypos+size);
    }
    if(top==true){
      strokeWeight(2);
      line(xpos,ypos,xpos+size,ypos);
    }
    if(bottom==true){
      strokeWeight(2);
      line(xpos,ypos+size,xpos+size,ypos+size);
    }
    //strokeWeight(1);
    //noStroke();
    //if(visited==false){
    //  fill(200);
    //}else{
    //  fill(100);
    //}
    //rect(xpos+2,ypos+2,size-2,size-2);
  }
};
