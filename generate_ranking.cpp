#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
using namespace std;

Matrix colley(int T, vector<vector<int> >& partidos, bool calcular_error);

Matrix wp(int T, vector<vector<int> >& partidos);

Matrix nuestro_metodo(int T, vector<vector<int> >& partidos);

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

	  vector<vector<int> > partidos; //equipo0 equipo1 puntaje0 puntaje1
	  vector<int> opcionales;
	  int opcional, i, goles_i, j, goles_j;
	  while (inputf >> opcional >> i >> goles_i >> j >> goles_j){
	    vector<int> nuevo_partido;
	    nuevo_partido.push_back(i);
	    nuevo_partido.push_back(j);
	    nuevo_partido.push_back(goles_i);
	    nuevo_partido.push_back(goles_j);

	    partidos.push_back(nuevo_partido);
	    opcionales.push_back(opcional);
	  }

	  Matrix ranking;

	  if(argv[1][0] == '0'){
	    ranking = colley(T,partidos,false);
	  } else if(argv[1][0] == '1'){
	    ranking = wp(T,partidos);
	  } else if(argv[1][0] == '2'){
	    ranking = nuestro_metodo(T,partidos);
		} else if(argv[1][0] == '3'){
			ranking = colley(T,partidos,true);
		} else {
	    cout << "Metodo invalido." << endl;
	    exit(0);
	  }

	  //Escribimos el ranking en el archivo de salida
	  ofstream outputf(argv[3]);
	  if (outputf.is_open()){
	    for(int i = 0; i < T; i++)
	      outputf << fixed << setprecision(15) << ranking(i,0) << "\n";
	    cout << "Ranking generado con éxito." << endl;
	  } else {
	    cout << "No se pudo abrir el archivo de salida." << endl;
	    exit(0);
	  }
	}
	else {
	  cout << "No se pudo abrir el archivo de entrada." << endl;
	  exit(0);
	}
	return 0;
}

Matrix colley(int T, vector<vector<int> >& partidos, bool calcular_error){
	//Creamos la matriz de Colley
	Matrix C(T,T);
	for(int k = 0; k < T; k ++)
		C(k,k) = 2.0;

	//Creamos el vector b
	Matrix b(T,1);

	//Cargamos los partidos
	for(int k = 0; k < partidos.size(); k++){
		int i = partidos[k][0];
		int j = partidos[k][1];
		C(i-1,i-1)++;
		C(j-1,j-1)++;
		C(i-1,j-1)--;
		C(j-1,i-1)--;

		if (partidos[k][2] > partidos[k][3]) {
			b(i-1,0) += 1.0;
			b(j-1,0) -= 1.0;
		} else {
			b(i-1,0) -= 1.0;
			b(j-1,0) += 1.0;
		}
	}

	for (int i = 0; i < T; i++) {
		b(i,0) /= 2.0;
		b(i,0) += 1.0;
	}

	//Guardamos en ranking la solucion del sistema Cx = b obtenida con Eliminacion Gaussiana
	triangular(C,b);
	Matrix ranking = resolver_triangulado(C,b);

	if(calcular_error){
		Matrix bPrima = C*ranking;
		ofstream outputf("errores.csv");
	  if (outputf.is_open()){
	    for(int i = 0; i < T; i++){
				double error_act = ranking(i,0) - bPrima(i,0);
				if(error_act < 0)
					error_act = -error_act;
	      outputf << fixed << setprecision(15) << error_act << "\n";
	    cout << "Errores guardados con éxito." << endl;
			}
	  } else {
	    cout << "No se pudo abrir el archivo de salida de errores." << endl;
	    exit(0);
	  }
	}
	return ranking;
}

Matrix wp(int T, vector<vector<int> >& partidos){
	return Matrix(T,1);
}

Matrix nuestro_metodo(int T, vector<vector<int> >& partidos){
	map<int,double> puntajes;
	return Matrix(T,1);
}
