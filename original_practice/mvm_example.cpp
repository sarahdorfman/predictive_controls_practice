#include <iostream>
#include <eigen3/Eigen/Dense>
#include <fstream>

//for continuous
Eigen::VectorXd m_func(double t,const Eigen::VectorXd &in)
{
	Eigen::VectorXd out;

	//from my solution, I subsituted B to represent my K for clarity
	Eigen::MatrixXd A(4, 4);
	A << 	0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1,
		0, 0, 0, 0;
	Eigen::VectorXd B(4);
	B <<	0, 0, 0, -9.8;

	out= A* in + B;
	return(out);
}

// for discrete
Eigen::VectorXd disc_func(double h, const Eigen::VectorXd &in){

	Eigen::VectorXd out;

	//from my solution, I subsituted B to represent my K for clarity
	Eigen::MatrixXd A(4, 4);
	A << 	1, h, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, h,
		0, 0, 0, 1;
	Eigen::VectorXd B(4);

	double gh = -9.8*h;
	B <<	0, 0, 0, gh;

	out= A* in + B;
	return(out);

}


// for continuous
Eigen::VectorXd run(double t, const Eigen::VectorXd &in, double h)
{
        Eigen::VectorXd k1, k2, k3, k4;
        k1 = m_func(t, in);
        k2 = m_func(t + h / 2, in + (h / 2) * k1);
        k3 = m_func(t + h / 2, in + (h / 2) * k2);
        k4 = m_func(t + h, in + h * k3);

        return in + h* (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}




// for continuous
void solve(const Eigen::VectorXd &x0,double h,double time)
{
        Eigen::IOFormat fmt(8, 0, ", ", "\t", "", "", "", "");
	std::ofstream myfile;
	myfile.open ("CONT");


	int i;
	double  t;
	t=0;
	Eigen::VectorXd x=x0;

	while(t<time){
		x=run(t,x,h);
		myfile<<t<<"\t"<<x.format(fmt)<<std::endl;
		t=t+h;
	}
}

void solve_discrete(const Eigen::VectorXd &x0,double h,double time)
{
        Eigen::IOFormat fmt(8, 0, ", ", "\t", "", "", "", "");
	std::ofstream myfile;
	myfile.open ("DISC");


	int i;
	double  t;
	t=0;
	Eigen::VectorXd x=x0;

	while(t<time){
		x=disc_func(h,x);
		myfile<<t<<"\t"<<x.format(fmt)<<std::endl;
		t=t+h;
	}

}

int main(void)
{

	Eigen::VectorXd x(4);
	// I will say start is 0,0 with random speed in x and y
	x<<0,3,0,1;
	solve(x,.01,6.5);
	solve_discrete(x,.01,6.5);

}

