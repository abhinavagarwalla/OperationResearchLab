#include<iostream>
#include<cstdlib>
using namespace std;

void GetMat(double **A, int m, int n){
	cout << "Start entering the matrix: \n";
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin >> A[i][j];
		}
	}
}
	
void ShowMat(double **A, int m, int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
}

int main() {
	int i,n,m;

	cout << "Enter number of rows in payoff matrix: ";cin >> m;
	cout << "Enter number of cols in payoff matrix: ";cin >> n;

	double **A;

	A=(double **)malloc((m)*sizeof(double *));
	for(i=0;i<m;i++) 
		A[i]=(double *)malloc((n)*sizeof(double));

	GetMat(A, m, n);

	//M=(double *)malloc((n+m)*sizeof(double));
	//for(i=0;i<m+n;i++) M[i]=i;	
	double rowmin=10000, colmin=10000;
	for(int i=0;i<m;i++){
		rowmin = 10000;
		for(int j=0;j<n;j++){
			if(A[i][j] < rowmin)rowmin=A[i][j];
		}
		cout << "Rowmin: " << rowmin << " for row: " << i << endl;
		if(rowmin)
		for(int j=0;j<n;j++){
			A[i][j] -= rowmin;
		}
		ShowMat(A,m,n);
	}
	
	for(int j=0;j<n;j++){
		colmin = 10000;
		for(int i=0;i<m;i++){
			if(A[i][j] < colmin)colmin=A[i][j];
		}
		cout << "Colmin: " << colmin << " for col: " << j << endl;
		if(colmin)
		for(int i=0;i<m;i++){
			A[i][j] -= colmin;
		}
	}
	cout<<"\n";
	ShowMat(A,m,n);
	cout<<"\n";
	return 0;
}

