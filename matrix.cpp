#include "matrix.h"
#include <fstream>
#include <iomanip>

Matrix::Matrix() : _filas(0), _columnas(0), _arreglo(NULL) {
}

Matrix::Matrix(int n, int m) : _filas(n), _columnas(m) {
	_arreglo = new double[_filas*_columnas];
	// se rellena con 0
	for (int i = 0; i < n*m; ++i){
		_arreglo[i] = 0.0;
	}
}

Matrix& Matrix::operator=(const Matrix& B){
	if(_arreglo != NULL)
		delete[] _arreglo;
	_arreglo = new double[B.filas()*B.columnas()];
	for(int i = 0; i < B.filas(); i++){
		for(int j = 0; j < B.columnas(); j++){
			_arreglo[B.columnas()*i + j] = B(i,j);
		}
	}
	_filas = B.filas();
	_columnas = B.columnas();
	return *this;
}

int Matrix::filas() const {
	return _filas;
}

int Matrix::columnas() const {
	return _columnas;
}

double& Matrix::operator()(int i, int j) {
	return _arreglo[i*_columnas + j];
}

double Matrix::operator()(int i, int j) const {
	return _arreglo[i*_columnas + j];
}

Fila Matrix::operator()(int i) {
	return Fila(_arreglo+i*_columnas, _columnas);
}

void Matrix::print() const {
	for (int i = 0; i < _filas; i++) {
		for (int j = 0; j < _columnas; j++) {
			cout << _arreglo[i*_columnas + j] << " ";
		}
		cout << "\n";
	}
	return;
}

Matrix Matrix::operator*(Matrix& B){
	//Esta operacion multiplica dos matrices.
	Matrix C = Matrix(_filas, B.columnas());
	for(int fila = 0; fila < _filas; fila++){
		for(int col=0; col < B.columnas(); col++){
			double producto = 0;
			for(int aux = 0; aux < _columnas; aux++){
				producto += (_arreglo[fila*_columnas+aux] * B(aux, col));
			}
			C(fila,col) = producto;
		}
	}
	return C;
}

Matrix::~Matrix() {
	delete[] _arreglo;
}

Fila::Fila(double* arreglo, int columnas) : _arreglo(NULL),  _columnas(columnas) {
	_arreglo = arreglo;
}

int Fila::columnas() const {
	return _columnas;
}

void Fila::operator=(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] = f(i);
	}
}

double& Fila::operator()(int i) {
	return _arreglo[i];
}

void Fila::sumar(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f(i);
	}
}

void Fila::operator+=(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		_arreglo[i] += f(i);
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
	for (int i = 0; i < _columnas; ++i){
		(*this)(i) += f(i)*alpha;
	}
}

void Fila::swapear(Fila f) {
	for (int i = 0; i < _columnas; ++i)
	{
		double temp = _arreglo[i];
		_arreglo[i] = f(i);
		f(i) = temp;
	}
}

void triangular(Matrix &A, Matrix &b,bool save_aii) {
	// se realiza triangulacion usando cada uno de las filas como pivote
	Matrix pivotes(1,A.filas());
	for (int pivote = 0; pivote < A.filas() - 1; ++pivote)
	{
		double aii = A(pivote,pivote);
		if(save_aii)
			pivotes(0,pivote) = aii;
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
				;//A(pivote).swapear(A(posible_pivote));
			}
			// si no, entonces esta columna ya esta triangulada porque son todos 0.
			else continue;
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
	if(save_aii){
		pivotes(0,A.filas()-1) = A(A.filas()-1,A.filas()-1);
		ofstream outputf("pivotes.csv");
		if (outputf.is_open()){
			for(int i = 0;i < A.filas(); i++)
				outputf << fixed << setprecision(15) << pivotes(0,i)<< "\n";
			cout << "Pivotes guardados con éxito." << endl;
		} else {
			cout << "No se pudo abrir el archivo de salida de pivotes." << endl;
			exit(0);
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
