# Zvonkin
#include <cstdio>
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

class image{
private:
	int **matrix;
	int x,y;

public:
	image(int x, int y, int **mat){
		this->matrix = new int*[x];
		for(int i=0;i<x;i++){
			this->matrix[i]=new int[y];
			for (int j=0;j<y;j++)
				this->matrix[i][j]=mat[i][j];
		}
		this->x=x;
		this->y=y;




	}


	image(int x, int y){
		this->matrix = new int*[x];
		for(int i=0;i<x;i++){
			this->matrix[i]=new int[y];
			for (int j=0;j<y;j++)
				this->matrix[i][j]=0;
		}
		this->x=x;
		this->y=y;




	}

	int get_x(){
		return this->x;

	}

	int get_y(){

		return this->y;

	}

	int get_p(int x,int y){

		return this->matrix[x][y];
	}

	void print_image(){

		for(int i=0; i<this->x;i++){
			for(int j=0;j<this->y;j++)
				cout<<this->matrix[i][j]<<" ";
			cout<<endl;
		}


	}

	void set_points(vector <int*> points){
		for(int i=0; i<points.size();i++){

			this->matrix[points[i][0]][points[i][1]]=1;

		}

	}


	void draw_rad(int r, int *t){
		int xs,xf,ys,yf;

		if(t[0]-r<0)
			xs=0;
		else 
			xs=t[0]-r;

		if(t[1]-r<0)
			ys=0;
		else 
			ys=t[1]-r;

		if(t[0]+r>=this->get_x())
			xf=this->get_x();
		else 
			xf=t[0]+r;

		if(t[1]+r>=this->get_y())
			yf=this->get_y();
		else 
			yf=t[1]+r;		



		
		for(int i=xs;i<xf;i++)
			for(int j=ys;j<yf;j++){
				if(this->matrix[i][j]==0){
				
				if((i==xs)||(i==xf-1))
					this->matrix[i][j]=3;	

				if((j==ys)||(j==yf-1))
					this->matrix[i][j]=3;

				}
			}
			

		this->matrix[t[0]][t[1]]=2;

	}

	int rad_prov(int x1, int y1, int x2, int y2,int r){
		double r1=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
		if(r1>(double)r) return 0;
		return 1;
	}


	int prov(vector<int*> p, int*t){

	for(int i=0;i<p.size();i++)
		if((t[0]==p[i][0])&&(t[1]==p[i][1]))
			return 0;

	return 1;
	}

	vector<int*> get_obj(int r,int fl){
		vector<int*> p;
		vector<int*> p1;
		int *c=new int[2];
		int *t;
		
		

		for(int i=0;i<this->x;i++){

			for(int j=0;j<this->y;j++){
				
				p1.clear();
				for(int i1=0;i1<=r;i1++)
					for(int j1=0;j1<=r;j1++){
						if((j-j1>=0)&&(i-i1>=0)){
							
							if((this->rad_prov(j,i,j-j1,i-i1,r))&&(this->matrix[i-i1][j-j1]==1)){
								
								t=new int[2];
								t[1]=j-j1;
								t[0]=i-i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}



						if((j+j1<this->y)&&(i+i1<this->x)){
							if((this->rad_prov(j,i,j+j1,i+i1,r))&&(this->matrix[i+i1][j+j1]==1)){
								
								t=new int[2];
								t[1]=j+j1;
								t[0]=i+i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}
						
					}

				if(p1.size()>p.size()){
					p=p1;
					c[1]=j;
					c[0]=i;
				}


			}
		}


			


		
		if(fl!=0){
			p.clear();
			p.push_back(c);


		}
		else cout<<"Центр окружности: "<<endl<<"x= "<<c[0]<<" y="<<c[1]<<endl;
		return p;
	}

};

vector<int*> read_coords( char* filename){
	vector<int*> p;
	
	
	ifstream file(filename);
	int x,y;
	int *t;
	
	while (!file.eof()){
		file>>x>>y;
		t=new int[2];
		t[0]=x;
		t[1]=y;
		p.push_back(t);
	}
	
	return p;
};



int* get_mass_centr(vector<int*> obj){
	int *t=new int[2];
	double x=0;
	double y=0;
	for(int i=0;i<obj.size();i++){
		x+=obj[i][0];
		y+=obj[i][1];

	}
	x=x/obj.size();
	y=y/obj.size();

	t[0]=(int)x;
	t[1]=(int)y;

	return t;
}


int* get_size(vector <int*> p){
	int *s=new int[2];
	s[0]=0;
	s[1]=0;

	for(int i=0; i<p.size();i++)
	{
		if(s[0]<p[i][0]) s[0]=p[i][0];
		if(s[1]<p[i][1]) s[1]=p[i][1];

	}

	return s;
}

void draw_points(image* i1){
	
	char fn[]="plain.pnm";
	ofstream file(fn);

	file<<"P3"<<endl;
	file<<i1->get_y()<<" "<<i1->get_x()<<endl;
	file<<255<<endl;

	


	for(int i=0; i<i1->get_x();i++){
			for(int j=i1->get_y()-1;j>=0;j--){


				if(i1->get_p(i,j)!=0)
					file<<0<<" "<<0<<" "<<0<<endl;
				else
					file<<255<<" "<<255<<" "<<255<<endl;
		}
			
	}


	file.close();

}


void draw_obj(image* i1,int r){
	char fn[]="obj.pnm";
	ofstream file(fn);
	vector<int*> p;
	int *t;


	t=i1->get_obj(r,1)[0];

	i1->draw_rad(r,t);

	file<<"P3"<<endl;
	file<<i1->get_y()<<" "<<i1->get_x()<<endl;
	file<<255<<endl;

	for(int i=0; i<i1->get_x();i++){
			for(int j=i1->get_y()-1;j>=0;j--){


				if(i1->get_p(i,j)==1)
					file<<0<<" "<<0<<" "<<0<<endl;

				if(i1->get_p(i,j)==0)
					file<<255<<" "<<255<<" "<<255<<endl;

				if(i1->get_p(i,j)==2)
					file<<100<<" "<<0<<" "<<0<<endl;
				if(i1->get_p(i,j)==3)
					file<<100<<" "<<100<<" "<<100<<endl;
		}
			
	}



	file.close();

}


int main(int argc, char *argv[]){
char fn[]="to4ki";
int r=4; //radius

vector<int*> p;
vector<int*> obj;
int *s=new int[2];


p=read_coords(fn);
s=get_size(p);

image *i1=new image(s[0]+1,s[1]+1);

i1->set_points(p);

cout<<"Радиус: "<<r<<endl;

obj=i1->get_obj(r,0);
cout<<"Точки объекта:"<<endl;
for(int i=0;i<obj.size();i++)
	cout<<"x= "<<obj[i][0]<<" y= "<<obj[i][1]<<endl;

cout<<"Центр масс:"<<endl;

s=get_mass_centr(obj);

cout<<"x= "<<s[0]<<" y= "<<s[1]<<endl;

draw_points(i1);
draw_obj(i1,r);

	return 0;
}
