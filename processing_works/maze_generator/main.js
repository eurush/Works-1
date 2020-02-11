int cell_size=25;
int grid_width,grid_height;
grid g1;
void setup(){
 size(500,500);
 grid_width=500/cell_size;
 grid_height=500/cell_size;
 g1=new grid();
}
void draw(){
 background(255);
 //g1.display();
 g1.traverse_maze(0,0);
 g1.display();
 println("ended");
 noLoop();
}
