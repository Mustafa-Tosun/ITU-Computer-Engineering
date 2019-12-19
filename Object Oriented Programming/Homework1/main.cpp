// Mustafa TOSUN 150170055

#include <iostream>
#include <fstream>
#include <vector>
#include "Vector.h"
#include "Polynomial.h"
using namespace std;

int main() {
	int i, j; // For loop counters
	int op1, op2; // input operands
	char op; // input operator

	// Reading Polynomial.txt
	fstream polfile;
	polfile.open("Polynomial.txt");

	if (!polfile) {
		cerr << "ERROR: Unable to open Polynomial.txt";
		return 1;
	}

	int **poldata; // Data of Polynomials	
	int pol_num; // Number of Polynomials
	polfile >> pol_num;
	poldata = new int*[pol_num];

	vector<Polynomial> pols; // std::vector for Polynomial objects

	for (i = 0; i < pol_num; i++) {
		int degree;
		polfile >> degree;
		poldata[i] = new int[degree + 1];
		for (j = degree; j >= 0; j--) polfile >> poldata[i][j];
		pols.push_back(Polynomial(degree, poldata[i]));
	}

	// Reading Vector.txt
	fstream vecfile;
	vecfile.open("Vector.txt");

	if (!vecfile) {
		cerr << "ERROR: Unable to open Vector.txt";
		return 1;
	}

	int **vecdata; // Data of Vectors
	int vec_num; // Number of Vectors
	vecfile >> vec_num;
	vecdata = new int*[vec_num];

	vector<Vector> vecs; // std::vector for Vector objects

	for (i = 0; i < vec_num; i++) {
		int dimension;
		vecfile >> dimension;
		vecdata[i] = new int[dimension];
		for (j = dimension - 1; j >= 0; j--) vecfile >> vecdata[i][j];
		vecs.push_back(Vector(dimension, vecdata[i]));
	}

	// Interface
	cout << "Polynomial and Vector List Program!" << endl;
	cout << "Polynomials and Vectors are read from text files!" << endl << endl;
	cout << "Possible Actions:" << endl;
	cout << "1. Print Polynomial and Vector lists" << endl;
	cout << "2. Do a polynomial operation" << endl;
	cout << "3. Do a vector operation" << endl;
	cout << "4. Help: Print possible actions" << endl;
	cout << "0. Exit the program" << endl;

	int input = 1;
	while (input != 0) // when input==0 , exit the program
	{
		cout << endl << "Enter an option:";
		cin >> input;

		//Print Polynomial and Vector lists
		if (input == 1) {
			cout << "Vectors:" << endl;
			for (int i = 0; i < vec_num; i++) {
				cout << i + 1 << ". " << vecs[i] << endl;
			}

			cout << endl << "Polynomials:" << endl;
			for (int i = 0; i < pol_num; i++) {
				cout << i + 1 << ". " << pols[i] << endl;
			}
		}

		// Do a polynomial operation
		else if (input == 2) {
			cout << "Which polynomial operation would you like to do?((+:addition, *:multiplication):" << endl;
			cin >> op1 >> op >> op2;
			if (op == '+') {
				cout << "(" << pols[op1 - 1] << ")" << " + " << "(" << pols[op2 - 1] << ")" << " = " << Polynomial(pols[op1 - 1] + pols[op2 - 1]) << endl;
			}
			else if (op == '*') {
				cout << "(" << pols[op1 - 1] << ")" << " * " << "(" << pols[op2 - 1] << ")" << " = " << Polynomial(pols[op1 - 1] * pols[op2 - 1]) << endl;
			}
			else {
				cerr << "Undefined operation!" << endl;
			}
		}

		// Do a vector operation
		else if (input == 3) {
			cout << "Which vector operation would you like to do?((+:addition, *:scalar multiplication, .:dot product):" << endl;
			cin >> op1 >> op >> op2;
			if (op == '+') {
				if(vecs[op1-1].getdimension() != vecs[op2-1].getdimension()){
					cerr << "Size of vectors are not equal. This operation can not be performed!" << endl;
				}
				else{
					cout << vecs[op1 - 1] << " + " << vecs[op2 - 1] << " = " << Vector(vecs[op1 - 1] + vecs[op2 - 1]) << endl;
				}
			}
			else if (op == '*') {
				cout << vecs[op1 - 1] << " * " << op2 << " = " << Vector(vecs[op1 - 1] * op2) << endl;
			}
			else if (op == '.') {
				if(vecs[op1-1].getdimension() != vecs[op2-1].getdimension()){
					cerr << "Size of vectors are not equal. This operation can not be performed!" << endl;
				}
				else{	
					cout << vecs[op1 - 1] << " . " << vecs[op2 - 1] << " = " << (vecs[op1 - 1] * vecs[op2 - 1]) << endl;
			}	}
			else {
				cerr << "Undefined operation!" << endl;
			}
		}

		// Help:Print possible actions
		else if (input == 4) {
			cout << "Possible Actions:" << endl;
			cout << "1. Print Polynomial and Vector lists" << endl;
			cout << "2. Do a polynomial operation" << endl;
			cout << "3. Do a vector operation" << endl;
			cout << "4. Help: Print possible actions" << endl;
			cout << "0. Exit the program" << endl;
		}

		// in case of undefined input
		else if (input !=0 && input !=1 && input !=2 && input !=3 && input !=4 ){
			cout << "Undefined action!" << endl;
		}
	}

	// Deallocating memory of vecdata
	for (i = 0; i < vec_num; i++) {
			delete[] vecdata[i];
	}
	delete[] vecdata;

	// Deallocating memory of poldata
	for (i = 0; i < pol_num; i++) {
			delete[] poldata[i];
	}
	delete[] poldata;
	
	// Closing files
	vecfile.close();
	polfile.close();
	
	return 0;
}