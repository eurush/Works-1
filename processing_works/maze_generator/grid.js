int give_loc(int x,int y){
 return x+grid_width*y; 
}
class grid{
  ArrayList<cell> blocks;
  grid(){
   blocks=new ArrayList<cell>();
   for(int y=0;y<grid_height;y++){
     for(int x=0;x<grid_width;x++){
       blocks.add(new cell(x*cell_size,y*cell_size));
     }
   }
  }
  void display(){
    for(cell here:blocks){
        here.display();
    }
  }
  boolean leftline(int whichy){
    if(blocks.get(give_loc(1,whichy)).visited==false){
      return false;
    }else{
      if(whichy==0){
        if(blocks.get(give_loc(0,whichy+1)).visited==false){
          return false;
        }
      }else if(whichy==grid_height-1){
        if(blocks.get(give_loc(0,whichy-1)).visited==false){
          return false;
        }
      }else{
        if(blocks.get(give_loc(0,whichy-1)).visited==false || blocks.get(give_loc(0,whichy+1)).visited==false){
          return false;
        }
      }
    }
    return true;
  }
  boolean rightline(int whichy){
    if(blocks.get(give_loc(grid_width-2,whichy)).visited==false){
      return false;
    }else{
      if(whichy==0){
        if(blocks.get(give_loc(grid_width-1,whichy+1)).visited==false){
          return false;
        }
      }else if(whichy==grid_height-1){
        if(blocks.get(give_loc(grid_width-1,whichy-1)).visited==false){
          return false;
        }
      }else{
        if(blocks.get(give_loc(grid_width-1,whichy-1)).visited==false || blocks.get(give_loc(grid_width-1,whichy+1)).visited==false){
          return false;
        }
      }
    }
    return true;
  }
  boolean topline(int whichx){
    if(blocks.get(give_loc(whichx,1)).visited==false){
      return false;
    }else{
      if(whichx==0){
        if(blocks.get(give_loc(whichx+1,0)).visited==false){
          return false;
        }
      }else if(whichx==grid_width-1){
        if(blocks.get(give_loc(whichx-1,0)).visited==false){
          return false;
        }
      }else{
        if(blocks.get(give_loc(whichx-1,0)).visited==false || blocks.get(give_loc(whichx+1,0)).visited==false){
          return false;
        }
      }
    }
    return true;
  }
  boolean bottomline(int whichx){
    if(blocks.get(give_loc(whichx,grid_height-2)).visited==false){
      return false;
    }else{
      if(whichx==0){
        if(blocks.get(give_loc(whichx+1,grid_height-1)).visited==false){
          return false;
        }
      }else if(whichx==grid_width-1){
        if(blocks.get(give_loc(whichx-1,grid_height-1)).visited==false){
          return false;
        }
      }else{
        if(blocks.get(give_loc(whichx-1,grid_height-1)).visited==false || blocks.get(give_loc(whichx+1,grid_height-1)).visited==false){
          return false;
        }
      }
    }
    return true;
  }
  boolean check_all_neighbours(int whichx,int whichy){
    if(whichx==0){
       return leftline(whichy);
    }else if(whichx==grid_width-1){
       return rightline(whichy);
    }
    if(whichy==0){
       return topline(whichx);
    }else if(whichy==grid_height-1){
       return bottomline(whichx);
    }
    boolean ri=blocks.get(give_loc(whichx+1,whichy)).visited;
    boolean le=blocks.get(give_loc(whichx-1,whichy)).visited;
    boolean to=blocks.get(give_loc(whichx,whichy-1)).visited;
    boolean bo=blocks.get(give_loc(whichx,whichy+1)).visited;
    return ri && le && to && bo;
  }
  void traverse_maze(int whichx,int whichy){
    if(blocks.get(give_loc(whichx,whichy)).visited==true){
      return;
    }
    //if(whichx==grid_width-1 && whichy==grid_height-1){
    //  return;
    //}
    blocks.get(give_loc(whichx,whichy)).visited=true;
    while(true){
      int delx=((int(random(0,100)))%4);
      int dely=0;
      if(delx%2==0){
        if((int(random(0,100)))%2==0){
          dely=-1;
        }else{
          dely=1;
        }
        delx=0;
      }else{
        delx=delx-2;
      }
      //delay(50);
      if((whichx+delx>=0 && whichx+delx<grid_width && whichy+dely>=0 && whichy+dely<grid_height)){
        if( blocks.get(give_loc(whichx+delx,whichy+dely)).visited==false){
           if(delx==0){
             if(dely==1){
               blocks.get(give_loc(whichx,whichy)).bottom=false;
               blocks.get(give_loc(whichx+delx,whichy+dely)).top=false;
             }else{
               blocks.get(give_loc(whichx,whichy)).top=false;
               blocks.get(give_loc(whichx+delx,whichy+dely)).bottom=false;
             }
           }else if(delx==1){
               blocks.get(give_loc(whichx,whichy)).right=false;
               blocks.get(give_loc(whichx+delx,whichy+dely)).left=false;
           }else{
               blocks.get(give_loc(whichx,whichy)).left=false;
               blocks.get(give_loc(whichx+delx,whichy+dely)).right=false;
           }
           
           traverse_maze(whichx+delx,whichy+dely);
        }
        if(check_all_neighbours(whichx,whichy)==true){
          break;
        }
      }
    }
    //int[] alongx={0,1,-1};
    //int[] alongy={1,-1};
    //for(int x:alongx){
    //  if(x==0){
    //    for(int y:alongy){
    //      if(whichx+x>=0 && whichx+x<grid_width && whichy+y>=0 && whichy+y<grid_height){
    //        if(blocks.get(give_loc(whichx+x,whichy+y)).visited==false){
    //           if(y==1){
    //             blocks.get(give_loc(whichx,whichy)).bottom=false;
    //             blocks.get(give_loc(whichx+x,whichy+y)).top=false;
    //           }else{
    //             blocks.get(give_loc(whichx,whichy)).top=false;
    //             blocks.get(give_loc(whichx+x,whichy+y)).bottom=false;
    //           }
    //          traverse_maze(whichx+x,whichy+y);
    //        }
    //      }
    //    }
    //  }else{
    //      if(whichx+x>=0 && whichx+x<grid_width){
    //        if(blocks.get(give_loc(whichx+x,whichy)).visited==false){
    //          if(x==1){
    //             blocks.get(give_loc(whichx,whichy)).right=false;
    //             blocks.get(give_loc(whichx+x,whichy)).left=false;
    //         }else{
    //             blocks.get(give_loc(whichx,whichy)).left=false;
    //             blocks.get(give_loc(whichx+x,whichy)).right=false;
    //         }
    //          traverse_maze(whichx+x,whichy);
    //        }
    //      }
    //  }
    //}
  }
};
