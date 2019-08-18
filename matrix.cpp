#include "matrix.h"

Matrix::Matrix(int n, int m) :  _arreglo(NULL), _filas(n), _columnas(m) {
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

void Fila::sumar(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f._arreglo[i];
	}
}

void Fila::multiplicar(double alpha) {
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


