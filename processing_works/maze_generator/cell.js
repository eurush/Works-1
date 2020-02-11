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
      strokeWeight(3);
      line(xpos,ypos,xpos,ypos+size);
    }
    if(right==true){
      strokeWeight(3);
      line(xpos+size,ypos,xpos+size,ypos+size);
    }
    if(top==true){
      strokeWeight(3);
      line(xpos,ypos,xpos+size,ypos);
    }
    if(bottom==true){
      strokeWeight(3);
      line(xpos,ypos+size,xpos+size,ypos+size);
    }
    //strokeWeight(1);
    //noStroke();
    //if(visited==false){
    //  fill(200);
    //}else{
    //  fill(255);
    //}
    //rect(xpos,ypos,size,size);
  }
};
