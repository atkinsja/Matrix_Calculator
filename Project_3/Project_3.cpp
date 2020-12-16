#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void read(double**, int, bool&, ifstream&);
void add(double**, double**, double**, int);
void subtract(double**, double**, double**, int);
void dot_product(double**, double**, double**, int);
double determinant(double**, int);
void cofactor(double**, double**, int, int, int);
void print(double**, int, ofstream&);
void free(double**, int);

int main()
{
	int size;
	int selection;
	string inFile_name = "input.txt";
	string outFile_name = "out.txt";

	ifstream inFile;
	ofstream outFile;

	size = 3;

	double **matrixA = new double *[size];
	double **matrixB = new double *[size];
	double **matrix_result = new double *[size];
	for (int i = 0; i < size; i++)
	{
		matrixA[i] = new double[size];
		matrixB[i] = new double[size];
		matrix_result[i] = new double[size];
	}
	
	outFile.open(outFile_name);
	if (!outFile)
	{
		cout << "Error opening output file " << outFile_name;
		return -1;
	}
	bool populated = false;

	do
	{
		cout << size << " X " << size << " matrix" << endl;
		cout << "1. Read" << endl;
		cout << "2. Print" << endl;
		cout << "3. Add" << endl;
		cout << "4. Subtract" << endl;
		cout << "5. Dot Product" << endl;
		cout << "6. Determinant" << endl;
		cout << "7. Change diminsions (currently " << size << ")" << endl;
		cout << "0. Exit" << endl;
		cout << "What would you like to do for the matrices?: ";
		cin >> selection;
		switch (selection)
		{
		case 1:
			inFile.open(inFile_name);
			if (!inFile)
			{
				cout << "Error opening input file " << inFile_name << "\n\n";
				populated = false;
			}
			system("cls");
			read(matrixA, size, populated, inFile);
			read(matrixB, size, populated, inFile);
			if (populated)
				cout << "Matrices populated.\n\n";
			else
				cout << "Not enough elements in " << inFile_name << " to populated Matrix A and Matrix B.\n\n";
			inFile.close();
			break;
		case 2:
			system("cls");
			if (!populated)
			{
				cout << "Please read in matrix data first.\n\n";
				break;
			}
			cout << "Matrix A:" << endl;
			outFile << "Matrix A:" << endl;
			print(matrixA, size, outFile);

			cout << "Matrix B:" << endl;
			outFile << "Matrix B:" << endl;
			print(matrixB, size, outFile);

			cout << "Matrices written to " << outFile_name << "\n\n";
			break;
		case 3:
			system("cls");
			if (!populated)
			{
				cout << "Please read in matrix data first.\n\n";
				break;
			}
			cout << "Matrix A + Matrix B:" << endl;
			outFile << "Matrix A + Matrix B:" << endl;
			add(matrixA, matrixB, matrix_result, size);
			print(matrix_result, size, outFile);

			cout << "Matrix written to " << outFile_name << "\n\n";
			break;
		case 4:
			system("cls");
			if (!populated)
			{
				cout << "Please read in matrix data first.\n\n";
				break;
			}
			cout << "Matrix A - Matrix B:" << endl;
			outFile << "Matrix A - Matrix B:" << endl;
			subtract(matrixA, matrixB, matrix_result, size);
			print(matrix_result, size, outFile);

			cout << "Matrix B - Matrix A:" << endl;
			outFile << "Matrix B - Matrix A:" << endl;
			subtract(matrixB, matrixA, matrix_result, size);
			print(matrix_result, size, outFile);

			cout << "Matrices written to " << outFile_name << "\n\n";
			break;
		case 5:
			system("cls");
			if (!populated)
			{
				cout << "Please read in matrix data first.\n\n";
				break;
			}
			cout << "Matrix A * Matrix B: " << endl;
			outFile << "Matrix A * Matrix B: " << endl;
			dot_product(matrixA, matrixB, matrix_result, size);
			print(matrix_result, size, outFile);

			cout << "Matrix B * Matrix A: " << endl;
			outFile << "Matrix B * Matrix A: " << endl;
			dot_product(matrixB, matrixA, matrix_result, size);
			print(matrix_result, size, outFile);

			cout << "Matrices written to " << outFile_name << "\n\n";
			break;
		case 6:
			system("cls");
			if (!populated)
			{
				cout << "Please read in matrix data first.\n\n";
				break;
			}
			cout << "The determinate of Matrix A is: " << determinant(matrixA, size) << endl;
			cout << "The determinate of Matrix B is: " << determinant(matrixB, size) << endl;
			cout << "\n\n";

			outFile << "The determinate of Matrix A is: " << determinant(matrixA, size) << endl;
			outFile << "The determinate of Matrix B is: " << determinant(matrixB, size) << endl;
			outFile << "\n\n";

			break;
		case 7:
			free(matrixA, size);
			free(matrixB, size);
			free(matrix_result, size);

			system("cls");
			cout << "The current dimensions of the matrices are: " << size << " X " << size << endl;
			cout << "To change, enter the dimensions of the N X N matrix in " << inFile_name << ": ";
			cin >> size;

			matrixA = new double *[size];
			matrixB = new double *[size];
			matrix_result = new double *[size];
			for (int i = 0; i < size; i++)
			{
				matrixA[i] = new double[size];
				matrixB[i] = new double[size];
				matrix_result[i] = new double[size];
			}
			populated = false;
			cout << "\n";
			break;
		case 0:
			free(matrixA, size);
			free(matrixB, size);
			free(matrix_result, size);
			outFile.close();
			return 0;
		default:
			system("cls");
			cout << "Invalid selection\n\n";
		}
	} while (selection != 0);
}

void print(double **matrix, int size, ofstream &outFile)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(5) << matrix[i][j] << " ";
			outFile << setw(5) << matrix[i][j] << " ";
		}
		cout << "\n";
		outFile << "\n";
	}
	cout << "\n\n";
	outFile << "\n\n";
}

void read(double **matrix, int size, bool& populated, ifstream &inFile)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			inFile >> matrix[i][j];
			if (!inFile)
			{
				populated = false;
				return;
			}
		}
	}
		populated = true;
}

void add(double **matrixA, double **matrixB, double **matrix_sum, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix_sum[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}
}

void subtract(double **matrixA, double **matrixB, double **matrix_diff, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix_diff[i][j] = matrixA[i][j] - matrixB[i][j];
		}
	}
}

void dot_product(double **matrixA, double **matrixB, double **matrix_product, int size)
{
	double total;
	double *temp = new double[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			total = 0;
			for (int k = 0; k < size; k++)
			{
				temp[k] = matrixA[i][k] * matrixB[k][j];
			}
			for (int x = 0; x < size; x++)
			{
				total = temp[x] + total;
			}
			matrix_product[i][j] = total;
		}
	}
	delete[] temp;
}

double determinant(double **matrix, int size)
{
	double det = 0;
	if (size == 1)
		return matrix[0][0];

	double **temp = new double*[size];
	for (int i = 0; i < size; i++)
		temp[i] = new double[size];

	int sign = 1;

	for (int i = 0; i < size; i++)
	{
		cofactor(matrix, temp, 0, i, size);
		det += sign * matrix[0][i] * determinant(temp, size - 1);

		sign = -sign;
	}

	free(temp, size);
	return det;
}

void cofactor(double **matrix, double **temp, int row_selection, int col_selection, int size)
{
	int i = 0;
	int j = 0;

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (row != row_selection && col != col_selection)
			{
				temp[i][j++] = matrix[row][col];
				if (j == size - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

void free(double **matrix, int size)
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];

	delete[] matrix;
}