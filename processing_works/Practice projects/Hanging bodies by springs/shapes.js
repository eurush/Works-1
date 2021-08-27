function SHAPES(x,y,sides,radius){
	this.color = color(255,0,0,100);
	this.options ={
		friction: 0,
		restitution:0
	};
	this.pos = createVector(x,y);
	this.sides = sides;
	this.radius = radius;
	
	this.createShape = function(){
		this.body = Bodies.polygon(x,y,sides,radius,this.options);
		Composite.add(engine1.world,this.body);
	}
	this.update = function(){
		this.pos.x = this.body.position.x;
		this.pos.y = this.body.position.y;
	}
	this.show=function(){
		stroke(0,255,0);
		strokeWeight(2);
		push();
		translate(this.pos.x,this.pos.y);
		rotate(this.body.angle);
		line(0,0,0,this.radius/sqrt(2));
		pop();
		// stroke(1);
		noStroke();
		strokeWeight(1);
		fill(this.color);
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
