#include <iostream>
using namespace std;

Class Util{

	public:
		void matrixMultiply(int *A[10], int *B[10], int Ra, int Ca, int int Rb, int Cb, int *C[10]){
			if(Ca1!=Rb){
				cout << "\n The given matrices can't be multiplied.";
				return;
			}
			
			for(int i=0;i<Ra;i++){
				for(int j=0;j<Cb;j++){
					C[i][j]=0;
				}
			}

			for(int i=0;i<Ra;i++){
				for(int j=0;j<Ca;j++){
					for(int k=0;k<Rb;k++){
						C[i][j] += A[i][k]*B[k][j];
					}
				}
			}
						
		}

};
