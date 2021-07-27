PVector st,end;
float c1;
POPULATION p1;
PVector target;
int scl=20;
int popu = 100;
void setup(){
     size(600,600);
     target = new PVector(width/2,height/2-20);
     st = new PVector(0,0);
     end = new PVector(0,0);
     p1 = new POPULATION(target,popu,scl);
     colorMode(HSB);
}
void draw(){
  background(255);
  p1.update();
  p1.displayenv();
}
void mousePressed(){
   st = new PVector(mouseX,mouseY); 
}
void mouseDragged(){
   stroke(1);
   fill(31,100);
   rect(st.x,st.y,mouseX-st.x,mouseY-st.y);
}
void mouseReleased(){
   end = new PVector(mouseX,mouseY);
   p1.addobs(new OBSTACLE(st,end));
}
void keyPressed(){
     if(key==TAB){
         p1 = new POPULATION(target,popu,scl);
     }  
}

