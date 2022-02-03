// drag mouse to add points

var root;
var points=[];
var range;
var ptsall;
function setup(){
    createCanvas(800,600);
    root = new QUAD(width,height,{x:width/2,y:height/2},4);
    // range = {x:400,y:300,w:90,h:90};
    range = new BLOCK(90,90,{x:400,y:300});
    // for(let i=0;i<50;i++){
    //     let pt = {x:random(width),y:random(height)};
    //     points.push(pt);
    //     root.insert(pt);
    // }
}
function draw(){
    background(200);
    for(let p of points){
        noFill();
        stroke(0,0,0);
        strokeWeight(3);
        point(p.x,p.y);
    }
    rectMode(CENTER);   noFill();
    stroke(0,255,0);    strokeWeight(3);
    range.center.x = mouseX; range.center.y = mouseY;
    rect(range.center.x,range.center.y,range.width,range.height);


    root.show();
    root.queryrange(range);

    ptsall = root.queryrange(range);
    for(let pt of ptsall){
        stroke(0,255,0);
        strokeWeight(4);
        point(pt.x,pt.y);
    }
    fill(0);stroke(0);strokeWeight(1);
    textSize(32);
    text(ptsall.length, mouseX-20, mouseY-20);
    // ptsall=[];
}
// function mousePressed(){
//     let pt = {x:mouseX,y:mouseY};
//     points.push(pt);
//     root.insert(pt);
// }
function mouseDragged(){
    let pt = {x:mouseX,y:mouseY};
    points.push(pt);
    root.insert(pt);
}

class QUAD{

    // N when y++ and S when y--
    // W when x-- and E when x++
    constructor(w,h,center,capacity){
        this.block = new BLOCK(w,h,center);
        this.capacity = capacity;
        this.points=[];
        this.divided=0;
    }
    insert(pt){
        if(!this.block.contains(pt))return false;

        if(this.points.length<this.capacity){
            this.points.push(pt);
            return true;
        }
        if(this.divided==0){
            this.subdivide();
            this.divided=22;
        }
        if(this.NW.insert(pt))return true;
        if(this.NE.insert(pt))return true;
        if(this.SW.insert(pt))return true;
        if(this.SE.insert(pt))return true;
        return false;
    }
    subdivide(){
        let w = this.block.width, h = this.block.height;
        let center = this.block.center;
        this.NW = new QUAD(w/2,h/2,{x:center.x-w/4,y:center.y+h/4},this.capacity);
        this.NE = new QUAD(w/2,h/2,{x:center.x+w/4,y:center.y+h/4},this.capacity);
        this.SW = new QUAD(w/2,h/2,{x:center.x-w/4,y:center.y-h/4},this.capacity);
        this.SE = new QUAD(w/2,h/2,{x:center.x+w/4,y:center.y-h/4},this.capacity);
        this.divided==122;
        // console.log("S",this.divided);
    }
    queryrange(rng){
        if(!this.block.intersect(rng)){
            return[];
        }
        let pts=[];
        for(let pt of this.points){
            if(rng.contains(pt))pts.push(pt);
            // stroke(255,255,0);
            // strokeWeight(4);
            // point(pt.x,pt.y);
        }
        if(this.divided>0){
            let nwarr = this.NW.queryrange(rng);
            // let ptsNW = this.NW.queryrange(rng);
            let nearr = this.NE.queryrange(rng);
            // let ptsNE = this.NE.queryrange(rng);
            let swarr = this.SW.queryrange(rng);
            // let ptsSW = this.SW.queryrange(rng);
            let searr = this.SE.queryrange(rng);
            // let ptsSE = this.SE.queryrange(rng);
            for(let i of nwarr)pts.push(i);
            for(let i of nearr)pts.push(i);
            for(let i of swarr)pts.push(i);
            for(let i of searr)pts.push(i);
        }
        return pts;
    }
    show(){
        if(this.points.length==0)return;
        this.block.show();
        if(this.divided>0){
            this.NW.show();
            this.NE.show();
            this.SE.show();
            this.SW.show();
        }
    }
}

class BLOCK{
    constructor(w,h,center){
        this.center = center;
        this.width = w;            // full width and full height
        this.height = h;
    }
    contains(pt){
        let xpass = (pt.x<=this.center.x+this.width/2)&&(this.center.x-this.width/2<pt.x);
        let ypass = (pt.y<=this.center.y+this.height/2)&&(this.center.y-this.height/2<pt.y);
        return xpass&&ypass;

    }   
    intersect(blk){
        // this block is stationary and rng is varying
        let inside=false;  
        // N wall = y++
        let Sblk = blk.center.y - blk.height/2;
        let Nblknow = this.center.y + this.height/2;
        inside|= Nblknow >= Sblk;

        // S wall = y--
        let Nblk = blk.center.y + blk.height/2;
        let Sblknow = this.center.y - this.height/2;
        inside|= Sblknow <= Nblk;

        // W wall = x--
        let Eblk = blk.x-blk.w/2;
        let Wblknow = this.center.x - this.width/2;
        inside|= Wblknow <= Eblk;

        // E wall = x++
        let Wblk = blk.x+blk.w/2;
        let Eblknow = this.center.x + this.width/2;
        inside|= Eblknow >= Eblk;
        return true;

    }
    show(){
        stroke(255,0,0);
        noFill();
        strokeWeight(2);
        rectMode(CENTER);
        rect(this.center.x,this.center.y,this.width,this.height);
    }
}
