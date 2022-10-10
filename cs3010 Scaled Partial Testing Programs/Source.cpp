#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include<vector>
#include <iomanip>
using namespace std;

//Function Prototypes
void display1_DArray(vector<float>& matrix, int numofEquations, string matrixName);
void display1_DArray(vector<int>& matrix, int numofEquations, string matrixName);
void displayMatrix(vector<vector<float>>& matrix, int numOfEquations);
void displayMatrix2(vector<vector<float>>& matrix, int numOfEquations);
void combineMatricies(vector<vector<float>>& a, vector<float>& b, vector<vector<float>>& userEquations, int numOfEquations);


int main()
{
	cout << fixed;
	cout << setprecision(2);


	//Variables
	int numOfEquations = 0;
	int inputMethod = -1;
	int x;
	int i, j, k;
	int temp;
	int rindex = 0;

	float r, rmax, smax, xmult;
	float sum = 0;
	string userFile = "";
	vector<vector<float>> userEquations, a;
	vector<float> multipliers;
	vector<float> row;
	vector<float> l;
	vector<float> s;
	vector<float> b;
	vector<float> xi;


	cout << "How many equations will you be entering?: " << endl;
	cin >> numOfEquations;
	while (numOfEquations != 1 && numOfEquations != 2 && numOfEquations != 3 && numOfEquations != 4 && numOfEquations != 5 && numOfEquations != 6 && numOfEquations != 7 && numOfEquations != 8 && numOfEquations != 9 && numOfEquations != 10)
	{
		cin.clear();                        // clear error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty buffer 
		cout << "Error: Please enter an integer between 2 and 10 (inclusive)." << endl;
		cin >> numOfEquations;
	}

	//create a 2-d vector inizalized with all 0's
	userEquations.assign(numOfEquations, vector<float>(numOfEquations + 1, 0));
	a.assign(numOfEquations, vector<float>(numOfEquations, 0));
	b.assign(numOfEquations, 0);
	s.assign(numOfEquations, 0);
	l.assign(numOfEquations, 0);
	xi.assign(numOfEquations, 0);

	//Get user inputs
	cout << "How do you want to input your equations?: " << endl;
	cout << "1. Manually enter each row including the b values." << endl;
	cout << "2. Enter a file name which has the augmented coeffiecent matrix includining" << endl;
	cout << "   the b values in a simple text file format" << endl;
	cin >> inputMethod;

	while (inputMethod != 1 && inputMethod != 2)
	{
		cin.clear();                        // clear error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty buffer 
		cout << "Error: Please choose between options 1 and 2." << endl;
		cin >> inputMethod;
	}
	if (inputMethod == 1)
	{
		std::cout << "Enter coefficent values for your augmented coeffiecent matrix: \n";
		for (int i = 1; i <= numOfEquations; i++)
		{
			std::cout << i << ": ";

			int curCol = 0;
			while (curCol < numOfEquations + 1)
			{
				cin >> x;
				row.push_back(x);
				curCol += 1;
			}
			//cout << "reached end of while";

			userEquations[i - 1] = row;
			row.clear();
		}
	}
	else if (inputMethod == 2)
	{
		cout << "Please enter the name of your properly formated txt file: " << endl;
		cin >> userFile;
		//take runtimes from Time.txt and average them
		fstream fileData;
		string line;
		string num;
		int curRow = 0;
		fileData.open(userFile, ios::in);
		if (fileData.is_open())
		{
			while (getline(fileData, line))
			{
				//cout << line << endl;
				stringstream s(line);

				while (getline(s, num, ' '))
				{
					row.push_back(stoi(num));
				}

				userEquations[curRow] = row;
				curRow += 1;
				row.clear();
			}
		}

		fileData.close();
	}
	else
	{
		cout << "Error: Please choose between options 1 and 2." << endl;
	}


	for (int row = 0; row < numOfEquations; row++)
	{
		for (int col = 0; col <= numOfEquations; col++)
		{
			if (col == numOfEquations)
			{
				b[row] = userEquations[row][col];
			}
			else
			{
				a[row][col] = userEquations[row][col];
			}
		}
	}
	cout << "\n\n";
	cout << "!!!Note: All indicies will start at 0 NOT 1!!!" << endl;
	cout << "\n\n";
	displayMatrix(userEquations, numOfEquations);
	//displayMatrix2(a, numOfEquations);
	//display1_DArray(b, numOfEquations, "b");

	for (i = 0; i < numOfEquations; i++)
	{
		l[i] = i;
		smax = 0;
		for (j = 0; j < numOfEquations;j++)
		{
			if (smax < abs(a[i][j]))
			{
				smax = abs(a[i][j]);
			}
			else
			{
				smax = smax;
			}
		}
		s[i] = smax;
	}

	display1_DArray(s, numOfEquations, "s");

	display1_DArray(l, numOfEquations, "l");

	vector<float> ratios;
	ratios.assign(numOfEquations, 0);
	cout << "\n\n";
	for (i = 0; i < numOfEquations - 1;i++)
	{
		rmax = 0;
		for (j = i; j < numOfEquations; j++)
		{
			r = fabs(a[l[j]][i] / s[l[j]]);
			ratios[j] = r;
			if (r > rmax)
			{
				rmax = r;
				rindex = j;
			}
		}
		display1_DArray(ratios, numOfEquations, "ratios");
		display1_DArray(l, numOfEquations, "l");
		cout << "rmax = " << rmax << endl;
		//cout << "rindex = " << rindex << endl;
		temp = l[i];
		l[i] = l[rindex];
		l[rindex] = temp;

		//cout << "pivot index in l = " << l[rindex] << endl;
		cout << "pivot row = " << l[i] << endl;
		
		for (j = i + 1;j < numOfEquations;j++)
		{
			//cout << "i = " << i << "k = " << k << endl;
			//cout << "s[l[j]][i]=" << s[l[i]] << endl;
			//cout << a[l[j]][i] << "/" << a[l[i]][i] << endl;
			xmult = a[l[j]][i] / a[l[i]][i];
			
			//cout << "multiplier is " << xmult << endl;
			for (k = i;k < numOfEquations;k++)
			{
				//cout << "i:" << i << ", j:" << j << ", k:" << k << endl;
				//cout << "l[i]:" << l[i] << ", l[j]:" << l[j] << ", l[k]:" << l[k] << endl;
				//cout << a[l[j]][k] << "-" << (xmult * a[l[i]][k]) << endl;
				a[l[j]][k] = a[l[j]][k] - (xmult * a[l[i]][k]);
				//cout << "a[l[j]][k] is " << a[l[j]][k] << endl;
			}
			b[l[j]] = b[l[j]] - (xmult * b[l[i]]);
			//cout << "b[l[j]] is " << b[l[j]] << endl;
			//displayMatrix(userEquations, numOfEquations);
		}
		combineMatricies(a, b, userEquations, numOfEquations);
		displayMatrix(userEquations, numOfEquations);
		cout << "\n\n";
		//cout << "Done::::" << endl;
	}
	//Deallocate s
	//s.clear();

	xi[numOfEquations - 1] = b[l[numOfEquations - 1]] / a[l[numOfEquations - 1]][numOfEquations - 1];
	//cout << "init xi: " << xi[numOfEquations - 1] << endl;
	for (j = numOfEquations - 2; j > -1;j--)
	{
		sum = 0;
		for (k = j + 1;k < numOfEquations;k++)
		{
			sum = sum + a[l[j]][k] * xi[k];
			//cout << "sum: " << sum << endl;
		}
		xi[j] = (b[l[j]] - sum) / a[l[j]][j];
	}
	/*
	combineMatricies(a, b, userEquations, numOfEquations);
	displayMatrix(userEquations, numOfEquations);*/
	//displayMatrix2(a, numOfEquations);
	display1_DArray(xi, numOfEquations, "xi");
	for (int row = 0; row < numOfEquations; row++)
	{
		cout << "x" << row << " = " << xi[row] << endl;
	}
}

void combineMatricies(vector<vector<float>>& a, vector<float>& b, vector<vector<float>>& userEquations, int numOfEquations)
{
	for (int row = 0; row < numOfEquations; row++)
	{
		for (int col = 0; col <= numOfEquations; col++)
		{
			if (col == numOfEquations)
			{
				userEquations[row][col] = b[row];
			}
			else
			{
				userEquations[row][col] = a[row][col];
			}
		}
	}
}

void display1_DArray(vector<int>& matrix, int numofEquations, string matrixName)
{
	for (int i = 0; i < numofEquations; i++)
	{
		if (i == 0)
		{
			cout << matrixName << " = [" << matrix[i];
		}
		else
		{
			cout << ", " << matrix[i];
		}
	}
	cout << "]" << endl;
}

void display1_DArray(vector<float>& matrix, int numofEquations, string matrixName)
{
	for (int i = 0; i < numofEquations; i++)
	{
		if (i == 0)
		{
			cout << matrixName << " = [" << matrix[i];
		}
		else
		{
			cout << ", " << matrix[i];
		}
	}
	cout << "]" << endl;
}


void displayMatrix(vector<vector<float>>& matrix, int numOfEquations)
{
	for (int i = 0; i < numOfEquations; i++)
	{
		for (int j = 0; j < numOfEquations + 1; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void displayMatrix2(vector<vector<float>>& matrix, int numOfEquations)
{
	for (int i = 0; i < numOfEquations; i++)
	{
		for (int j = 0; j < numOfEquations; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}