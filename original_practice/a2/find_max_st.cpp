
// MvM,  find max in moisy data, "read between the noisy lines"
// data is written you so you can plot it
// There is a naive max, run it several times and you see how it jumps

#include <iostream>
#include <string>
#include <random>

#include <eigen3/Eigen/Dense>


#define MAX_NUM 2014

#define MIN .12

double x_val[MAX_NUM];
double y_val[MAX_NUM];


void make_data(int num)
{

  if(num>MAX_NUM)return;

  std::random_device rd;  //FOR SEED
  std::mt19937 generator(rd()); 
  std::uniform_real_distribution<double> distribution_x(-5,5);
  std::normal_distribution<double> distribution_y(0,1);


  for (int i=0; i<num; ++i) {
     x_val[i]= distribution_x(generator);
     y_val[i]= -(x_val[i]-MIN)*(x_val[i]-MIN) + distribution_y(generator);
  }
}


void print_data(const char* f_name,int num)
{
	int i;
	FILE* out_file=fopen(f_name,"w");
	for(i=0;i<num;i++){
		fprintf(out_file,"%f\t%f\n",x_val[i],y_val[i]);
	}

}

//native, find largest y and return corresponding x
double find_max_naive(double* x,double* y,int num)
{
	int i;
	double max_x,max_y;
	max_y=y[0];
	for(i=1;i<num;i++){
		if(y[i]>max_y){
			max_y=y[i];
			max_x=x[i];
		}
	}
	return(max_x);

}

// YOU IMPLEMENT  THIS, ~15-20 lines ...

//fit y=a*x^2+b*x+c lls and return -b/2*a as  the position x that maximizes the fit.
// The other code examples I gave have the pieces needed.
double find_max(double* x,double* y,int num)
{

	Eigen::MatrixXd A(num,3);
	Eigen::VectorXd Y(num);

	for (int i = 0; i<num; i++){
		double x_val = *x;
		A(i,0) = 1;
		A(i,1) = x_val;
		A(i,2) = x_val*x_val;
		Y(i) = *y;
		y++;
		x++;
	}

	Eigen::MatrixXd At = A.transpose();
	
	// I use gen AI (Claude Sonnet) for these 3 lines	
	Eigen::MatrixXd AtA = At*A; // my note: A transpose by A (left side of equation)
	Eigen::MatrixXd Aty = At*Y; // my note: A transpose by y (rigth side of equation)
	Eigen::VectorXd B = AtA.ldlt().solve(Aty); // my note: ldlt is a decomposition function, and then solve is called

	//std::cout << B<<std::endl;

	double b = B(1);
	double a = B(2);
	
	double min = (-b)/(2*a);

	return(min);
}



int main(void)
{

	// DATA is in global x_val,y_val ...
	make_data(256);
	print_data("DATA",256);


	const double n_max=find_max_naive(x_val,y_val,256);
	const double a_max=find_max(x_val,y_val,256);

	printf(" TURE MAX %f  Naive:  %f  New Max %f \n",MIN,n_max,a_max);

	return(0);
}
