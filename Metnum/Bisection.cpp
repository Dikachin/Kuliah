#include <bits/stdc++.h>

using namespace std;

//persamaan polinom derajat 2
float fx(float x)
{
	return x*x - 7*x + 12;
}
/*fungsi untuk memastikan fx(x[0]) bernilai negatif
  dan fx(x[1]) bernilai positif */
void swapx(float x[])
{
	if (fx(x[0]) > fx(x[1]))
	{
		float tmp=x[0];
		x[0]=x[1];
		x[1]=tmp;
	} 
}

int main()
{
	float x[2]; //x0 dan x1
	srand(time(NULL));

	// random nilai tebakan
	x[0]=10000;//((double)(rand()%11))/2.0; 
	x[1]=3.5;//((double)(rand()%11))/2.0;
	while (fx(x[0])*fx(x[1]) > 0 || x[0]==x[1])
	{
		x[0]=((double)(rand()%11))/2.0;
		x[1]=((double)(rand()%11))/2.0;
	}

	swapx(x);
	printf("X0 = %.7lf. X1 = %.7lf\n",x[0],x[1]);

	//nilai tebakan dari akar persamaan
	float xmid = (x[0]+x[1])/2.0;

	//algoritma bisection
	int cnt=0;
	while (fabs(fx(xmid))>0.0000001)
	{
		printf("Xmid = %.7lf. F(Xmid) = %.7lf\n",xmid,fx(xmid));

		if (-1*fx(xmid)>0.0000001) x[0]=xmid;
		else if (fx(xmid)>0.0000001) x[1]=xmid;
		xmid = (x[0]+x[1])/2.0;

		printf("X0 = %.7lf. X1 = %.7lf\n",x[0],x[1]);
		cnt++;
	}
	cout<<cnt<<endl;
	printf("X = %.7lf. f(X) = %.7lf ",xmid,fx(xmid));

}