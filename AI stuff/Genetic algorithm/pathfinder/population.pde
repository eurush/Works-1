class POPULATION{
      ELEMENT[] current;
      //float[] fitness;
      ArrayList<OBSTACLE> obs;
      ELEMENT bestfit;
      PVector target;
      float targetsize = 20;
      int scl;
      int popu;
      int generations=0;
      float maxfitval=0;
      boolean gotit = false;
      float fitnesssum=0;
      
      
      
      //----------------------------------------------------------------------------constructor
      POPULATION(PVector target,int popu,int scl){
          this.scl = scl;
          this.popu = popu;
          this.target = target.copy();
          this.bestfit = new ELEMENT(this.scl,-1);
          this.obs = new ArrayList<OBSTACLE> ();
          //this.obs.add(new OBSTACLE(new PVector(width/6+40,height/2+20),new PVector(5*width/6-40,height/2+60)));
          //this.obs.add(new OBSTACLE(new PVector(width/6+40,height/2-70),new PVector(5*width/6-40,height/2-110)));
          //this.fitness = new float[this.popu];
          this.current = new ELEMENT[this.popu];
          for(int i=0;i<this.current.length;i++){
              this.current[i] = new ELEMENT(this.scl,i);
              //this.fitness[i] = 0;
          }
      }
      void addobs(OBSTACLE o1){
        
          this.obs.add(o1);
      }
      
      
      
      // ----------------------------------------------------------------------calculate fitness and normalize 
      void calculatefitness(){
          //float sum=0;
          for(int i=0;i<this.current.length;i++){
              PVector e1 = this.current[i].pos.copy();
              PVector mid = PVector.sub(this.target,e1);
              float fitnow = 0;
              if(mid.mag()<=2*this.targetsize)fitnow = map(mid.mag(),0,2*this.targetsize,10,1);
              else if(this.current[i].reached==true) fitnow = 10;
              else fitnow = 10/(mid.mag());
              //if(this.current[i].crashed && !this.current[i].reached)this.current[i].fitness = this.current[i].fitness /10;
              //float fitnow = 1/( (mid.mag()));
              this.current[i].fitness = max(0,fitnow);
              this.maxfitval = max(this.maxfitval,this.current[i].fitness);
              //sum += this.current[i].fitness;
          }
          //this.fitnesssum = sum;
          normalizefitness();
      }
      void normalizefitness(){
          this.fitnesssum=0;
           for(int i=0;i<this.current.length;i++){
              this.current[i].fitness= this.current[i].fitness/this.maxfitval;
              this.fitnesssum+=this.current[i].fitness;
          }
      }
      // ---------------------------------------------------------------------------get new generation
      int getindex(){
         float val = (random(this.fitnesssum));
         int idx = 0;
         while(val>=0){
             val-= this.current[idx].fitness;
             idx++;
         }
         idx--;
         return idx;
      }
      void getnewgeneration(){
        ELEMENT[] newgen = new ELEMENT[this.current.length];
        for(int i=0;i<this.current.length;i++  ){
              int par1 = getindex();
              int par2 = getindex();
              //println(par1 + " ,"+par2);
              newgen[i] = new ELEMENT(this.scl,i);
              newgen[i].crossover(this.current[par1],this.current[par2]);
        }
        this.current = newgen;
      }
      
       // -------------------------------------------------------------------------all done living or not
      boolean alldone(){
        boolean allcrashed = true;
        for(ELEMENT e1 : this.current){
           allcrashed = allcrashed & (e1.crashed || e1.died); 
        }
        return allcrashed;
      }
      // --------------------------------------------------------------------reseting next generation
      void elementreset(){
          for(ELEMENT e1 : this.current){
              e1.health = e1.maxhealth;
              e1.reposition();
              e1.hue = 90;
              e1.crashed = false;
          }
      }
      
      
     
      
      // -----------------------------------------------------------------------------update everything
      void update(){
        if(alldone()==true){
          calculatefitness();
          
          getnewgeneration();
          elementreset();
          
          this.maxfitval = 0;
          this.generations+=1;
          
        }
        // updating positions of ELEMENTS
        calculatefitness();
        for(ELEMENT e1 : this.current){
          e1.fieldupdate(this.obs,this.target,this.targetsize);
          if(e1.reached==true)this.gotit = true;
        }
        
      }
      
      
      
      // ---------------------------------------------------------------------------display everything
      void displayenv(){
        //noFill();
        fill(0);
        textSize(20);
        text("Gen : "+Integer.toString(this.generations),width/2-40,20);
        text("Most Fit : "+Float.toString(this.maxfitval),width/2-40,40);
        fill(255,0,0);
        ellipse(this.target.x,this.target.y,this.targetsize,this.targetsize);
        for(ELEMENT e1 : this.current){
          e1.display();
        }
        for(OBSTACLE o1 : this.obs){
            o1.display();
        }
      }
     
  
}
