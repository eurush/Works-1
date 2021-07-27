1) Each element have their own Force-field, which guides their velocity and velocity over frame-time decides position.
    {   
          Important variables inside ELEMENT:
          mutationrate, fitness (real-time), force-field array, maxhealth, current health, position and velocity, (remaining variables are mainly for debugging
          and displaying), healthloss_decrement, boolean values -> reached, crashed and died, maxvelocity and maxacceleration (to not break the simulation by 
          accumuation of veloctity or acceleration), Hue value (to display health in terms of color)
          
          What ELEMENT can do:
          can take 2 parents as parameter to perform crossover and mutation, check for edges and obstacles, reposition (to reset to starting position)
          , Applyforce function to move element, (rest are displaying functions)
    }
    
2) Population, is where fitness is calculated, new-generation is born
   {
          Important variables inside POPULATION:
          ELEMENT[] array, obstacle[] array, no. of generations, target position, (remaining variables are mainly for debugging or displaying)
          
          What POPULATION can do:
          calculate fitness (with normalization), adds real time drawn obstacles, creates new-generation, resetting imp. parameters in new ELEMENT[] array, 
          (rest are displaying functions)
          
   }
3) Obstacle, its just a simple rectangle made with the help of 2 corner points,
   {
          Important variables inside OBSTACLE:
          corner point1, corner point2
          
          What POPULATION can do:
          checks if a given position is inside or not, (rest are just displaying functions)
          
   
   }
4) Main Sketch, is where everything is setted up, and looping happens to keep the simulation going
   {
          Important variables:
          Population, Target, population size, scale (how wide force-field should be, like if i have main-screen of 600x600 pixels, and then if scale=10, then
          force-field will have 60x60 force-vectors, each force-vector reponsibe for 10x10's grid), start and end position vectors (to create real-time obstacles)
          
          What mainly happens in Main Sketch:
          setup function intializes everything, draw function displays and updates the POPULATION over and over again (infinite loop so to speak),
          3 mouse interactive functions to draw obstacle in real-time, 1 keyboard interactive function to reset the simulation
        
   }
   
