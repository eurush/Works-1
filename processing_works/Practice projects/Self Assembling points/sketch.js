
var font1;
function preload(){
    font1 = loadFont('./fonts/ttfpart3.ttf');
}
var points1 = [];
var points2 = [];
var textmsg = "Happy";
var textmsg2 = "Diwali";
var textsize = 140;
var effRadii = 100;
var maxvelinE= false;
function setup(){
    createCanvas(1000,600);
    let x=0,y=height/3,delx = width/textmsg.length;
    for(let c of textmsg){
        points1.push(new POINTS(c,x,y,textsize,font1));
        x+=delx;
    }
    x=0,y+=height/2;
    for(let c of textmsg2){
        points2.push(new POINTS(c,x,y,textsize,font1));
        x+=delx*0.9;
    }
    colorMode(HSB);
}

function draw(){
    background(255);
    for(let pts of points1){
        pts.updateVel();
        pts.show();
    }
    for(let pts of points2){
        pts.updateVel();
        pts.show();
    }
    noFill();
    stroke(0,50);
    strokeWeight(1);
    circle(mouseX,mouseY,2*effRadii);

}


class POINTS{
    constructor(ch,offx,offy,fontsize,font){
        this.fontsize = fontsize;
        this.options = {
            sampleFactor: 0.4,
            simplifyThreshold: 0
        };
        this.fonthere = font;
        this.points=this.fonthere.textToPoints(ch,offx,offy,this.fontsize,this.options);;
        this.points_original = this.fonthere.textToPoints(ch,offx,offy,this.fontsize,this.options);
        this.alphabet=ch;
        this.pos = createVector(offx,offy); 
        this.maxaccn = 1;
        this.maxvel = 5;
        this.velocities = [];
        for(let i=0;i<this.points.length;i++){
            this.velocities.push(createVector(0,0));
        }
    }
    updateVel(){
        for(let i=0;i<this.points.length;i++){
            let dist1 = dist(this.points[i].x,this.points[i].y,mouseX,mouseY);
            // dist1*=dist1;
            let accn_mag = map(dist1,0,2*effRadii,0,this.maxaccn);
            let accn;
            let isitinside_100 = false;
            if(dist1>effRadii){
                dist1 = dist(this.points[i].x,this.points[i].y,
                             this.points_original[i].x,this.points_original[i].y);
                accn_mag=map(dist1,100,max(height,width),10*this.maxaccn,0);
                accn = p5.Vector.sub(createVector(this.points_original[i].x,this.points_original[i].y),
                createVector(this.points[i].x,this.points[i].y)).setMag(accn_mag);;
                isitinside_100= true;
            }else{
                accn = p5.Vector.sub(createVector(mouseX,mouseY),
                createVector(this.points[i].x,this.points[i].y)).setMag(accn_mag);                
            }

            this.velocities[i].add(accn);
            if(maxvelinE==true)this.velocities[i].limit(this.maxvel);
            this.points[i].x+=this.velocities[i].x;
            this.points[i].y+=this.velocities[i].y;
            if(abs(this.points[i].x-this.points_original[i].x)<10 && isitinside_100)this.points[i].x=this.points_original[i].x;
            if(abs(this.points[i].y-this.points_original[i].y)<10 && isitinside_100)this.points[i].y=this.points_original[i].y;
            this.check_boundaries(i);
        }
    }
    check_boundaries(i){
        let x = this.points[i].x;
        let y = this.points[i].y;
        if(x<=0 || x>=width)this.points[i].x = (width+x)%width;
        if(y<=0 || y>=height)this.points[i].y = (height+y)%height;
    }
    show(){
        beginShape();
        noFill();
        let i=0;
        // stroke(255,255,255,20);
        strokeWeight(5);
        for(let pt of this.points){
            stroke(255*abs(sin(2*i)),255,255,20);
            point(pt.x,pt.y);
            i+=PI/this.points.length;
        }
        endShape();
    }   
}

function keyPressed(){
    if(maxvelinE==false)maxvelinE=true;
    else maxvelinE=false;
}
