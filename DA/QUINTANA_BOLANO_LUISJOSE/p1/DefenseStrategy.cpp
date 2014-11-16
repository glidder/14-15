// ###### Config options ################

#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
long SimpleRandomGenerator::a;
#endif

#include <math.h>
#include <utility>
#include <vector>

using namespace Asedio;              

//Function that calculates the euclidean distance between two cells
float euclideanDistance (float x1, float x2, float y1, float y2){
	return (sqrt(pow(x1-x2,2)+pow(y1-y2,2)));
}

//Function that determines the position of the defenses
void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    float maxDistance = euclideanDistance(0,(nCellsHeight-1)*cellHeight,0,(nCellsWidth-1)*cellWidth);
    float maxDistanceCenter = euclideanDistance(0,((nCellsHeight-1)*cellHeight)/2,0,((nCellsWidth-1)*cellWidth)/2);
	
	//Cell values for the position of the main tower are calculated
	//A higher value represents a better position.
	float cellValue[nCellsHeight][nCellsWidth];
	float obstacleValue[nCellsHeight][nCellsWidth];
	for (int x=0; x<nCellsHeight; ++x){
		for (int y=0; y<nCellsWidth;++y){
			//First values are assigned to center the turret
			cellValue[x][y]=(maxDistanceCenter-euclideanDistance(x*cellHeight,((nCellsHeight-1)*cellHeight)/2,y*cellWidth,((nCellsWidth-1)*cellWidth)/2))/maxDistanceCenter);
			//Now a modifier is added according to the number of obstacles surrounding the position
			//More obstacles mean a higher value, and the total value is set to 0 if the position collides with an obstacle
			obstacleValue[x][y]=0;
			for (List<Object*>::iterator currentObstacle = obstacles.begin();currentObstacle != obstacles.end();++currentObstacle){
				float objectDistance = euclideanDistance(x*cellHeight,(*curentObstacle)->position.x*cellHeight,y*cellWidth,(*currentObstacle)->position.y*cellWidth);
				if(objectDistance < currentObstacle.radio){
					cellValue[x][y]=0; obstacleValue[x][y]=-1;
				} else {
					obstacleValue[x][y]+=(maxDistance-objectDistance)/maxDistance)/obstacles.size();
				}
			}
			if(obstacleValue[x][y]>0){
				cellValue[x][y]+=obstacleValue[x][y];
			}
		}			
	}
	//TEMPORARY THING
	std::vector <std::pair <std::pair<int, int>, float>> orderedCells;
	/////////////////
	
    int maxAttemps = 1000;
    List<Defense*>::iterator currentDefense = defenses.begin();
    while(currentDefense != defenses.end() && maxAttemps > 0) {

        (*currentDefense)->position.x = ((int)(_RAND2(nCellsWidth))) * cellWidth + cellWidth * 0.5f;
        (*currentDefense)->position.y = ((int)(_RAND2(nCellsHeight))) * cellHeight + cellHeight * 0.5f;
        (*currentDefense)->position.z = 0; 
        ++currentDefense;
    }

#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = (int)(_RAND2(255));
       }
    }
    dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells
                         , cellValues, std::list<Defense*>(), true);

    for(int i = 0; i < nCellsHeight ; ++i)
        delete [] cellValues[i];
	delete [] cellValues;
	cellValues = NULL;

#endif
}
