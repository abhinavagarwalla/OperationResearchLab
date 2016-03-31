#include <iostream>
using namespace std;

float mat[10][10];
float Bnew[10][10];
float E[10][10], B[10][10];
float e[10],n[10];
int main(){
    int R=0;int C=0;
    int count=0;

    cout << "Enter the number of rows: ";
    cin >> R;
    cout << "Enter the number of columns: ";
    cin >> C;

    cout << " Enter in matrix form: \n";
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cin >> mat[i][j];
            if(i==j){
                B[i][j]=1;E[i][j]=1;
            }
            else{
                B[i][j]=0;E[i][j]=0;
            }
        }
    }

    //start the iterative process
    for(int r=0;r<C;r++){
        
        int flag=1;
        for(int i=0;i<R;i++){
            if(mat[r][r]!=1){flag=0;break;}
            if(i!=r && mat[i][r]!=0){flag=0;break;}
        }
        cout << "Flag is " << flag;
        if(flag)continue;
        count++;

        //Computing e
        for(int i=0;i<R;i++){
            e[i]=0;
            for(int j=0;j<C;j++){
                e[i] += B[i][j]*mat[j][r];
            }
        }

        //Computing n
        for(int i=0;i<R;i++){
            if(i==r)n[i] = 1.0/e[r];
            else n[i] = -e[i]/e[r];
        }

        //Setting E to identity
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                E[i][j]=0;
                if(i==j)E[i][j]=1;
            }
        }

        //Setting rth column to n
        for(int i=0;i<R;i++)E[i][r]=n[i];
        
        cout << " \n\n Printing E" << count << ": \n";
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                cout << E[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        //Computing B^-1
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                Bnew[i][j]=0; 
                for(int k=0;k<R;k++){
                    Bnew[i][j] += E[i][k]*B[k][j];
                }
            }
        }
        
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                B[i][j] = Bnew[i][j];
            }
        }
        
        cout << "Intermediate Inv(B" << count << ")\n\n";
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "Printing Final Inverse\n\n";
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
        
    return 0;
}
