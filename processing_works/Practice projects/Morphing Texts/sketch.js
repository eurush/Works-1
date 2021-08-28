
// Works with .ttf and .otf Font Formats
var otf1;
function preload(){
    otf1 = loadFont('./fonts/ttfpart3.ttf');
}
// After preloading

// Fix parameters for both Target and Initial Strings
var sizeslider;
var sampleslider;
var speed=2.7;
var newpos = [];
var threshold = 1.4;
var whichone=true;
var offx = 20,offy=30;

var strokeW1 = 2;

// DOM elements for Strings
var inputbox1,inputbox2,name1,name2;
var firstpoints;
var secondpoints;;
var pinkcolor;
var scl=20;
function setup(){
    createCanvas(1000,600);
    background(100);
    sizeslider = createSlider(0,1000,250);
    sizeslider.position(0,height+20);
    sampleslider = createSlider(0,50,40);
    sampleslider.position(0,height+40);

    inputbox1 = createInput('A');
    inputbox2 = createInput('B');
    inputbox1.position(width/2,height+20);
    inputbox2.position(width/2,height+40);
    inputbox1.size(100);
    inputbox2.size(100);
    inputbox1.mousePressed(dothis);
    inputbox2.mousePressed(dothis);

    name1 = createP('size_slider');
    name1.position(150,height+5);

    name2 = createP('sample_slider');
    name2.position(150,height+25);

    firstpoints = otf1.textToPoints(inputbox1.value(),offx,sizeslider.value()+offy,sizeslider.value(),{
        sampleFactor : sampleslider.value()/50
    });
    secondpoints = otf1.textToPoints(inputbox2.value(),offx,2*sizeslider.value()+offy,sizeslider.value(),{
        sampleFactor : sampleslider.value()/50
    });
    getnewpos();
}
function draw(){
    push();
    colorMode(RGB);
    background(100);
    pop();
    colorMode(HSB);
    if(whichone==true)showfirst();
    else showsecond();
    updatepoints();

}
function updatepoints(){
    var cnt=0;
    for(var i=firstpoints.length-1;i>=0;i--){
        firstpoints[i].x+=newpos[i].x;
        firstpoints[i].y+=newpos[i].y;
        var idx = int(map(i,0,firstpoints.length-1,0,secondpoints.length-1));
        var dist1 = dist(firstpoints[i].x,firstpoints[i].y,secondpoints[idx].x,secondpoints[idx].y);
        if(dist1<threshold){
            newpos[i].x=0;
            newpos[i].y=0;
            cnt++;
        }
    }
    if(cnt==firstpoints.length){
        whichone=false;
    }
}
function getnewpos(){
    for(var i=0;i<firstpoints.length;i++){
        var pointa = createVector(firstpoints[i].x,firstpoints[i].y);
        var idx = int(map(i,0,firstpoints.length-1,0,secondpoints.length-1));
        var pointb = createVector(secondpoints[idx].x,secondpoints[idx].y).sub(pointa);
        pointb.setMag(random(1,speed));
        newpos.push(pointb);
    }
}
function showfirst(){
    var colorval = 0;
    var frwd = true;
    push();
    colorMode(HSB);
    noFill();
    beginShape();
    // noStroke();
    for(var posi of firstpoints){
        push();
        stroke(colorval,255,255,100);
        strokeWeight(strokeW1);
        point(posi.x,posi.y);
        // vertex(posi.x,posi.y);
        pop();
        if(frwd==true)colorval++;
        else colorval--;
        if(colorval==256)frwd=false;
        if(colorval==0)frwd = true;
    }
    endShape();
    pop();
}
function showsecond(){
    var colorval=0;
    var frwd=true;
    push();
    colorMode(HSB);
    noFill();
    noStroke();
    beginShape();
    for(var posi of secondpoints){
        push();
        stroke(colorval,255,255,100);
        strokeWeight(strokeW1);
        // vertex(posi.x,posi.y);
        point(posi.x,posi.y);
        pop();
         if(frwd==true)colorval++;
        else colorval--;
        if(colorval==256)frwd=false;
        if(colorval==0)frwd = true;
    }
    endShape();
    pop();

}
function dothis(){
    // background(100);
    whichone = true;
    firstpoints = otf1.textToPoints(inputbox1.value(),offx,sizeslider.value()+offy,sizeslider.value(),{
        sampleFactor : sampleslider.value()/50
    });
    secondpoints = otf1.textToPoints(inputbox2.value(),offx,2*sizeslider.value()+offy,sizeslider.value(),{
        sampleFactor : sampleslider.value()/50
    });
    newpos = [];
    getnewpos();
}
