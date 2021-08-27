function BOUNDARY(x,y,w,h){
	this.options ={
		friction: 0,
		restitution:0,
		angle : 0,
		angularSpeed : 0,
		isStatic : true
	};
	this.pos = createVector(x,y);
	this.width = w;
	this.height = h;
	// this.settings = function(angle,angularSpeed){

	// }
	this.createBoundary = function(){
		this.body = Bodies.rectangle(x,y,w,h,this.options);
		Composite.add(engine1.world,this.body);
	}
	this.update = function(){
		this.pos.x = this.body.position.x;
		this.pos.y = this.body.position.y;
	}
	this.show=function(){
		stroke(0,255,0);
		strokeWeight(2);
		point(this.pos.x,this.pos.y);
		stroke(1);
		strokeWeight(2);
		// noStroke();
		fill(0,100);
		beginShape();
		for(var posi of this.body.vertices){
			vertex(posi.x,posi.y);
		}
		endShape(CLOSE);
	}
	this.remove=function(engine1){
		Composite.remove(engine1.world,this.body);
	}
}
