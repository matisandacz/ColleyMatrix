#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;

// utilidad para hacer operaciones con filas bonito
class Fila {
	public:
		int columnas();

		// asignacion. Supone mismo numero de columnas
		void operator=(Fila f);

		// suma componente a componente. Supone mismo numero de columnas
		void sumar(Fila f);
		void operator+=(Fila f);

		// sumar alpha a todos los componentes
		void sumar(double alpha);
		void operator+=(double alpha);

		// multiplica todos los componentes por alpha
		void multiplicar(double alpha);
		void operator*=(double alpha);

		// suma f*alpha a la fila.  Supone mismo numero de columnas 
		void sumar_multiplo(Fila f, double alpha);

		// intercambia el contenido de esta fila con la fila f. Supone mismo numero de columnas
		void swapear(Fila f);


	private:
		double* _arreglo; // donde comienza la fila
		int _columnas; // numero de columnas
		Fila(double* arreglo, int columnas); // constructor

		// Solo Matrix puede construir filas 
		friend class Matrix;
};
	

class Matrix {
	public:
		Matrix(int n, int m);

		int filas();
		int columnas();
		~Matrix();

		// devolver elemento. Comienza en 0,0
		double operator()(int i, int j) const;
		double& operator()(int i, int j);

		// devolver la fila i. Lo devuelto es "por referencia-ish"
		Fila operator()(int i);

		// multiplicaion matricial
		Matrix operator*(Matrix &B);

		// imprime matriz 
		void print();

	private:
		int _filas; // numero de filas
		int _columnas; // numero de columnas
		double* _arreglo; // arreglo de doubles

};
#endif