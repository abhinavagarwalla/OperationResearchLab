#include <iostream>
using namespace std;

class Simplex{

	int neqn;
	//int nlec;
	//int ngec;
	//int neec;
	int nvar;

	float obj[10];
	float mat[10][10];
	float tableau[10][10];
	float b[10];
	int d[10];
	int dmap[10];

	public:
	Simplex(){
		for(int i=0;i<10;i++)dmap[i]=-1;
	}

	void init(){
		cout << "\nEnter the number of variables: ";
		cin >> nvar;
		
		/*cout << "\nEnter the number of equations with <= sign: ";
		cin >> nlec;
		
		cout << "\nEnter the number of equations with = sign: ";
		cin >> neec;

		cout << "\nEnter the number of equations with >= sign: ";
		cin >> ngec;*/

		cout << "\nEnter the number of equations: ";
		cin >> neqn;
		//neqn = nlec + ngec + neec;

	}

	void setMatrix(){
		cout << "Enter the constraints matrix: ";
		for(int i=0; i<neqn; i++){
			for(int j=0;j<=nvar; j++){
				cin >> mat[i][j]; //also contains the constants
			}
		}
	}

	void setObjective(){
		cout << "Enter the objective function to be maximised: ";
		for(int i=0;i<nvar;i++)cin >> obj[i];
	}

	void findSolution(){
		for(int i=0;i < neqn;i++){
			for(int j=0;j<=nvar;j++){
				tableau[i][j] = mat[i][j];
			}
		}

		for(int i=0;i<=nvar;i++){
			tableau[neqn][i] = -obj[i];
		}

		bool flag=true;
		while(flag){
			float min=10000;
			int prod=0;
			int minpos = -1;

			for(int i=0;i<nvar;i++){
				if(tableau[neqn][i] < 0)prod=1;
			}
			if(!prod){
				//cout << "Prod is " << prod;
				flag=0;
				break;
			}
				
			for(int i=0;i<nvar;i++)
			{
				if(tableau[neqn][i] <= min)
				{
					min = tableau[neqn][i];
					minpos = i;
				}
			}
		
			int pivot = -1;
			float minp = 10000;
			for(int i=0;i< neqn;i++)
			{
				if(1.0*tableau[i][nvar]/tableau[i][minpos] < minp && 1.0*tableau[i][nvar]/tableau[i][minpos]>0)
				{
					minp = 1.0*tableau[i][nvar]/tableau[i][minpos];
					pivot = i;
				}
			}
		
			if(pivot==-1){
				flag=0;
				incos = 1;
				break;
			}
			cout << "Pivot " << tableau[pivot][minpos] << " at pos " << pivot;
		
			d[minpos] = 1;
			dmap[minpos] = pivot;
			float p = tableau[pivot][minpos];
		
			for(int i=0;i<=neqn;i++)
			{
				for(int j=0;j<=nvar;j++)
				{
					if(i==pivot || j==minpos)continue;
					tableau[i][j] = tableau[i][j] - 1.0*tableau[pivot][j]*tableau[i][minpos]/p;
				}
			}

			for(int i=0;i<=neqn; i++)
			{
				if(i==pivot)continue;
				tableau[i][minpos] = -tableau[i][minpos]/p;
			}
			for(int j=0;j<=nvar;j++)
			{
				if(j==minpos)continue;
				tableau[pivot][j] = tableau[pivot][j]/p;
			}
			tableau[pivot][minpos] = 1.0/tableau[pivot][minpos];

		
		
			/*cout << "Simplex table\n ";
			for(int i=0;i <= eqn;i++)
			{
				for(int j=0;j<=nvar;j++)
				{
					cout <<tableau[i][j] << " ";
				}
				cout << endl;
			}*/
		//flag = 0;
		}
	}
};
