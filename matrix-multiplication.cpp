//Program by Christina Ochsner
//PS#: 1166214

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void error(ofstream &f);

int main(int argc, char *argv[])
{	
	//Declare and/or initialize variables to be used in program.
	string str;
	string str2;
	int rowA=0;
	int colA=0;
	int rowB=0;
	int colB=0;
	int numColsA;
	int numColsB;
	double matrixA[20][20];
	double matrixB[20][20];
	double matrixC[20][20];
	char a[10];
	char b[10];
	char c[10];
	char letter;
	int i=0;
	int y=1;
	int first=0;
	int o;
	char ch;
	
	//Parse command line to retrieve and store file names.
	while(argv[y][i]!='\0')
	{
		switch(argv[y][i])
		{
			case '=':
			i++;
			o=0;
			while(argv[y][i]!='\0'&&argv[y][i]!=';'&&argv[y][i]!=' ')
			{
				switch(letter)
				{
					case 'a':
					a[o]=argv[y][i];
					if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
					{
						a[o+1]='\0';
					}
					break;
					
					case 'b':
					b[o]=argv[y][i];
					if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
					{
						b[o+1]='\0';
					}
					break;
					
					case 'c':
					c[o]=argv[y][i];
					if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
					{
						c[o+1]='\0';
					}
					break;
				}
				o++;
				i++;
			}
			if(argv[y][i]=='\0'&&argc>2&&y<3)
			{
					i=0;
					y++;
			}
			break;
			
			case 'A':
			letter='a';
			i++;
			break;
			
			case 'B':
			letter='b';
			i++;
			break;
			
			case 'C':
			letter='c';
			i++;
			break;
			
			default:
			i++;
			break;
		}

	}
	
	//Declare and open input/output files
	ifstream file (a);
	ifstream file2 (b);	
	ofstream file3;
	file3.open (c);
	FILE *f=fopen(a, "r");
	FILE *f2=fopen(b, "r");
	
	//Check to see if empty file was given for matrix A or B.
	while(fscanf(f,"%c",&ch)==EOF||fscanf(f2,"%c",&ch)==EOF||ch==' ')
	{
		if(fscanf(f,"%c",&ch)==EOF||fscanf(f2,"%c",&ch)==EOF)
		{
			cout<<"...Error! Empty matrix file will not be accepted."<<endl;
			error(file3);
			return 0;
		}
	}
	
	if (file.is_open()&&file2.is_open())
 	{
		//Input matrixA and count rows/columns. Print error if # of columns changes from row to row.
		cout<<"...Inputting matrices"<<endl;
		while(getline(file, str))
		{
			istringstream ss(str);
			istringstream ss2(str);
			char check[20][20];
			
			if(str.empty())
			{
				continue;
			}	
			
			//Check that each character in the matrix entries are valid.
			int k=0;
			int l=0;
			int dec=0;

			while(ss2>>check[k])
			{
				dec=0;
				l=0;
				while(check[k][l]!='\0')
				{
					int checker=check[k][l]-'0';
					//Print error for an invalid matrix character.
					if(check[k][l]!='.'&&check[k][l]!='-'&&(checker<0||checker>9)&&check[k][l]!='+')
					{
						cout<<"...Error! Invalid character entered into matrix."<<endl;
						error(file3);
						return 0;
					}
					//Print error if too many decimals are in an entry.
					else if(check[k][l]=='.')
					{
						dec++;
						if(dec>1||check[k][l+1]=='\0')
						{
							cout<<"...Error! Invalid decimal entry."<<endl;
							error(file3);
							return 0;
						}
					}
					//Print error if negative symbol(s) are misplaced in an entry.
					else if(check[k][l]=='-'&&(l>0||check[k][l+1]=='\0'))
					{
						cout<<"...Error! Invalid negative sign entry."<<endl;
						error(file3);
						return 0;
					}
					else if(check[k][l]=='+'&&(l>0||check[k][l+1]=='\0'))
					{
						cout<<"...Error! Invalid plus sign entry."<<endl;
						error(file3);
						return 0;
					}
					l++;
				}
				k++;
			}
			while(ss>>matrixA[rowA][colA])
			{
				colA++;
			}
			//Update # of rows if the line was not empty or only filled with spaces.
			if(colA!=0)
			{
				rowA++;
			}
			//If line was filled with only spaces, skip the rest of the loop iteration.
			else			
			{
				continue;
			}
			//Check if the number of columns are the same for every row. If not, print error. 
			if(numColsA!=colA)
			{
				if(first==0)
				{
					numColsA=colA;
					first++;
				}
				else
				{
					cout<<"...Error! # of columns is not the same in each row"<<endl;
					error(file3);
					return 0;
				}
			}
			//Set column counter back to 0.
			colA=0;
		}
		first=0;
		//Input matrixB and count rows/columns. Print error if # of columns changes from row to row.
		while(getline(file2, str2))
		{
			if(str2.empty())
			{
				continue;
			}
			istringstream ss(str2);
			istringstream ss2(str2);
			char check2[20][20];
			
			
			//Check that each character in the matrix entries are valid.
			int k=0;
			int l=0;
			int dec=0;

			while(ss2>>check2[k])
			{
				dec=0;
				l=0;
				while(check2[k][l]!='\0')
				{
					int checker=check2[k][l]-'0';
					//Print error for an invalid matrix character.
					if(check2[k][l]!='.'&&check2[k][l]!='-'&&(checker<0||checker>9)&&check2[k][l]!='+')
					{
						cout<<"...Error! Invalid character entered into matrix."<<endl;
						error(file3);
						return 0;
					}
					//Print error if too many decimals are in an entry.
					else if(check2[k][l]=='.')
					{
						dec++;
						if(dec>1||check2[k][l+1]=='\0')
						{
							cout<<"...Error! Invalid decimal entry."<<endl;
							error(file3);
							return 0;
						}
					}
					//Print error if negative symbol(s) are misplaced in an entry.
					else if(check2[k][l]=='-'&&(l>0||check2[k][l+1]=='\0'))
					{
						cout<<"...Error! Invalid negative sign entry."<<endl;
						error(file3);
						return 0;
					}
					else if(check2[k][l]=='+'&&(l>0||check2[k][l+1]=='\0'))
					{
						cout<<"...Error! Invalid plus sign entry."<<endl;
						error(file3);
						return 0;
					}
					l++;
				}
				k++;
			}
			while(ss>>matrixB[rowB][colB])
			{
				colB++;
			}
			//Update # of rows if the line was not empty or only filled with spaces.
			if(colB!=0)
			{
				rowB++;
			}
			//If line was filled with only spaces, skip the rest of the loop iteration.
			else			
			{
				continue;
			}
			//Check if the number of columns are the same for every row. If not, print error. 
			if(numColsB!=colB)
			{
				if(first==0)
				{
					numColsB=colB;
					first++;
				}
				else
				{
					cout<<"...Error! # of columns is not the same in each row"<<endl;
					error(file3);
					return 0;
				}
			}
			//Set column counter back to 0.
			colB=0;
		}
		
		//Calculate matrixA * matrixB if the # of columns in matrixA match the # of rows in matrixB. Otherwise, print error.
		if(numColsA==rowB)
		{
			
			cout<<"...Calculating matrix A * matrix B"<<endl;
			for(int i = 0; i < rowA; ++i)
			{
				for(int j = 0; j < numColsB; ++j)
				{
					for(int k = 0; k < numColsA; ++k)
					{
						matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
					}
				}
			}
			
			//Print result matrixC to proper output file.
			cout<<"...Printing output matrix to "<<c<<endl;
			for(int i = 0; i < rowA; ++i)
			{
				for(int j = 0; j < numColsB; ++j)
				{
					file3<<fixed<<setprecision(2)<<matrixC[i][j]<<" ";
				}
				file3<<endl;
			}
			
		}
		else
		{
			cout<<"...Error! Matrices have improper dimensions for multiplication."<<endl;
			error(file3);
			return 0;
		}
		
	}
	//Send user log message that program is exiting.
	cout<<"...Exiting\n"<<endl;
	file3.close();
	return 0;
}
//Prints error message in output file, closes output file, and sends user exiting log message.
void error(ofstream& file3)
{
	file3<<"error";
	file3.close();
	cout<<"...Exiting\n"<<endl;
}


