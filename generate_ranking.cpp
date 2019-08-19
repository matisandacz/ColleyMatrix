#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void colley(int T, vector<vector<int> > partidos, double* ranking);

void wp(int T, vector<vector<int> > partidos, double* ranking);

void nuestro_metodo(int T, vector<vector<int> > partidos, double* ranking);

void EG(Matrix& c, double* b, double* ranking);

int main(int argc, char** argv) {
	if(argc != 4){
	  cout << "Debe ingresar exactamente 3 parametros." << endl;
	  exit(0);
	}
	//argv[1] es numero de metodo
	//argv[2] es archivo de entrada
	//argv[3] es archivo de salida
	ifstream inputf(argv[2]);
	if (inputf.is_open()) {
	  //Cantidad de participantes - cantidad de partidos.
	  int T, P;
	  inputf >> T >> P;
	  Matrix C(T,T);

	  vector<vector<int> > partidos; //equipo0 equipo1 ganador(0 o 1)
	  vector<int> opcionales;
	  int opcional, i, goles_i, j, goles_j;
	  while (inputf >> opcional >> i >> goles_i >> j >> goles_j){
	    vector<int> nuevo_partido;
	    nuevo_partido.push_back(i);
	    nuevo_partido.push_back(j);
	    nuevo_partido.push_back(goles_i < goles_j);
	    partidos.push_back(nuevo_partido);
	    opcionales.push_back(opcional);
	  }

	  double* ranking = new double[T];

	  if(argv[1][0] == '0'){
	    colley(T,partidos,ranking);
	  } else if(argv[1][0] == '1'){
	    wp(T,partidos,ranking);
	  } else if(argv[1][0] == '2'){
	    nuestro_metodo(T,partidos,ranking);
	  } else {
	    cout << "Metodo invalido." << endl;
	    exit(0);
	  }

	  //Escribimos el ranking en el archivo de salida
	  ofstream outputf(argv[3]);
	  if (outputf.is_open()){
	    for(int i = 0; i < T; i++)
	      outputf << ranking[i] << "\n";
	    cout << "Ranking generado con éxito." << endl;
	  } else {
	    cout << "No se pudo abrir el archivo de salida." << endl;
	    exit(0);
	  }

	  delete[] ranking;
	}
	else {
	  cout << "No se pudo abrir el archivo de entrada." << endl;
	  exit(0);
	}
	return 0;
}

void colley(int T, vector<vector<int> > partidos, double* ranking){
	//Creamos la matriz de Colley
	Matrix C(T,T);
	for(int k = 0; k < T; k ++)
		C(k,k) = 2.0;

	//Creamos el vector b
	double* b = new double[T];
	for (int i = 0; i < T; i++) {
		b[i] = 1.0;
	}

	//Cargamos los partidos
	for(int k = 0; k < partidos.size(); k++){
		int i = partidos[k][0];
		int j = partidos[k][1];
		C(i-1,i-1)++;
		C(j-1,j-1)++;
		C(i-1,j-1)--;
		C(j-1,i-1)--;
		if (i >= j) {
			b[i] = b[i] + 0.5;
			b[j] = b[j] - 0.5;
		}
		else {
			b[i] = b[i] - 0.5;
			b[j] = b[j] + 0.5;
		}
	}

	//Guardamos en ranking la solucion del sistema Cx = b obtenida con Eliminacion Gaussiana
	EG(C,b,ranking);

	delete[] b;
}

void wp(int T, vector<vector<int> > partidos, double* ranking){
}

void nuestro_metodo(int T, vector<vector<int> > partidos, double* ranking){
}

void EG(Matrix& A, double* b, double* x){
	for(int i = 0; i < A.filas(); i++){
		x[i] = 3.5;
	}
}
