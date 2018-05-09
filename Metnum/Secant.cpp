#include <bits/stdc++.h>
using namespace std;

//persamaan polinom derajat 2
double fx(double x)
{
	return x*x - 7*x + 12;
}
void swapx(double x[])
{
	if (fx(x[0]) > fx(x[1]))
	{
		double tmp=x[0];
		x[0]=x[1];
		x[1]=tmp;
	} 
}


int main()
{
	double x[2]; //x0 dan x1
	srand(time(NULL));

	// random nilai tebakan
	x[0]=20;//((double)(rand()%11))/2.0;
	x[1]=3.5000000;//((double)(rand()%11))/2.0;
	while (fx(x[0])*fx(x[1]) > 0 || x[0]==x[1]) 
	{
		x[0]=((double)(rand()%11))/2.0;
		x[1]=((double)(rand()%11))/2.0;
	}

	swapx(x);
	//printf("X0 = %.7lf. X1 = %.7lf\n",x[0],x[1]);

	//gradient
	double m = (fx(x[1])-fx(x[0]))/(x[1]-x[0]);

	//nilai tebakan dari akar persamaan
	double xnew = x[0] - fx(x[0])/m;
	int cnt=0;
	//Algoritma Regula False Method

	while (fabs(fx(xnew))>0.0000001)
	{
		//printf("Xmid = %.7lf. F(Xmid) = %.7lf\n",xnew,fx(xnew));
		printf("%.7lf\n",fx(x[0])/m);
		if (-1*fx(xnew)>0.0000001) x[0]=xnew;
		else if (fx(xnew)>0.0000001) x[1]=xnew;
		m = (fx(x[1])-fx(x[0]))/(x[1]-x[0]);
		xnew = x[0] - fx(x[0])/m;
		//printf("X0 = %.7lf. X1 = %.7lf\n",x[0],x[1]);
		cnt++;
	}
	printf("%.7lf\n",fx(x[0])/m);
	printf("X = %.7lf. f(X) = %.7lf ",xnew,fx(xnew));
	cout<<cnt<<endl;
}  