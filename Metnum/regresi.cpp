#include <bits/stdc++.h>
#define ii pair<double,double>
#define x first
#define y second
#define pb push_back
#define mp make_pair

using namespace std;
double matrix[100][101];
vector<double> gaussjordan(int N){
	for (int k=0; k<N; k++){
		int i_max=k;
        int v_max=matrix[i_max][k];

        for (int i=k+1; i<N; i++)
            if (abs(matrix[i][k])>v_max)
                v_max=matrix[i][k],i_max=i;
        if (i_max!=k)
            for (int j=0; j<=N; j++) {
        		double temp=matrix[k][j];
        		matrix[k][j]=matrix[i_max][j];
        		matrix[i_max][j]=temp; 
        	}
    	for (int i=k+1; i<N; i++) {
            double f=matrix[i][k]/matrix[k][k];
            for (int j=k+1; j<=N; j++)
                matrix[i][j]-=matrix[k][j]*f;
            matrix[i][k]=0;
        }
	}

	vector<double> x(N,0);
    for (int i=N-1;i>=0;i--) {
        x[i]=matrix[i][N];
        for (int j=i+1; j<N; j++) {
            x[i]-=matrix[i][j]*x[j];
        }
 
        x[i]=x[i]/matrix[i][i];
    }
   	return x;
}

//y = a + bx
ii regresiLinear(vector< ii > kord){
	double sumxi=0;
	double sumyi=0;
	double sumxi2=0;
	double sumxiyi=0;
	int N = kord.size();
	for (int i=0; i<N; i++){
		sumxi+=kord[i].x;
		sumyi+=kord[i].y;
		sumxi2+=kord[i].x*kord[i].x;
		sumxiyi+=kord[i].x*kord[i].y;
	}
	double aa = (double)N*sumxiyi - sumxi*sumyi;
	double bb = (double)N*sumxi2 - sumxi*sumxi;
	double b = aa/bb;
	double a = sumyi/(double)N - b*sumxi/(double)N;
	return mp(a,b);
}

//y = a*x^b
ii berpangkatForm(vector< ii > kord) {
	double sumxi=0;
	double sumyi=0;
	double sumxi2=0;
	double sumxiyi=0;
	int N = kord.size();
	for (int i=0; i<N; i++){
		if (kord[i].x!=0){
			sumxi+=log10(kord[i].x);
			sumxi2+=log10(kord[i].x)*log10(kord[i].x);
		}
		if (kord[i].y!=0)
			sumyi+=log10(kord[i].y);
		if (kord[i].y!=0 && kord[i].x!=0)
			sumxiyi+=log10(kord[i].x)*log10(kord[i].y);
	}
	double aa = (double)N*sumxiyi - sumxi*sumyi;
	double bb = (double)N*sumxi2 - sumxi*sumxi;
	double b = aa/bb;
	double A = sumyi/(double)N - b*sumxi/(double)N;
	double a = pow(10,A);
	return mp(a,b);
}
//y = ae^bx
ii exponesialForm(vector< ii > kord) {
	double sumxi=0;
	double sumyi=0;
	double sumxi2=0;
	double sumxiyi=0;
	int N = kord.size();
	for (int i=0; i<N; i++){

		sumxi+=kord[i].x;
		if (kord[i].y!=0)
			sumyi+=log(kord[i].y);
		sumxi2+=kord[i].x*kord[i].x;
		if (kord[i].y!=0)
			sumxiyi+=kord[i].x*log(kord[i].y);
	}
	double aa = (double)N*sumxiyi - sumxi*sumyi;
	double bb = (double)N*sumxi2 - sumxi*sumxi;
	double b = aa/bb;
	double A = sumyi/(double)N - b*sumxi/(double)N;
	double a = exp(A);
	return mp(a,b);
}

//polinomial orde r
vector<double> polinomialForm(vector< ii > kord, int orde) {
	for (int i=0; i<orde; i++){
		for (int j=0; j<orde+1; j++){
			if (j==orde)
				for (int k=0; k<kord.size(); k++)
					matrix[i][j]+=pow(kord[k].x,double(i))*kord[k].y;
			else
				for (int k=0; k<kord.size(); k++)
					matrix[i][j]+=pow(kord[k].x,(double)(i+j));
		}
	}
	return gaussjordan(orde);
}

double error(ii hasilMethod, vector< ii > kord, int method) {
	int N = kord.size();
	double sumy=0;
	if (method==0)
		for (int i=0; i<N; i++){
			double yreg = hasilMethod.first + hasilMethod.second*kord[i].x;
			sumy+=fabs(yreg-kord[i].y)/kord[i].y;
		}
	if (method==1)
		for (int i=0; i<N; i++){
			double yreg = hasilMethod.first*pow(kord[i].x,hasilMethod.second);
			sumy+=fabs(yreg-kord[i].y)/kord[i].y;
		}
	if (method==2)
		for (int i=0; i<N; i++){
			double yreg = hasilMethod.first*exp(kord[i].x*hasilMethod.second);
			sumy+=fabs(yreg-kord[i].y)/kord[i].y;
		}
	return sumy/(double)(N);
}

double pFormError(vector<double> pF, vector< ii > kord) {
	int N=kord.size();
	double sumy=0;
	for (int i=0; i<N; i++){
		double yreg=0;
		for (int j=0; j<(int)pF.size(); j++){
			yreg+= pF[j]*pow(kord[i].x,j);
		}
		sumy+=fabs(yreg-kord[i].y)/kord[i].y;
	}
	return sumy/(double)(N);
}

int main(){

	int N; cin>>N;
	vector< ii > kord;
	for (int i=0; i<N; i++){
		double x,y; cin>>x>>y;
		kord.pb(mp(x,y));
	}
	
	ii rL = regresiLinear(kord);
	if (rL.second>0)
		printf("y = %.6f + %.6fx\n",rL.first,rL.second);
	else 
		printf("y = %.6f - %.6fx\n",rL.first,fabs(rL.second));

	ii bF = berpangkatForm(kord);
	printf("y = %.6fx^%.6f\n",bF.first,bF.second);

	ii eF = exponesialForm(kord);
	printf("y = %.6fe^%.6fx\n",eF.first,eF.second);

	int orde; cin>>orde;
	vector<double> pF = polinomialForm(kord,orde+1);
	printf("y = %.6f ",pF[0]);
	for (int i=1; i<(int)pF.size(); i++){
		if (pF[i]<0)
			printf("- %.6fx^%d ",fabs(pF[i]),i);
		else printf("+ %.6fx^%d ",pF[i],i);
	}
	printf("\n");

	double rLerror = error(rL,kord,0);
	double bFerror = error(bF,kord,1);
	double eFerror = error(eF,kord,2);
	double pFerror = pFormError(pF,kord);
	printf("%.6f %.6f %.6f %.6f\n",rLerror,bFerror,eFerror,pFerror);
}