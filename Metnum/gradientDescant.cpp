//exact Line Search
//Persamaan 5x1^2 + 4x2^2 + 3x3^2 + x1 + x2 + x3
#include <bits/stdc++.h>
#define error (float)1e-7
#define nParameter (int)3

float c[nParameter] = {3,4,5};

using namespace std;

//fungsi fx
float f(float x[])
{
	float ans=0;
	for (int i=0; i<nParameter; i++)
	{
		ans+=c[i]*x[i]*x[i];
		ans+=x[i];
	}
	return ans;
}

//mencari nilai besaran vektor dari gradient
float skalarGradient(float gradient[]) {
	float ans = 0;
	for (int i=0;i<nParameter;i++)
		ans = ans + gradient[i]*gradient[i];
	return sqrt(ans);
}

float hitungGradient(float x,int i)
{
	return 2*c[i]*x+1;
}

//mencari nilai stepsize
float htiungStepsize(float x[],float gradient[]) {
	float A=0,B=0;
	for (int i=0; i<nParameter; i++)
	{
		A+=(2*c[i]*x[i]*gradient[i]+gradient[i]);
		B+=(2*c[i]*gradient[i]*gradient[i]);
	}
	return A/B;
}

int main()
{
	float x[] = {-1000,-1000,-1000}; //inisial solusi
	float gradient[nParameter] = {1,1,1}; //inisial gradien awal
	int count=0;
	FILE *fp;
	printf("%s\n", );
	fp=fopen("wkwk.csv","w+");
	while (skalarGradient(gradient) > error)
	{
		count++;

		//menghitung gradien yang baru
		for (int i=0;i<nParameter;i++)
			gradient[i] = hitungGradient(x[i],i);

		//menghitung stepsize
		float stepsize=htiungStepsize(x,gradient);
		//printf("stepsize ke-%d adalah%.7f\n",count,stepsize);

		//menghitung nilai xi yang baru
		for (int i=0; i<nParameter;i++)
			x[i] = x[i] - stepsize*gradient[i];

		//mencetaik nilai xi dan gradientnya
		//for (int i=0; i<nParameter; i++)
			//printf("x%d adalah %.7f dan gradientnya adalah %.7f\n",i,x[i],gradient[i]);
			fprintf(fp,"%d;%.7f;%.7f;%.7f;%.7f;%.7f;%.7f;%.7f;%.7f\n",count,x[0],x[1],x[2],gradient[0],gradient[1],gradient[2],stepsize,f(x));
		//printf("%d \n",count,stepsize,f(x));
	}
	fclose(fp);
	//mencetak nilai optimum dari fungsi yang ditentukan
	//printf("f(%.7f,%.7f,%.7f)=%.7f\n",x[0],x[1],x[2],f(x));
}
