

var dataset,perp1,coeff=[];
function setup(){
    createCanvas(600,600);
    let n=3;
    // coeff=[0.074,0.8026,0.5670];
    for(let i=0;i<n;i++){
        coeff.push(random(-1,1));
    }
    datahere=new DATASET(coeff,300); 
    perp1=new NEURON(n);
}
function draw(){
    background(51);
    // showing dataset
    datahere.show();
    // train and show result
    perp1.training(datahere.data);
    perp1.partition();

}

class NEURON{
    constructor(n){
        this.weights=[];
        this.lr=0.0001;
        for(let i=0;i<=n;i++){
            this.weights.push(random(-1,1));
        }
    }
    guess(inpp){
        let ans=this.weights[0]*inpp[0];
        for(let i=1;i<inpp.length;i++){
            ans+=this.weights[i]*inpp[i];
        }
        return ans<0 ? -1 : 1;
    }
    training(sethere){
        for(let datahere of sethere){
            let error=datahere.label - this.guess(datahere.pts);
            for(let i=0;i<this.weights.length;i++){
                this.weights[i]+=error*this.lr*datahere.pts[i];
            }
        }
    }
    partition(){
        stroke(255,0,0);
        strokeWeight(3);
        noFill();
        beginShape();
        let numofpoints=100;
        for(let i=0;i<1;i+=1/numofpoints){
            let y = 0;
            for(let j=1;j<this.weights.length;j++){
                y+=this.weights[j]*pow(i,j-1);
            }
            y=y/this.weights[0];
            vertex(i*width,y*height);
        }
        endShape();
    }
}

class DATASET{
    constructor(coeff,numofpoints){
        this.coeff=coeff.slice();
        this.data=[];
        for(let numm=0;numm<numofpoints;numm++){
            let arr=[]; arr.push(0);
            let x=random(-1,1);
            let y=random(-1,1);
            let ans=0;
            for(let i=0;i<coeff.length;i++){
                ans+=this.coeff[i]*pow(x,i);
                arr.push(pow(x,i));
            }
            arr[0]=y;
            ans+=y;
            this.data.push({pts : arr.slice(),label:ans<0 ? -1 : 1});
        }
    }
    show(){
        stroke(0,255,0);
        strokeWeight(3);
        noFill();
        beginShape();
        let numofpoints=100;
        for(let i=0;i<1;i+=1/numofpoints){
            let y = 0;
            for(let j=0;j<this.coeff.length;j++){
                y+=this.coeff[j]*pow(i,j);
            }
            // y=map(y,0,y,0,height);
            vertex(i*width,y*height);
        }
        endShape();
    }

}
