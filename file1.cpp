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
		this->matrix = new int*[y];
		for(int i=0;i<y;i++){
			this->matrix[i]=new int[x];
			for (int j=0;j<x;j++)
				this->matrix[i][j]=mat[i][j];
		}
		this->x=x;
		this->y=y;




	}


	image(int x, int y){
		this->matrix = new int*[y];
		for(int i=0;i<y;i++){
			this->matrix[i]=new int[x];
			for (int j=0;j<x;j++)
				this->matrix[i][j]=0;
		}
		this->x=x;
		this->y=y;




	}


	void print_image(){

		for(int i=0; i<this->y;i++){
			for(int j=0;j<this->x;j++)
				cout<<this->matrix[i][j]<<" ";
			cout<<endl;
		}


	}

	void set_points(vector <int*> points){
		for(int i=0; i<points.size();i++){

			this->matrix[points[i][1]][points[i][0]]=1;

		}

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

	vector<int*> get_obj(int r){
		vector<int*> p;
		vector<int*> p1;
		int c[2];
		int *t;
		
		

		for(int i=0;i<this->y;i++){

			for(int j=0;j<this->x;j++){
				
				p1.clear();
				for(int i1=0;i1<=r;i1++)
					for(int j1=0;j1<=r;j1++){
						if((j-j1>=0)&&(i-i1>=0)){
							
							if((this->rad_prov(j,i,j-j1,i-i1,r))&&(this->matrix[i-i1][j-j1]==1)){
								
								t=new int[2];
								t[0]=j-j1;
								t[1]=i-i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}



						if((j+j1<this->x)&&(i+i1<this->y)){
							if((this->rad_prov(j,i,j+j1,i+i1,r))&&(this->matrix[i+i1][j+j1]==1)){
								
								t=new int[2];
								t[0]=j+j1;
								t[1]=i+i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}
						
					}

				if(p1.size()>p.size()){
					p=p1;
					c[0]=j;
					c[1]=i;
				}


			}
		}





		cout<<"Центр окружности: "<<endl<<"x= "<<c[0]<<" y="<<c[1]<<endl;


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

obj=i1->get_obj(r);
cout<<"Точки объекта:"<<endl;
for(int i=0;i<obj.size();i++)
	cout<<"x= "<<obj[i][0]<<" y= "<<obj[i][1]<<endl;

cout<<"Центр масс:"<<endl;

s=get_mass_centr(obj);

cout<<"x= "<<s[0]<<" y= "<<s[1]<<endl;

	return 0;
}
