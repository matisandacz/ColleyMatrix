// colleyMatrix1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void printMatrix(int** m, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << (m[i][j]) << " ";
		}
		cout << "\n";
	}
	return;
}

void printVector(double* b, int size) {
	for (int i = 0; i < size; i++) {
		cout << b[i] << " ";
	}
}

int main()
{	
	ifstream myfile("test.txt");
	if (myfile.is_open()) {
		
		//Cantidad de participantes - cantidad de partidos.
		int T, P;
		myfile >> T >> P;
		
		//Creamos la matriz dinámica C.
		int** C = new int*[T];
		for (int i = 0; i < T; i++) {
			C[i] = new int[T];
		}

		//Se inicializa la matriz
		for (int i = 0; i < T; i++) {
			for (int j = 0; j < T; j++) {
				if (i == j) {
					C[i][j] = 2;
				}
				else {
					C[i][j] = 0;
				}
			}
		}

		//Creamos el vector dinámico b
		double* b = new double[T];

		//Se inicializa el vector.
		for (int i = 0; i < T; i++) {
			b[i] = 1;
		}

		int optional, i, goles_i, j, goles_j;
		while (myfile >> optional >> i >> goles_i >> j >> goles_j)
		{
			//Procesamos los datos
			C[i-1][i-1]++;
			C[j-1][j-1]++;
			C[i-1][j-1]--;
			C[j-1][i-1]--;

			if (goles_i >= goles_j) {
				b[i] = b[i] + 0.5;
				b[j] = b[j] - 0.5;
			}
			else {
				b[i] = b[i] - 0.5;
				b[j] = b[j] + 0.5;
			}
			
		}

		printMatrix(C, T);
		printVector(b, T);
		
		//Se libera la memoria
		delete[] b;
		for (int i = 0; i < T; i++) {
			delete[] C[i];
		}
		delete[] C;
		//TODO: Triangular la matriz C usando eliminación Gaussiana y resolver el sistema.

	}
	else {
		exit(0);
	}
	return 0;
}




