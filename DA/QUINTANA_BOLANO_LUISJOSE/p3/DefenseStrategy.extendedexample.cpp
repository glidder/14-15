// ###### Config options ################

#define PRUEBAS_CAJA_NEGRA 1

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

using namespace Asedio;              

void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 

#ifdef PRUEBAS_CAJA_NEGRA
    //******************************************************************************************
    // Pruebas de caja negra para los algoritmos de ordenación
    //******************************************************************************************        

    // Lo que aparece a continuación es un esquema general. Deberá adaptarlo a 
    // sus necesidades.

    /*std::vector<tipocelda*> celdas();
    for(int i=0 ; i < 100 ; ++i) {
        tipocelda* celda = new tipocelda();
        celda->valor = i;
        celdas.push_back(celda);
    }

    while ( next_permutation(celdas.begin(), celdas.end(), predicado()) ) {
        tipocelda copia_celdas(celdas);
        ordenacion_fusion(copia_celdas.begin(), copia_celdas.end())
        if(!ordenado(copia_celdas)) {
            std::cout << "Error en la ordenación" << std::endl ;
    }

    sort(celdas, predicado());
    while ( next_permutation(celdas.begin(), celdas.end(), predicado()) ) {
        tipocelda copia_celdas(celdas);
        ordenacion_rapida(copia_celdas.begin(), copia_celdas.end())
        if(!ordenado(copia_celdas)) {
            std::cout << "Error en la ordenación" << std::endl ;
    }*/

#endif

    //******************************************************************************************
    // Medida del tiempo de la versión que usa la matriz para guardar los valores de las celdas
    //******************************************************************************************

    // Medir el tiempo que tardan en ejecutarse los algoritmos que colocan todas las defensas
    // de la base (centro de extracción y resto de defensas). Repetir el proceso tantas veces como sea necesario, 
    // de acuerdo al esquema de medida indirecto del tiempo.    

    // tiempo_con_matriz = ...

    //******************************************************************************************
    // Medida del tiempo de la versión que usa una lista preordenada (ordenación por fusión)
    //******************************************************************************************

    // Medir el tiempo que tardan en ejecutarse los algoritmos que colocan todas las defensas
    // de la base (centro de extracción y resto de defensas). Repetir el proceso tantas veces como sea necesario, 
    // de acuerdo al esquema de medida indirecto del tiempo.    

    // tiempo_con_preordenacion_fusion = ...

    //******************************************************************************************
    // Medida del tiempo de la versión que usa una lista preordenada (ordenación rápida)
    //******************************************************************************************

    // Medir el tiempo que tardan en ejecutarse los algoritmos que colocan todas las defensas
    // de la base (centro de extracción y resto de defensas). Repetir el proceso tantas veces como sea necesario, 
    // de acuerdo al esquema de medida indirecto del tiempo.

    // tiempo_con_preordenacion_rapida = ...

    //******************************************************************************************
    // Medida del tiempo de la versión que usa un montículo
    //******************************************************************************************

    // Medir el tiempo que tardan en ejecutarse los algoritmos que colocan todas las defensas
    // de la base (centro de extracción y resto de defensas). Repetir el proceso tantas veces como sea necesario, 
    // de acuerdo al esquema de medida indirecto del tiempo.    

    // tiempo_con_monticulo = ...

    //******************************************************************************************
    // Imprimir los tiempos de las cuatro versiones
    //******************************************************************************************

    // Imprimir una linea en la salida estándar que contenga las siguientes columnas, separadas por un tabulador:
    // número de celdas, tiempo_con_matriz, tiempo_con_preordenacion_fusion, tiempo_con_preordenacion_rapida, tiempo_con_monticulo

    //******************************************************************************************
    // Ejemplo sobre como medir el tiempo usando la clase cronómetro
    //******************************************************************************************

    // Eliminar este código una vez comprendido

	cronometro c;
    long int r = 0;
    c.activar();
    do {	
		List<Defense*>::iterator currentDefense = defenses.begin();
		while(currentDefense != defenses.end() && maxAttemps > 0) {

			(*currentDefense)->position.x = ((int)(_RAND2(nCellsWidth))) * cellWidth + cellWidth * 0.5f;
			(*currentDefense)->position.y = ((int)(_RAND2(nCellsHeight))) * cellHeight + cellHeight * 0.5f;
			(*currentDefense)->position.z = 0; 
			++currentDefense;
		}
		
		++r;
    } while(c.tiempo() < 1.0);
    c.parar();
    std::cout << (nCellsWidth * nCellsHeight) << '\t' << c.tiempo() / r << '\t' << c.tiempo()*2 / r << '\t' << c.tiempo()*3 / r << '\t' << c.tiempo()*4 / r << std::endl;
}
