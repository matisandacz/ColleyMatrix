# ColleyMatrix

Informe:
https://www.overleaf.com/7834423656cndvmcqyqfrq

La sección principal de la implementación, que calcula los rankings con cualquier método se puede ejecutar con:

./main COD archivo1 archivo2 arg

COD puede ser 0, 1 o 2 para CMM, WP y nuestro método, respectivamente

arg debe ser especificado si COD es 2, para definir qué función se utilizará, exponencial o sigmoide, en cualquier otro caso es opcional. Si COD es 0, con arg = 1 se imprime el error calculado comparando Cx y b en error_numerico.csv y con arg = 2 se imprimen los pivotes de la eliminación gaussiana en pivotes.csv

archivo1 es el archivo con la competencia de entrada, escrito con el formato del ejemplo del enunciado
archivo2 es el ranking de salida, donde la i-ésima línea es el puntaje del i-ésimo equipo

El test de predicción está en prediction_test.py y se puede ejecutar con:

python prediction_test.py COD archivo1 arg

con la misma semántica de main, aunque arg solo tiene sentido para COD = 0
