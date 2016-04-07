#include<iostream>
#include<stdlib.h>

using namespace std;

void showMatrix(double** A,int m,int n) {
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++)
			cout<<A[i][j]<<"\t";
		cout<<"\n";
	}
}

void mult(double **R,double **A,double **B,int a,int b,int c) {
	for(int i=0;i<a;i++) {
		for(int j=0;j<c;j++) {
			R[i][j]=0;
			for(int k=0;k<b;k++) R[i][j]+=A[i][k]*B[k][j];
		}
	}
}

int entering_variable(double **A,double **M,double*Z,int *T,int m,int n) {
	double **Y;
	Y=(double **)malloc(sizeof(double*));
	Y[0]=(double *)malloc(m*sizeof(double));
	double **Cb;
	Cb=(double**)malloc(sizeof(double*));
	Cb[0]=(double*)malloc(m*sizeof(double));
	for(int i=0;i<m;i++) Cb[0][i]=Z[T[i+n]];
	mult(Y,Cb,M,1,m,m);
	double min=1;
	int index=-1;
	for(int i=0;i<n;i++) {
		double sum=0;
		for(int j=0;j<m;j++)
			sum+=A[j][T[i]]*Y[0][j];
		sum-=Z[T[i]];
		if((sum<0)&&(sum<min)) {
			sum=min;
			index=i;
		}
	}
	return index;
}

int departing_variable(double **A,double **B,double **M1,double **Xb,int *T,int m,int n,int e) {
	mult(Xb,M1,B,m,m,1);
	double **Alj,**Pj;
	Alj=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) Alj[i]=(double*)malloc(sizeof(double));
	Pj=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) {Pj[i]=(double*)malloc(sizeof(double)); Pj[i][0]=A[i][T[e]];}
	mult(Alj,M1,Pj,m,m,1);
	int index=-1;
	double min=0,sum;
	for(int i=0;i<m;i++) {
		if((Alj[i][0]<=0)||(Xb[i][0]<=0)) continue;
		else {
			sum=Xb[i][0]/Alj[i][0];
			if((index==-1)||(sum<min)) {min=sum;index=i;}
		}
	}
	return index;
}

void result(double *Z,int *T,double **Xb,int m,int n) {
	double r=0;
	for(int i=0;i<m;i++) cout<<"X"<<T[n+i]+1<<" = "<<Xb[i][0]<<"\n";
	for(int i=0;i<m;i++) {
		r+=Xb[i][0]*Z[T[n+i]];
	}
	cout<<"Other variables are equal to zero"<<endl;
	cout<<"\nMax= "<<r<<endl;
}

double** MatrixMultiplication(double **M,double **N,int n) {
	int i,j,k;
	double **R;
	R=(double **)malloc(n*sizeof(double *));
	for(i=0;i<n;i++)
		R[i]=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			R[i][j]=0;
			for(k=0;k<n;k++) R[i][j]+=M[i][k]*N[k][j];
		}
	}
	return R;
}

void vectorMultiplication(double *C,double **M,double *C1,int n) {
	for(int i=0;i<n;i++) {
		C[i]=0;
		for(int j=0;j<n;j++)	C[i]+=M[i][j]*C1[j];
	}
}


void inverse(double **A,double **B,int n) {
	double **M,*C,**E,*C1,temp;
	int i,j;
	M=(double **)malloc(n*sizeof(double *));
	for(i=0;i<n;i++)
		M[i]=(double*)malloc(n*sizeof(double));
	E=(double **)malloc(n*sizeof(double *));
	for(i=0;i<n;i++)
		E[i]=(double*)malloc(n*sizeof(double));
	C=(double*)malloc(n*sizeof(double));
	C1=(double*)malloc(n*sizeof(double));

	for(i=0;i<n;i++)
		for(j=0;j<n;j++) {
			if(i==j) {E[i][j]=1; M[i][j]=1;}
			else {E[i][j]=0; M[i][j]=0;}
		}

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++)   C1[j]=A[j][i];
		vectorMultiplication(C,M,C1,n);
		temp=C[i];
		for(j=0;j<n;j++) {
			if(j==i) C[j]=1/temp;
			else C[j]=(-1)*(C[j]/temp);
		}
		for(j=0;j<n;j++) {
			if(i!=0)  {
				if((i-1)==j) E[j][i-1]=1;
				else E[j][i-1]=0;
			}
			E[j][i]=C[j];
		}
		M=MatrixMultiplication(E,M,n);
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			B[i][j]=M[i][j];
}

void revise(double**A,double**B,double*Z,int m,int n){
	int *T;
	T=(int*)malloc((n+m)*sizeof(int));
	for(int i=0;i<n+m;i++) T[i]=i;//keeping track of variable numbers
	double **M,**M1;
	M=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) M[i]=(double*)malloc(m*sizeof(double));
	M1=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) M1[i]=(double*)malloc(m*sizeof(double));
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++) {if(i==j) M[i][j]=1; else M[i][j]=0;}
	double **Xb;
	Xb=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) Xb[i]=(double*)malloc(sizeof(double));
	while(1) {
		int e;cout<<"\n";
		cout<<"B= "<<endl;
		showMatrix(M,m,m);
		inverse(M,M1,m);cout<<"\n";
		cout<<"B^-1 = "<<endl;
		showMatrix(M1,m,m);
		e=entering_variable(A,M1,Z,T,m,n);
		//cout<<"Entering Variable = X"<<T[e]+1<<endl;
		if (e<0) {mult(Xb,M1,B,m,m,1);result(Z,T,Xb,m,n); return;}
		int d;
		d=departing_variable(A,B,M1,Xb,T,m,n,e);
		//cout<<"Departing Variable = X"<<T[d+n]+1<<endl;
		if(d<0) {cout<<"\ninfeasible\n"; return;}
		for(int i=0;i<m;i++) M[i][d]=A[i][T[e]];
		d+=n;
		//swapping basic and non-basic variables
		int swap;
		swap=T[d];
		T[d]=T[e];
		T[e]=swap;
	}
}

int main() {
	int n,m;
	cout<<"Enter the number of Variables: :"<<endl;   	cin>>n;
	cout<<"Enter the number of equations: "<<endl;	cin>>m;
	cout<<"Enter the coefficients of the Objective Function (for minimisation, enter the coefficients multiplied by -1): "<<endl;
	double *Z;
	Z=(double*)malloc((n+m)*sizeof(double));
	for(int i=0;i<n;i++) cin>>Z[i];
	for(int i=n;i<n+m;i++) Z[i]=0;
	cout<<"Enter the equations lhs:"<<endl;
	double **A;
	A=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) A[i]=(double *)malloc((n+m)*sizeof(double));
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) cin>>A[i][j];
		for(int j=n;j<n+m;j++) {if(i==(j-n)) A[i][j]=1; else A[i][j]=0;}
	}
	cout<<"Enter the constants rhs:"<<endl;
	double **B;
	B=(double**)malloc(m*sizeof(double*));
	for(int i=0;i<m;i++) B[i]=(double *)malloc(sizeof(double));
	for(int i=0;i<m;i++) cin>>B[i][0];
	revise(A,B,Z,m,n);
}
