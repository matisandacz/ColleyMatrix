#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <map>
using namespace std;

Matrix colley(int T, vector<vector<int> >& partidos, char arg);

Matrix wp(int T, vector<vector<int> >& partidos);

Matrix nuestro_metodo(int T, vector<vector<int> >& partidos, char arg);

double f(int d,int T, char arg); //funcion de asignacion de puntaje de nuestro metodo

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
	    	ranking = colley(T,partidos,*argv[4]);
			else
	    	ranking = colley(T,partidos,'0');
	  } else if(argv[1][0] == '1'){
	    ranking = wp(T,partidos);
	  } else if(argv[1][0] == '2'){
			if(argc == 5)
	    	ranking = nuestro_metodo(T,partidos,*argv[4]);
			else
				ranking = nuestro_metodo(T,partidos,'0');
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

Matrix colley(int T, vector<vector<int> >& partidos, char arg){
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

	if(arg == '1'){
		Matrix bPrima = C*ranking;
		ofstream outputf("error_numerico.csv");
	  if (outputf.is_open()){
	  	double epsilon = 0.0;
	    for(int i = 0; i < T; i++){
				double error_act = b(i,0) - bPrima(i,0);
				if(error_act < 0) {
					error_act = -error_act;
				}
				epsilon += error_act;
			}
		outputf << fixed << setprecision(15) << (epsilon/ ((double)T) ) << "\n";
	    cout << "Error de aproximacion guardado con éxito." << endl;
	  } else {
	    cout << "No se pudo abrir el archivo de salida de errores." << endl;
	    exit(0);
	  }
	}
	return ranking;
}

Matrix wp(int T, vector<vector<int> >& partidos){
	//T es la cantidad de equipos
	//partidos contiene vectores <EQUPO0 EQUIPO1  puntaje0 puntaje1>
	//Creamos un diccionario infoJugadores que dado un equipo i, nos da un vector <#GANADOS, #TOTAL_JUGADOS>
	vector<pair<int,int> > infoJugadores;
	for(int i = 0; i < T; i++)
		infoJugadores.push_back(pair<int,int>(0,0)); //al principio nadie jugo nada
	for(int i = 0; i < partidos.size(); i++){
		int equipo0 =  partidos[i][0] - 1;
		int equipo1 =  partidos[i][1] - 1;
		int puntaje0 =  partidos[i][2];
		int puntaje1 =  partidos[i][3];
		/*CASO GANA EL EQUIPO 0*/
		if(puntaje0 > puntaje1){
			//Sumamos un ganado al primer equipo
			infoJugadores[equipo0].first +=1;
			//Sumamos un partido jugado al primer equipo
			infoJugadores[equipo0].second +=1;
			//Sumamos un partido jugado al segundo equipo
			infoJugadores[equipo1].second +=1;
		}
			/*CASO GANA EL EQUIPO 1*/
		else{
			//Sumamos un ganado al segundo equipo
			infoJugadores[equipo1].first +=1;
			//Sumamos un partido jugado al primer equipo
			infoJugadores[equipo0].second +=1;
			//Sumamos un partido jugado al segundo equipo
			infoJugadores[equipo1].second +=1;
		}
	}
	//Creamos la matriz de rankings de acuerdo a #Ganados/#Total_jugados
	Matrix ranking = Matrix(T,1);

	for (int i = 0; i < T; i++) {
		if(infoJugadores[i].second != 0){
			ranking(i,0) = (double)infoJugadores[i].first / (double)infoJugadores[i].second;
		}else
			ranking(i,0) = -1; //-1 si no se puede calcular porque todavia no jugo
	}

	return ranking;
}

Matrix nuestro_metodo(int T, vector<vector<int> >& partidos, char arg){
	Matrix tabla(T,1); //puntaje de cada equipo, al principio es 0
	for(int i = 0; i < partidos.size(); i++){
		int rank1 = 1;
		int rank2 = 1;
		for(int j = 0; j < T; j++){
			if(tabla(j,0) > tabla(partidos[i][0]-1,0)) rank1++;
			if(tabla(j,0) > tabla(partidos[i][1]-1,0)) rank2++;
		}
		if(partidos[i][1] > partidos[i][3]){
			tabla(partidos[i][0],0) += f(rank1 - rank2, T, arg);
			tabla(partidos[i][2],0) -= f(rank1 - rank2, T, arg);
		} else {
			tabla(partidos[i][0],0) += f(rank2 - rank1, T, arg);
			tabla(partidos[i][2],0) -= f(rank2 - rank1, T, arg);
		}
	}
	return tabla;
}

double f(int d, int T, char arg){ //si type es true es exponencial y si es false es sigmoidea
	if(arg == '0')
		return exp(d*(log(T)/(double)T)); //no me pregunten por que, fueron los parametros que mas me gustaron
	else if(arg == '1')
		return 1.0/(1.0+exp(-d*(log(T)/(double)T)));
	else
		return 0.5+(2.0/(double)T)*(double)d;
}
