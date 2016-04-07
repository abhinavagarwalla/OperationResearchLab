#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

#define SIZE 15
#define M 10000.0

int check(double a[][SIZE], int row, int col){
	int i, j, index = 0;
	double min = 0;
	bool t = false;

	for(j = 0; j < col; j++){
		if(a[row][j] < 0){
			t = true;
			if(a[row][j] < min){
				min = a[row][j];
				index = j;
			}
		}
	}

	if(t)
		return index;
	else
		return -2;
}

void print(double a[][SIZE], int row, int col){
	int i, j;

    for(i = 0; i < row; i++){
    	cout << "\n";
        for(j = 0; j < col; j++)
            cout << a[i][j] << "\t";
    }
}

void getMatrix(double a[][SIZE], int &row, int &col, int dc[SIZE]){
	int i, j, d, k;
	int c = col;
    for(i = 0; i < row; i++){
    	cout << "\n 1. for less than, 2. for bigger than, 3. for equal to" << endl;
    	cin >> d;

    	if(d == 1 ){
        	for(j = 0; j < c; j++)
            	cin >> a[i][j];
    	}
    	if(d == 3){
        	for(j = 0; j < c; j++)
            	cin >> a[i][j];
            dc[i] = 1;

    	}

    	if(d == 2){
    		for(j = 0; j < c; j++)
            	cin >> a[i][j];
            j = col;
            col += 1;
            for(k = 0; k < row; k++){
            	if(i == k){
            		a[k][j] = -1;
            		continue;
            	}
            	a[k][j] = 0;
            }
             dc[i] = 1;
    	}
    }
}

void setMatrix(double a[][SIZE], int row, int col){
	int i, j;
    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            cin >> a[i][j];
}

double a[SIZE][SIZE], b[SIZE][SIZE], temp[SIZE][SIZE], r[SIZE][SIZE];
int dc[SIZE];

int main(){
	int i, j, m, n, count;
	bool flag = true;
	int ob = 0;
	for(i = 0; i < SIZE; i++)
		dc[i] = 0;

	cout << "Enter the no of variables" << endl;
	cin >> n;
	cout << "Enter the no of equations" << endl;
	cin >> m;

	count = n;
	cout << "Enter the coefficients of the matrix" << endl;
	getMatrix(a, m, n, dc);
	cout << "Enter the constants of the equations" << endl;
	setMatrix(b, m, 1);
	cout << "Enter the coefficients and constant for the objective function" << endl;
	cout << "1. for Max and 2. for Min" << endl;
	cin >> ob ;
	setMatrix(r, 1, n + 1);

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			temp[i][j] = a[i][j];
	}

	for(i = 0; i < m; i++)
		temp[i][n] = b[i][0];

	for(i = 0; i <= n; i++){
		temp[m][i] = -r[0][i];
		for(j = 0; j < m; j++){
			if(dc[j] == 1){
				temp[m][i] -= (double)(M * temp[j][i]);
			}

		}
	}


	print(temp, m + 1, n + 1);

	while(check(temp, m, n) >= 0){
		int prow, pcol;
		double pivot, min = 88888999.0;
		pcol = check(temp, m, n);

		for(j = 0; j < n; j++){
			if(temp[m][pcol] == temp[m][j]){
				for(i = 0; i < m; i++){
					if((double)(temp[i][n] / temp[i][j]) < min && (double)(temp[i][n] / temp[i][j]) > 0){
						min = (double)(temp[i][n] / temp[i][j]);
						prow = i;
						pcol = j;
					}
				}
			}
		}

		pivot = temp[prow][pcol];

		cout << "\nPivot element is :" << pivot << endl;

		for(i = 0; i < m + 1; i++){
			for(j = 0; j < n + 1; j++){
				if(i != prow && j != pcol){
					temp[i][j] = temp[i][j] * pivot - temp[prow][j] * temp[i][pcol];
					temp[i][j] /= pivot;
				}
			}
		}

		for(j = 0; j < n + 1; j++){
			if(j != pcol){
				temp[prow][j] /= pivot;
			}
		}
		for(i = 0; i < m + 1; i++){
			if(i != prow)
				temp[i][pcol] /= -pivot;
		}

		temp[prow][pcol] = 1 / pivot;

		cout << "\nCurrent Simplex table is:" << endl;

		print(temp, m + 1, n + 1);

		for(i = 0; i < n; i++){
			if(temp[m][i] == 0){
				flag = false;
				break;
			}
		}
		if(flag == false)
			break;

	}

	if(flag)
		if(abs(temp[m][n]) >= M)
			cout << " No Solution" << endl;
		else{
			if(ob == 2)
				cout << "\nMaximum Value of LPP is :" << -temp[m][n] << endl;
			else
				cout << "\nMaximum Value of LPP is :" << temp[m][n] << endl;
		}
	else
		cout << "Infinite Solutions " << endl;
}
