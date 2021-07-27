class ELEMENT {
  PVector pos, vel;
  float maxvel = 5, maxaccn = 2;
  float radius = 100;
  float hue = 0;
  float hue1 = 0;
  float health = 200;
  float maxhealth = 200;
  float loss = 0.1;
  boolean crashed = false;
  boolean reached = false;
  boolean died = false;
  PVector[] field;
  int scl;
  float fitness=0;
  int zoff ;
  float mutationrate = 0.02;
  
  
  //----------------------------------------------------------------------------constructor
  ELEMENT(int scl,int zoff) {
    this.scl = scl;
    this.zoff = zoff;
    this.pos = new PVector(width/2, height-10);
    this.vel= new PVector(0, 0);
    field = new PVector[int(width/this.scl)*int(height/this.scl)];
    float xoff=0,yoff=0;
    for(int j=0;j<height/this.scl;j++){
      xoff=0;
        for(int i=0;i<width/this.scl;i++){
            int idx = i + j*(int(width/this.scl));
            float ang = map(noise(xoff,yoff,zoff),0,1,PI,4*PI);
            float magni = random(this.maxaccn);
            this.field[idx] = new PVector(cos(ang),sin(ang));
            this.field[idx].setMag(magni);
            this.field[idx].limit(this.maxaccn);
            xoff+=0.1;
        }
        yoff+=0.1;
     }
    //this.pos = pos.copy();
  }
  
  
  
  
  
  //---------------------------------------------------------------------------mutate and mutate
  PVector mutate(){
    float ang = map(random(1),0,1,PI,2*PI);
    float magni = random(this.maxaccn);
    PVector here = new PVector(magni*cos(ang),magni*sin(ang));
    return here;
  }
  
  void copyfield(ELEMENT e1,int till){
     // for(int j=0;j<height/this.scl;j++){
     //   for(int i=0;i<width/this.scl;i++){
     //       int idx = i + j*(int(width/this.scl));
     //       this.field[idx] = e1.field[idx].copy();
     //   }
     //}
     for(int i=0;i<till;i++){
           this.field[i] = e1.field[i].copy();
           if(random(1) < this.mutationrate)this.field[i] = mutate();
     }
     
  }
  void crossover(ELEMENT e2,ELEMENT e1){
      //println("aaa");
      int till = int(random(e1.field.length));
      copyfield(e2,till);
      //println("aaa");
      //ELEMENT child = new ELEMENT(this.scl,this.zoff);
      //for(int j=0;j<height/this.scl;j++){
      //  for(int i=0;i<width/this.scl;i++){
      //      int idx = i + j*(int(width/this.scl));
      //      if(idx%2==1)this.field[idx] = e1.field[idx].copy();
      //      //else child.field[idx] = this.field[idx].copy();
      //      if(random(1) < this.mutationrate)this.field[idx] = mutate();
      //  }
      //}
      this.fitness = max(e1.fitness,e2.fitness);
      for(int i=till;i<e1.field.length;i++){
           this.field[i] = e1.field[i].copy();
           if(random(1) < this.mutationrate)this.field[i] = mutate();
     }
  }
  
  //---------------------------------------------------------------reposition + checkedges and obstacles
  void reposition(){
     this.pos = new PVector(width/2, height-10);
  }
  void checkedges() {
    if (this.pos.x<0 || this.pos.x>=width || this.pos.y<0 || this.pos.y>=height){
          //this.crashed=true;
    }
    if (this.pos.x<0 || this.pos.x>=width)this.pos.x = abs(width - abs(this.pos.x));
    if (this.pos.y<0 || this.pos.y>=height)this.pos.y = abs(height - abs(this.pos.y));
  }
  boolean checkcollision(ArrayList<OBSTACLE> obshere){
        boolean ok = false;
        for(OBSTACLE o1 : obshere){
            ok = ok | o1.within(this.pos);
        }
        return ok;
  }
  
  
  //---------------------------------------------------------------getting field force + applying force + seek behaviour
  void fieldupdate(ArrayList<OBSTACLE> obshere,PVector target,float targetsize){
       checkedges();
       PVector mid = PVector.sub(target,this.pos);
       if(mid.mag()<=targetsize)this.reached=true;
       int x = int(this.pos.x/this.scl) ;
       int y = int(this.pos.y/this.scl) ;
       int idx = x + y*int(width/this.scl);
       update(this.field[idx],obshere);
  }
  void update(PVector target,ArrayList<OBSTACLE> obshere){
      if(this.health!=0){
          this.health-=1;
      }else{
         this.died = true; 
      }
      if(checkcollision(obshere)){
        this.crashed = true;
        this.health = 0;
         this.vel.setMag(0);
      }else{
         //applyseekforce(target); 
         applyforce(target);
      }
  }
  void applyforce(PVector force){
      this.vel.add(force);
      this.vel.limit(this.maxvel);
      this.pos.add(vel);
      checkedges();
  }
  void applyseekforce(PVector target) {
    PVector mid = PVector.sub(target, pos);
    float distnow = mid.mag();
    mid.limit(this.maxaccn);
    vel.add(mid);
    vel.limit(maxvel);
    float magnow = distnow;
    if (distnow<=this.radius) {
      //if(distnow<=50)reposition();
      magnow = map(magnow, 0, this.radius, 0, this.maxvel); 
      vel.setMag(magnow);
    }

    pos.add(vel);
    checkedges();
  }
  
  

 
  //---------------------------------------------------------------------------display ELEMENT
  void display() {
    colorMode(HSB);
    //noStroke();
    this.hue = map(this.health,0,this.maxhealth,0,90);
    fill(this.hue,255,255);
    PVector pt1 = new PVector(cos(this.vel.heading()), sin(this.vel.heading()));
    PVector pt2 = new PVector(cos(this.vel.heading()+PI/2), sin(this.vel.heading()+PI/2));
    PVector pt3 = new PVector(cos(this.vel.heading()-PI/2), sin(this.vel.heading()-PI/2));
    pt1.setMag(20);
    pt1.add(pos);
    pt2.setMag(5);
    pt2.add(pos);
    pt3.setMag(5);
    pt3.add(pos);
    beginShape();
    vertex(pt1.x, pt1.y);
    vertex(pt2.x, pt2.y);
    vertex(pt3.x, pt3.y);
    endShape(CLOSE);
    fill(0);
    textSize(15);
    text(Integer.toString(this.zoff),this.pos.x+10,this.pos.y);
    //text(Float.toString(this.fitness),this.pos.x+10,this.pos.y+15);
    
  }
  
  
  //---------------------------------------------------------------display force field
  void showfield(){
    //rectMode(CENTER);
     for(int j=0;j<height/this.scl;j++){
        for(int i=0;i<width/this.scl;i++){
            int idx = i + j*(int(width/this.scl));
            PVector h = new PVector(cos(this.field[idx].heading()),sin(this.field[idx].heading()));
            float magni = map(this.field[idx].mag(),0,this.maxaccn,0,this.scl);
            h.setMag(magni);
            PVector poshere = new PVector(i*this.scl+i*this.scl/2,j*this.scl + j*this.scl/2);
            stroke(0);
            strokeWeight(1);
            line(poshere.x - h.x,poshere.y - h.y,poshere.x + h.x,poshere.y + h.y);
            strokeWeight(4);
            point(poshere.x + h.x,poshere.y + h.y);
        }
     }
  }
}
