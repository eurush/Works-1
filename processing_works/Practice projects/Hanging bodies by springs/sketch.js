var Engine = Matter.Engine,
    Bodies = Matter.Bodies,
    Composite = Matter.Composite;
    Constraint = Matter.Constraint;
    Mouse = Matter.Mouse;
    MouseConstraint = Matter.MouseConstraint;

var engine1 = Engine.create();

// Shapes and constraints
var allconstraints = [];
var alloptions = [];
var allshapes = [];
var hinge,optionsforhinge;
var connect;
var allpoints = [];
    // Parameters among "Shapes and Constraints"
    var numberofobjects = 10;
    var neutrallength = 45;
    var stiffness = 1.4;
// Mouse and its constraints
var mconst1;
var mousehere;

//obstacles
var obsleft,obsright,ground,obs1;


function setup(){
    var canvashere = createCanvas(900,600);
    makechain();
    connect = Constraint.create(optionsforhinge);
    mousehere = Mouse.create(canvashere.elt);
    var mouseoptions = {
        mouse : mousehere,
        constraint : {
            stiffness : 0.05
        }
    };
    mconst1 = MouseConstraint.create(engine1,mouseoptions);
    Composite.add(engine1.world,allconstraints);
    Composite.add(engine1.world,allshapes);
    Composite.add(engine1.world,[hinge, connect, mconst1]);
    createwalls();
}
function draw(){
    background(81);
    Engine.update(engine1, [delta=16.666], [correction=1]);
    

    updateandshowchain();
    updateandshowwalls();
    showmouseinteraction();
    beginShape();

    noFill();
    for(var phere of allpoints){
        vertex(phere.x,phere.y);
        // point(phere.x,phere.y);
    }
    endShape();
}

function makechain(){
    hinge = Bodies.circle(width/2,80,1,{isStatic:true});
    for(var i=0;i<numberofobjects;i++){
        allshapes.push(new SHAPES(random(40,width-40),random(0,height-40),40,20));
        allshapes[allshapes.length-1].createShape();
    }
    optionsforhinge = {
        bodyA: hinge,
        bodyB: allshapes[0].body,
        length : neutrallength,
        stiffness : stiffness

    };
    
    for(var i=0;i<numberofobjects-1;i++){
        allconstraints.push(Constraint.create({
        bodyA: allshapes[i].body,
        bodyB: allshapes[i+1].body,
        length : neutrallength,
        stiffness : stiffness

    }));
    }


}

function updateandshowchain(){
    for(var shapenow of allshapes){
        shapenow.update();
        shapenow.show();
    }
    stroke(0);
    // strokeWeight(2);

    line(hinge.position.x,hinge.position.y,allshapes[0].pos.x,allshapes[0].pos.y);
    for(var i=0;i<allshapes.length-1;i++){
        line(allshapes[i].pos.x,allshapes[i].pos.y,allshapes[i+1].pos.x,allshapes[i+1].pos.y);
    }
    allpoints.push(allshapes[allshapes.length-1].pos.copy());

    stroke(0,255,0);
    strokeWeight(4);
    point(hinge.position.x,hinge.position.y);
    noStroke();
    
    
}
function mousePressed(){
    allpoints = [];
}
function createwalls(){
    ground = new BOUNDARY(width/2,height,width,40);
    ground.createBoundary();
    obsleft = new BOUNDARY(0,height/2,40,height);
    obsleft.createBoundary();
    obsright = new BOUNDARY(width,height/2,40,height);
    obsright.createBoundary();
}
function updateandshowwalls(){
    obsleft.update();
    obsright.update();
    obsleft.show();
    obsright.show();
    ground.update();
    ground.show();
}
function showmouseinteraction(){
    if(mconst1.body){
        for(var shapehere of allshapes){
            if(shapehere.body==mconst1.body){
                push();
                fill(0,255,0,100);
                noStroke();
                ellipse(mconst1.body.position.x,mconst1.body.position.y,2*shapehere.radius);
                pop();
            }
        }
        var pos = mconst1.body.position;
        var offset = mconst1.constraint.pointB;
        var mouseloc = mconst1.constraint.pointA;
        push();
        stroke(0,255,0);
        strokeWeight(4);
        line(pos.x+offset.x,pos.y+offset.y,mouseloc.x,mouseloc.y);
        pop();
        // console.log(mconst1);
    }
}
