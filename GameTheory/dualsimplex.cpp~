#include <iostream>
using namespace std;

int d[10]={0};
int dmap[10]={-1};
float mat[10][10], b[10], temp[10][10], constants[10];
float ans[10][10], z[10];
int R, C;
int main()
{
	int in_var, eqn, var;
	int flag = 1;int incos=0;
	string inequality;
	cout << "Enter no of columns in payoff matrix\n";
	cin >> in_var;
	var= in_var;
	cout << "Enter no. of rows in payoff matrix\n";
	cin >> eqn;
	cout << "\nEnter the matrix: \n";
	for(int i = 0 ; i < eqn ; i++)
	{
		for(int j = 0 ; j < in_var ; j++)
		{
			cin >> mat[i][j];
		}
	}
	
	//finding out value of v_ (max min wala)
	float rowmin[10]={1000};

	for(int i=0;i < in_var;i++)
	{
		for(int j=0;j < eqn;j++)
		{
			temp[j][i] = -1*mat[j][i];
			if(rowmin[j] > mat[j][i])rowmin[j]=mat[j][i];
		}
	}
	
	float maxmi = -19900;
	for(int i=0;i<in_var;i++){
		cout << "  Rowmin:  " << rowmin[i]; 
		if(maxmi < rowmin[i])maxmi = rowmin[i];
	}
	
	cout << "\n Value of maxmi is: " << maxmi;
		for(int i=0;i<in_var;i++)
	{
		temp[eqn][i] = 1.0/maxmi;
	}
	
	for(int i=0;i<eqn;i++){temp[i][in_var]=-maxmi;}

	int max_or_min = 0; //0 for minimisation
	cout << "Initial simplex table\n ";
	for(int i=0;i <= eqn;i++)
	{
		for(int j=0;j<=in_var;j++)
		{
			cout << " " << temp[i][j];
		}
		cout << endl;
	}
	cout << " Flag is " << flag;
	while(flag){
		
		float min = 10000; int prod=0;
		int minpos = -1;
		for(int i=0;i<in_var;i++)
		{
			if(temp[eqn][i] < 0)prod=1;
		}
		for(int i=0;i<eqn;i++)
		{
			if(temp[i][in_var] < 0)prod=1;
		}
		if(!prod){
			cout << "Prod is " << prod;
			flag=0;
			break;
		}
				
		for(int i=0;i<in_var;i++)
		{
			if(temp[eqn][i] <= min)
			{
				min = temp[eqn][i];
				minpos = i;
			}
		}
		
		cout << " Value of minpos is " << minpos << " and invar is " << in_var << endl;
		int pivot = -1;
		float minp = 10000;
		for(int i=0;i< eqn;i++)
		{
			if(1.0*temp[i][in_var]/temp[i][minpos] < minp && 1.0*temp[i][in_var]/temp[i][minpos]>0)
			{
				minp = 1.0*temp[i][in_var]/temp[i][minpos];
				pivot = i;
			}
		}
		
		if(pivot==-1){
			flag=0;
			incos = 1;
			break;
		}
		cout << "Pivot " << temp[pivot][minpos] << " at pos " << pivot;
		cout << "Most negative element " << min;
		
		d[minpos] = 1;
		dmap[minpos] = pivot;
		float p = temp[pivot][minpos];
		
		for(int i=0;i<=eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				if(i==pivot || j==minpos)continue;
				//cout << "\n\n Debuggind pqrs for i = " << i << " and j= " << j << "\n";
				//cout << " q " << temp[pivot][j] << " r " << temp[i][minpos];
				temp[i][j] = temp[i][j] - 1.0*temp[pivot][j]*temp[i][minpos]/p;
			}
		}
		for(int i=0;i<=eqn; i++)
		{
			if(i==pivot)continue;
			temp[i][minpos] = -temp[i][minpos]/p;
		}
		for(int j=0;j<=in_var;j++)
		{
			if(j==minpos)continue;
			temp[pivot][j] = temp[pivot][j]/p;
		}
		temp[pivot][minpos] = 1.0/temp[pivot][minpos];
		
		
		cout << "Simplex table\n ";
		for(int i=0;i <= eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				cout <<temp[i][j] << " ";
			}
			cout << endl;
		}
		//flag = 0;
	}

	if(incos)
	{
		cout << "The given system of equations inconsistent  ";
		return 0;
	}
	if(max_or_min){
		cout << "The maximum of z is : " << temp[eqn][in_var];
	}
	else{
		cout << "The minimum of z is : " << -temp[eqn][in_var];
	}
	for(int i=0;i<10;i++)
	{
		if(d[i]){
			cout << " at x" << i+1 << " = " << temp[dmap[i]][in_var];
		}
	}
	for(int j=0;j<in_var;j++)
	{
		if(temp[eqn][j]==0)
		{
			cout << " However infinite solutions exist for this case ";
			break;
		}
	}
	return 0;
}
