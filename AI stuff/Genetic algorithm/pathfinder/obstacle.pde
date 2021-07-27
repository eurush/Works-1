class OBSTACLE{
      PVector p1,p2;
      
      //----------------------------------------------------------------------------constructor
      OBSTACLE(PVector p1,PVector p2){
            this.p1 = p1.copy();
            this.p2 = p2.copy();
      }
      
      
      boolean within(PVector pos){
          if((pos.x>=min(p1.x,p2.x) && pos.x<=max(p1.x,p2.x)) && (pos.y>=min(p1.y,p2.y) && pos.y<=max(p1.y,p2.y))){
                 return true;
          }
          return false;
          
      }
      void display(){
        stroke(21);
        fill(21,40);
        float dx = p2.x-p1.x;
        float dy = p2.y-p1.y;
        beginShape();
        vertex(p1.x,p1.y);
        vertex(p1.x+dx,p1.y);
        
        vertex(p2.x,p2.y);
        vertex(p1.x,dy+p1.y);
        endShape(CLOSE);
        
      }
}
