# ColleyMatrix

La sección principal de la implementación, que calcula los rankings con cualquier método se puede ejecutar con:

./main COD archivo1 archivo2 arg

COD puede ser 0, 1 o 2 para CMM, WP y nuestro método, respectivamente

arg debe ser especificado si COD es 2, para definir qué función se utilizará, exponencial o sigmoide, en cualquier otro caso es opcional. Si COD es 0, con arg = 1 se imprime el error calculado comparando Cx y b en error_numerico.csv y con arg = 2 se imprimen los pivotes de la eliminación gaussiana en pivotes.csv

archivo1 es el archivo con la competencia de entrada, escrito con el formato del ejemplo del enunciado
archivo2 es el ranking de salida, donde la i-ésima línea es el puntaje del i-ésimo equipo

El test de predicción está en prediction_test.py y se puede ejecutar con:

python prediction_test.py COD archivo1 arg
sys
con la misma semántica de main, aunque arg solo tiene sentido para COD = 0

generador_competencia.py fue utilizado en el test de error para matrices ralas y densas, guarda la competencia en competencia_generada.in porque está pensado para ser llamado por otros scripts. Se puede ejecutar con:

python generador_competencia.py NRO_EQUIPOS DENSIDAD

generador_competencia_pivotes.py fue utilizado en el test del tamaño de los pivotes, también guarda su resultado en competencia_generada.in. Se puede ejecutar con:

python generador_competencia_pivotes.py NRO_EQUIPOS NRO_PARTIDOS

graficador_ralasydensas.py fue utilizado para generar el gráfico presentado en el informe a partir de los datos en la carpeta datos_densidad, no recibe parámetros pero espera que estos archivos estén presentes

graficador_colley.py fue utilizado para visualizar matrices con diferentes densidades, recibe el archivo de la competencia

medir_error.py se puede ejecutar sin parámetros para generar los datos necesarios para el test de matrices ralas y densas

justicia.py fue utilizado para generar las posiciones en la tabla de cada uno de los equipos de la competencia. Toma un único parametro que es el archivo de texto en donde se almacenan los rankings generados por alguno de los algoritmos.

python justicia.py ARCHIVO_RANKINGS

estrategia_ganar.py fue utilizado para generar los graficos de victorias necesarias para cada conpetencia. Toma como parametro la competencia.

python estrategia_ganar.py ARCHIVO_COMPETENCIA

numeros_de_condicion1.py fue utilizado para generar el campo del numero de condicion 1. No toma parametros. Requiere de generador_competencia.py
