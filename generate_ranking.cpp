#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <map>
#include "metodos.h"
using namespace std;

int main(int argc, char** argv) {
	if(argc != 4 && argc != 5){
	  cout << "Parámetros incorrectos." << endl;
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
			if(argc == 5)
	    	ranking = colley(T,partidos,argv[4][0]);
			else
	    	ranking = colley(T,partidos,'0');
	  } else if(argv[1][0] == '1'){
	    ranking = wp(T,partidos, '0');
	  } else if(argv[1][0] == '2'){
			if(argc == 5)
	    	ranking = nuestro_metodo(T,partidos,argv[4][0]);
			else{
				ranking = nuestro_metodo(T,partidos,'0');
			}
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
