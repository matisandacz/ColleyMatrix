#include "matrix.h"

Matrix::Matrix(int n, int m) : _filas(n), _columnas(m) {
	_arreglo = new double[_filas*_columnas];

	// se rellena con 0
	for (int i = 0; i < n*m; ++i)
	{
		_arreglo[i] = 0.0;
	}
}

int Matrix::filas() {
	return _filas;
}

int Matrix::columnas() {
	return _columnas;
}

double& Matrix::operator()(int i, int j) {
	return _arreglo[i*_columnas + j];
}

double Matrix::operator()(int i, int j) const {
	return _arreglo[i*_columnas + j];
}

Fila Matrix::operator()(int i) {
	return Fila(&_arreglo[i*_columnas], _columnas);
}

void Matrix::print() {
	for (int i = 0; i < _filas; i++) {
		for (int j = 0; j < _columnas; j++) {
			cout << _arreglo[i*_columnas + j] << " ";
		}
		cout << "\n";
	}
	return;
}


Matrix::~Matrix() {
	delete [] _arreglo;
}


Fila::Fila(double* arreglo, int columnas) : _arreglo(NULL),  _columnas(columnas) {
	_arreglo = arreglo;
}

int Fila::columnas() {
	return _columnas;
}

void Fila::operator=(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] = f._arreglo[i];
	} 
}

void Fila::sumar(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f._arreglo[i];
	}
}

void Fila::operator+=(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f._arreglo[i];
	}
}

void Fila::sumar(double alpha) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += alpha;
	}
}

void Fila::operator+=(double alpha) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += alpha;
	}
}

void Fila::multiplicar(double alpha) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] *= alpha;
	}
}

void Fila::operator*=(double alpha) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] *= alpha;
	}
}

void Fila::sumar_multiplo(Fila f, double alpha) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f._arreglo[i]*alpha ;
	}
}

void Fila::swapear(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		double temp = _arreglo[i];
		_arreglo[i] = f._arreglo[i];
		f._arreglo[i] = temp;
	}
}


void triangular(Matrix &A, Matrix &b) {
	// se realiza triangulacion usando cada uno de las filas como pivote
	for (int pivote = 0; pivote < A.filas() - 1; ++pivote)
	{
		double aii = A(pivote,pivote);

		// si este pivote no sirve para triangular
		if (aii == 0)
		{
			// se busca otro pivote que tenga la columna i no nula
			int posible_pivote = pivote + 1;
			while(posible_pivote < A.filas() and A(posible_pivote,pivote) == 0) {
				++posible_pivote;
			}

			// si se encontro alguno, se swapean
			if (posible_pivote < A.filas())
			{
				A(pivote).swapear(A(posible_pivote));
			}

			// si no, entonces esta columna ya esta triangulada porque son todos 0.
			else {continue;}
			
		}

		// se aplica el pivote a cada una de las filas
		for (int j = pivote+1; j < A.filas(); ++j)
		{
			double aji = A(j,pivote);
			double alpha = -aji/aii;
			A(j,pivote) = 0;

			b(j).sumar_multiplo(b(pivote), alpha); 

			// se aplica el pivote a cada componente de la fila.
			for (int k = pivote+1; k < A.columnas(); ++k)
			{
				A(j,k) += A(pivote,k) * alpha;
			}
		}
	}
}


// Devuelve la solucion del sistema.
Matrix resolver_triangulado(Matrix &A, Matrix &b) {
	Matrix X = Matrix(A.filas(), b.columnas());

	for (int i = A.filas()-1; i >= 0; --i)
	{
		X(i) = b(i);

		for (int j = A.columnas() - 1; j > i; --j)
		{
			double aij = A(i,j);
			X(i).sumar_multiplo(X(j), -aij);
		}

		double aii = A(i,i);
		X(i).multiplicar(1.0/aii);
	}

	return X;
}
