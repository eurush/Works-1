#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<cmath>
#define XY(x,y) cout << "\033["<<y<<";"<<x<<"H";
using namespace std;

const double CANVAS_WIDTH=140,CANVAS_HEIGHT=30,PI=3.14159265358979;
const unsigned int millisecond = 1000;
void print(const string val,int x,int y){
	XY(x,y);
	cout<<val;
	flush(cout);
	XY(1,1);
}
void sleep(int milli){
	usleep(milli*millisecond);
}
void clear_screen(){
	// cout << "\033[2J\033[1;1H";
	system("clear");
}

struct STYLE;
struct LINE;
struct TEXT;
struct LOCATION;
struct RECT;

struct STYLE{
private :
	string red 	    =	"\033[41m", blue="\033[44m",	green ="\033[42m",  white="\033[7m";
	string underline= "\033[4m" ,	bold="\033[1m" ,	italic="\033[3m";
	string blink    ="\033[5m";
	string end      ="\033[m";
public:
	bool _underline	=	false;
	bool _bold		=	false;
	bool _italic	=	false;
	bool _red		=	false, _blue=false,_green=false,_white=false;
	bool _blink		=	false;

	STYLE(){};
	STYLE(bool _underline,bool _bold,bool _italic,bool _red,bool _blue,bool _green,bool _white,bool _blink){
		this->_underline=		_underline;
		this->_bold=		_bold;
		this->_italic=		_italic;
		this->_red=			_red;
		this->_blue=		_blue;
		this->_green=		_green;
		this->_white=		_white;
		this->_blink=		_blink;
	}
	STYLE(const STYLE& tmp) =delete;
	STYLE& operator=(const STYLE& tmp)=delete;
	void set_color(bool r=0,bool g=0,bool b=0,bool w=0){
		this->_red=		r;
		this->_green=	g;
		this->_blue=	b;
		this->_white=	w;
	}
	void set_effect(bool un=0,bool bo=0,bool it=0,bool bli=0){
		this->_blink=	bli;
		this->_underline= un;
		this->_italic=	it;
		this->_bold=	bo;
	}
	void put_style(string &here){
		string tmp="";
		if(this->_underline)	tmp+=red;
		if(this->_bold)		tmp+=bold;
		if(this->_italic)		tmp+=italic;
		if(this->_blink)		tmp+=blink;
		if(this->_red)		tmp+=red+here+end;
		else if(this->_blue)	tmp+=blue+here+end;
		else if(this->_green)	tmp+=green+here+end;
		else if(this->_white)	tmp+=white+here+end;
		here=tmp+end;
	}
	void clear_style(){
		 _underline	=	false;
	 	_bold		=	false;
	 	_italic	=	false;
		 _red		=	false, _blue=false,_green=false,_white=false;
	 	_blink	=	false;
	}
};



struct LOCATION{
	double x=1,y=1;
	LOCATION(){}
	LOCATION(double x,double y):x(x),y(y){}
	// LOCATION(const LOCATION& tmp) =delete;
	// LOCATION& operator=(const LOCATION& tmp)=delete;
	void operator=(LOCATION &here){
		here.x=x;
		here.y=y;
	}
	void set(double x,double y){
		this->x=x;
		this->y=y;
	}
};
struct TEXT{
	string original_here;
	string here;
	TEXT(){}
	TEXT(const string &h){
		this->here=h;
		this->original_here=h;
	}
	TEXT(const TEXT& tmp) =delete;
	// TEXT& operator=(const TEXT& tmp)=delete;
	void operator=(TEXT &tmp){
		tmp.original_here = this->original_here;
		tmp.here          = this->here;
	}
	void set(const string &h){
		this->here         = h;
		this->original_here= h;
	}
	void set_style(STYLE &s1){
		s1.put_style(this->here);}

	void put_style(){
		cout<<(this->here);
		flush(cout);
	}
	void put_original(){
		cout<<(this->original_here);
		flush(cout);
	}

	void put_pos(int x,int y,bool isitoriginal=false){
		if(!isitoriginal)print(this->here,x,y);
		else print(this->original_here,x,y);
	}
	void reset_to_original(){
		this->here=this->original_here;}

};
struct LINE{
	LOCATION l1,l2;
	LINE(){}
	LINE(double x1,double y1,double x2,double y2){
		l1.x=(x1),l1.y=(y1),l2.x=(x2),l2.y=(y2);
	}
	LINE(const LINE& tmp) =delete;
	// LINE& operator=(const LINE& tmp)=delete;
	void operator=(LINE &here){
		here.l1=l1;
		here.l2=l2;
	}
	void set(double x1,double y1,double x2,double y2){
		l1.x=(x1),l1.y=(y1),l2.x=(x2),l2.y=(y2);
	}
	void draw(string ch,LOCATION loc1,LOCATION loc2,int points=0){
		if(abs(loc2.x-loc1.x)<=0.5 && abs(loc2.y-loc1.y)<=0.6)return;

		if(loc1.x>=CANVAS_WIDTH || loc2.x>=CANVAS_WIDTH || loc1.y >= CANVAS_HEIGHT || loc2.y>= CANVAS_HEIGHT 
			||  loc1.x<0  || loc2.x <0 || loc1.y<0 || loc2.y<0){}else{
			print(ch,loc1.x,loc1.y);
			print(ch,loc2.x,loc2.y);
		}
		LOCATION mid((loc1.x+loc2.x)/2,(loc1.y+loc2.y)/2);
		LOCATION first(loc1.x,loc1.y);
		LOCATION second(loc2.x,loc2.y);
		draw(ch,first,mid,points);
		draw(ch,mid,second,points);
	}
	void rotate(double angle,double xoff,double yoff){
		double midx=xoff,midy=yoff;
		LOCATION l11(l1.x-midx,l1.y-midy);	
		LOCATION l22(l2.x-midx,l2.y-midy);
		double xnew0=l11.x*cos(angle)-sin(angle)*l11.y,ynew0=l11.x*sin(angle)+l11.y*cos(angle);
		double xnew1=l22.x*cos(angle)-sin(angle)*l22.y,ynew1=l22.x*sin(angle)+l22.y*cos(angle);
		l1.set(xnew0+midx,ynew0+midy);
		l2.set(xnew1+midx,ynew1+midy);
	}
	void draw(string ch="o",double angle=0.0,double xoff=0.0,double yoff=0.0){
		rotate(angle,xoff,yoff);


		print(ch,l1.x,l1.y);
		print(ch,l2.x,l2.y);
		int points=max(int(abs(l1.x-l2.x)),int(abs(l1.y-l2.y)));
		LOCATION mid((l1.x+l2.x)/2,(l1.y+l2.y)/2);
		LOCATION first(l1.x,l1.y);
		LOCATION second(l2.x,l2.y);
		draw(ch,first,mid,points);
		draw(ch,mid,second,points);
	}
	void draw(double angle,double xoff,double yoff){
		draw("o",angle,xoff,yoff);
	}
	void erase(double angle,double xoff,double yoff){
		draw(" ",angle,xoff,yoff);
	}
	void erase(){
		draw(" ");
	}

};
struct RECT{
	bool center=false,top_left=true;

	LOCATION l1;
	double WIDTH,HEIGHT;

	RECT(){}
	RECT(double w,double h,double herex,double herey):WIDTH(w),HEIGHT(h/2){
		l1.set(herex,herey);}


	RECT(const RECT& tmp) =delete;
	RECT& operator=(const RECT& tmp)=delete;

	void set_center_mode(int i){
		i==0 ? center=true,top_left=false : top_left=true,center=false;}

	void set_location(double x,double y){
		l1.x=x;	l1.y=y;}

	void set_dimension(double w,double h){
		WIDTH=w;
		HEIGHT=h/2;
	}

	void draw(double angle=0.0,bool erase=false){
		LINE v1,v2,h1,h2;
		
		double point00=l1.x,point01=l1.x+WIDTH,point10=l1.y,point11=l1.y+HEIGHT;
		

		v1.set(point00,point10,point00,point11);
		v2.set(point01,point10,point01,point11);
		h1.set(point00,point10,point01,point10);
		h2.set(point00,point11,point01,point11);
			
		if(erase){
			v1.erase(angle,l1.x,l1.y);
			v2.erase(angle,l1.x,l1.y);
			h1.erase(angle,l1.x,l1.y);
			h2.erase(angle,l1.x,l1.y);
		}else{
			v1.draw(angle,l1.x,l1.y);
			v2.draw(angle,l1.x,l1.y);
			h1.draw(angle,l1.x,l1.y);
			h2.draw(angle,l1.x,l1.y);
		}
	}

};
struct ELLIPSE{
	LOCATION center;
	double a=1,b=1;
	ELLIPSE(const ELLIPSE& tmp) =delete;
	ELLIPSE& operator=(const ELLIPSE& tmp)=delete;
	ELLIPSE(){}
	ELLIPSE(double  a,double b,double cx,double cy):a(a),b(b){
		center.x=cx;
		center.y=cy;
	}
	void set(double a,double b,double cx,double cy){
		this->a=(a),
		this->b=(b);
		center.x=cx;
		center.y=cy;
	}
	void draw(string ch="o"){
		double theta=0.0;
		double x0=this->a*cos(theta)+center.x,y0=this->b*sin(theta)+center.y; 
		for(;theta<2*PI;theta+=0.001){
			x0=this->a*cos(theta)+center.x;
			y0=this->b*sin(theta)+center.y;
			print(ch,x0,y0);
		}
	}
	void erase(){
		draw(" ");
	}

};
int main()
{	
	clear_screen();
	RECT r1(10,10,70,15);
	// r1.draw();
	double i=0.0;
	while(i<4*PI){
		r1.draw(i);
		sleep(100);
		r1.draw(i,true);
		i+=PI/40;
	}
  	return 0;
}
