#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "metodos.h"

using namespace std;

bool mayor(double i, double j){return i > j;}

//funcion que dado un ranking y una posicion, da el numero de equipo que se encuentra
// en dicha posicion.
int equipoEnPos(const Matrix& rank, int pos){
	vector<double> posiciones;
	for(int i = 0; i < rank.filas() ; ++i){
		posiciones.push_back(rank(i,0));
	}
	vector<double> copia(posiciones.begin(), posiciones.end());
	stable_sort(posiciones.begin(), posiciones.end(), mayor);
	int res = 0;
	while(copia[res] != posiciones[pos - 1] && res < copia.size()){
		res++;
	}
	return res;
}

//funcion que dado un ranking y un equipo, devuelve su posicion en la tabla ordenada
int posEquipo(const Matrix& rank, int equipo){
	int pos = 1;
	double rankEquipo = rank(equipo,0);
	for(int i = 0; i < rank.filas() ; ++i){
		if(rank(i,0)>rankEquipo){
			pos++;
		}
	}
	return pos;
}

// funcion que dado un equipo, la cantidad de equipos, una función que calcula un ranking, y una secuencia de partidos; determina
//		el salto promedio que realizaria dicho equipo en el partido siguiente, si le ganara al resto de los equipos
double promedioSensibilidad(int equipo, int cantEquipos, Matrix (*metodo)(int, vector<vector<int> >&, char) , vector<vector<int> >& partidos){
	double res = 0;
	Matrix rankInicial;
	rankInicial = metodo(cantEquipos, partidos, '0');
	int posInicial = posEquipo(rankInicial, equipo);
	for(int i = 0 ; i < cantEquipos ; i++){
		if(i != equipo){
			vector<int> nuevo_partido;
			nuevo_partido.push_back(equipo+1);
			nuevo_partido.push_back( i+1);
			nuevo_partido.push_back( 1);
			nuevo_partido.push_back( 0);
			partidos.push_back(nuevo_partido);

			Matrix rankNuevo;
			rankNuevo = metodo(cantEquipos, partidos, '0');

			int posNueva = posEquipo(rankNuevo, equipo);

			res += posInicial - posNueva;
			partidos.pop_back();
		}
	}

	return res/(cantEquipos - 1);
}

int main(int argc, char** argv) {
	if(argc != 4 && ){
	  cout << "Debe ingresar exactamente 3 parametros." << endl;
	  exit(0);
	}
	//argv[1] es numero de metodo
	//argv[2] es archivo de entrada
	//argv[3] es archivo de salida
	char met = argv[1][0];
	ifstream inputf(argv[2]);
	if (inputf.is_open()) {
		//Cantidad de participantes - cantidad de partidos.
		int T, P;
		inputf >> T >> P;

		vector<vector<int> > partidos; //equipo0 equipo1 puntaje0 puntaje1
		int opcional, i, goles_i, j, goles_j;

		double promedios[P][3];
		int indicePartido = 0;

		while (inputf >> opcional >> i >> goles_i >> j >> goles_j){
			vector<int> nuevo_partido;
			nuevo_partido.push_back(i);
			nuevo_partido.push_back(j);
			nuevo_partido.push_back(goles_i);
			nuevo_partido.push_back(goles_j);

			partidos.push_back(nuevo_partido);

			if(met == '0'){
				Matrix matCol = colley(T, partidos, '0');
				int equipoMejor = equipoEnPos(matCol, 1);
				int equipoInter = equipoEnPos(matCol, T/2);
				int equipoPeor = equipoEnPos(matCol, T);

				promedios[indicePartido][0] = promedioSensibilidad(equipoMejor, T, colley, partidos);
				promedios[indicePartido][1] = promedioSensibilidad(equipoInter, T, colley, partidos);
				promedios[indicePartido][2] = promedioSensibilidad(equipoPeor, T, colley, partidos);
			}
			else{
				if(met == '1'){
					Matrix matWP = wp(T, partidos, '0');
					int equipoMejor = equipoEnPos(matWP, 1);
					int equipoInter = equipoEnPos(matWP, T/2);
					int equipoPeor = equipoEnPos(matWP, T);

					promedios[indicePartido][0] = promedioSensibilidad(equipoMejor, T, wp, partidos);
					promedios[indicePartido][1] = promedioSensibilidad(equipoInter, T, wp, partidos);
					promedios[indicePartido][2] = promedioSensibilidad(equipoPeor, T, wp, partidos);
				}
				else{
					if(met == '2'){
						Matrix matNM = nuestro_metodo(T, partidos, '0');
						int equipoMejor = equipoEnPos(matNM, 1);
						int equipoInter = equipoEnPos(matNM, T/2);
						int equipoPeor = equipoEnPos(matNM, T);

						promedios[indicePartido][0] = promedioSensibilidad(equipoMejor, T, nuestro_metodo, partidos);
						promedios[indicePartido][1] = promedioSensibilidad(equipoInter, T, nuestro_metodo, partidos);
						promedios[indicePartido][2] = promedioSensibilidad(equipoPeor, T, nuestro_metodo, partidos);
					}
					else{
						cout << "Metodo no valido" << endl;
					}
				}
			}
			indicePartido++;
		}

		ofstream outputf(argv[3]);
	    if (outputf.is_open()){
			for(int i = 0; i < P; i++){
				outputf << fixed << setprecision(15) << promedios[i][0] << " ";
				outputf << fixed << setprecision(15) << promedios[i][1] << " ";
				outputf << fixed << setprecision(15) << promedios[i][2] << "\n";
			}
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
