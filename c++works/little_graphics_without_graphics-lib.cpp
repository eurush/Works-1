#include<iostream>
#include<fstream>
#include<cstring>
#include<math.h>
#include<vector>
#define IX(x,y) (x+(y)*(windows_x+2))
#define PI (2*asin(1))
int windows_x=100,windows_y=20;
using namespace std;
class RECT{
	int h,w,posx,posy;

public:
	RECT():h(0),w(0),posx(0),posy(0){}
	RECT(int h,int w,int posx,int posy):h(h),w(w),posx(posx),posy(posy){}
	void update(int h,int w,int posx,int posy){
		this->h=h;		this->w=w;
		this->posx=posx;	this->posy=posy;
	}
	void draw(fstream &f1,char ch='*',bool fill=false){
		f1.seekp(IX(posx,posy),ios::beg);
		for(int i=0;i<w;i++){
			f1<<ch;
		}
		for(int j=1;j<h-1;j++){
			f1.seekp(IX(posx,posy+j),ios::beg);
			f1<<ch;	int xhere=w-2;	while(xhere!=0 && fill==true){f1<<ch; xhere--;}		
			f1.seekp(IX(posx+w-1,posy+j),ios::beg);
			f1<<ch;
		}
		f1.seekp(IX(posx,posy+h-1),ios::beg);
		for(int i=0;i<w;i++){
			f1<<ch;
		}
	}
};
class INCLINED{
	RECT *pixel=NULL;
	int h,w,posx,posy;
	bool right;
	public:
	INCLINED(){}
	INCLINED(int h,int w,int posx,int posy,bool right=true):h(2*h),w(2*w),posx(posx),posy(posy),pixel(new RECT[h]()),right(right){}
	void update(int h,int w,int posx,int posy,bool right=true){
		this->h=2*h;	this->w=2*w;	this->posx=posx;
		this->posy=posy;	this->right=right;
		pixel=new RECT[h]();
	}
	void draw(fstream &f1,char ch='*',bool fill=false){
		for(int i=0;i<h/2;i++){
			pixel[i].update(2,3,posx+2*i,posy+(h-2)*(int(!right))-i*2*(1*(!right)-right));		
			pixel[i].draw(f1,ch,fill);
		}
	}
};
class CIRCLE{
	vector<RECT> pixel;
	int radius,posx,posy;
	public:
	CIRCLE(){}
	CIRCLE(int radius,int posx,int posy):radius(radius),posx(posx),posy(posy){}
	void udpate(int r,int px,int py){
		radius=r;	posx=px;	posy=py;
	}
	void draw(fstream &f1,char ch='*',double init_angle=0,double final_angle=2*PI,bool fill=false){
		for(double angle=init_angle;angle<final_angle;angle+=PI/10){
			pixel.push_back(RECT(2,2,posx-int(radius*(cos(angle))),posy-int(radius*(sin(angle)))));
			pixel[pixel.size()-1].draw(f1,ch,fill);
		}
	}

};
void create_area(int y,int x,fstream &f1){
	while(y--){
		int x1=x;
		while(x1--)f1<<' ';
		f1<<'\n';
	}
}
void print_screen(fstream &f1){
	f1.seekp(0,ios::beg);
	while(f1.eof()!=true){
		char s;	f1.get(s);	cout<<s;
	}
	f1.close();
}
int main(){
	fstream f1("a1.txt",ios::in | ios::out | ios::trunc);
	if(f1.is_open()==false){
		cout<<"damn it\n";
	}else{
		//string s="ABC";
		//int height_of_alphabet=6;
		create_area(windows_y,windows_x,f1);
		RECT canvas(windows_y-1,windows_x-1,0,0);
		INCLINED l1(5,5,5,5,true),l2(5,5,15,5,false);	l1.draw(f1,'*'); l2.draw(f1,'*');
		INCLINED l3(5,5,26,5,false),l4(5,5,36,5,true);   l3.draw(f1,'*');	l4.draw(f1,'*');
		RECT r1(2,3,33,9),r2(2,2,36,9),r3(2,2,38,9);  r1.draw(f1,'*');	r2.draw(f1,'*');   r3.draw(f1,'*');
		RECT r4(14,3,48,5); r4.draw(f1,'*',true);	CIRCLE c1(4,51,8); c1.draw(f1,'*',PI/2,3*PI/2); INCLINED l5(3,3,52,12,true); l5.draw(f1,'*',true);
		RECT r5(9,3,59,5),r6(2,10,60,14),r7(9,3,68,5);  r5.draw(f1,'*',true);	r6.draw(f1,'*',true);  r7.draw(f1,'*',true);
		RECT r8(10,3,72,5),r9(10,3,84,5);	INCLINED l6(5,5,73,5);	r8.draw(f1,'*',true);	r9.draw(f1,'*',true);	l6.draw(f1,'*');
		//CIRCLE c1(3,17,17);	c1.draw(f1,'*',PI/2,3*PI/2);
		canvas.draw(f1);
		print_screen(f1);
	}
	return 0;
}