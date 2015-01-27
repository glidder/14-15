// ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

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

/*
 *Function that calculates the euclidean distance between two cells
 */
float euclideanDistance (float x1, float x2, float y1, float y2){
	return (sqrt(pow(x1-x2,2)+pow(y1-y2,2)));
}

/*
 *Function that tests the feasibility for a tower position
 *It checks the potential collisions of the tower with the surrounding obstacles.
 */
bool feasibility (float cellWidth, float cellHeight, int x, int y, List<Defense*>::iterator defense, std::list<Object*> obstacles, std::list<Defense*>& defenses){
	for (List<Object*>::iterator currentObstacle = obstacles.begin(); currentObstacle != obstacles.end(); ++currentObstacle){
		float objectDistance = euclideanDistance(x*cellWidth+cellWidth*0.5f,(*currentObstacle)->position.x,y*cellHeight+cellHeight*0.5f,(*currentObstacle)->position.y);
		if(objectDistance < (*defense)->radio+(*currentObstacle)->radio){
			return false;
		}
	}
	List<Defense*>::iterator currentDefense = defenses.begin();
	while (currentDefense!=defense){
		float objectDistance = euclideanDistance(x*cellWidth+cellWidth*0.5f,(*currentDefense)->position.x,y*cellHeight+cellHeight*0.5f,(*currentDefense)->position.y);
		if(objectDistance < (*defense)->radio+(*currentDefense)->radio){
			return false;
		}
		++currentDefense;
	}
	return true;
}

/*
 *Function that assigns a value to every cell in the map
 *A higher value represents a better position for the main tower.
 */
std::vector <std::pair <std::pair<int, int>, float> > evaluateMain (int nCellsWidth, int nCellsHeight, float cellWidth, float cellHeight, std::list<Object*> obstacles){

	std::vector <std::pair <std::pair<int, int>, float> > cellVal (nCellsWidth*nCellsHeight);
	float maxDistance = euclideanDistance(0,(nCellsWidth-1)*cellWidth,0,(nCellsHeight-1)*cellHeight);
    float maxDistanceCenter = euclideanDistance(0,((nCellsWidth-1)*cellWidth)/2,0,((nCellsHeight-1)*cellHeight)/2);
	
	int i=0;
	for (int x=0; x<nCellsWidth; ++x){
		for (int y=0; y<nCellsHeight;++y){
			//First values are assigned to center the turret
			float centerValue=(maxDistanceCenter-euclideanDistance(x*cellWidth,((nCellsWidth-1)*cellWidth)/2,y*cellHeight,((nCellsHeight-1)*cellHeight)/2))/maxDistanceCenter;
			
			//Now a modifier is added according to the number of obstacles surrounding the position
			//More obstacles mean a higher value
			float obstacleValue=0;
			for (List<Object*>::iterator currentObstacle = obstacles.begin();currentObstacle != obstacles.end();++currentObstacle){
				float objectDistance = euclideanDistance(x*cellWidth+cellWidth*0.5f,(*currentObstacle)->position.x,y*cellHeight+cellHeight*0.5f,(*currentObstacle)->position.y);
				obstacleValue+=((maxDistance-objectDistance)/maxDistance)/obstacles.size();
			}

			//The sum of both values is assigned to the cell
			cellVal[i++]=std::make_pair(std::make_pair(x,y),centerValue+obstacleValue);
		}
	}

	return cellVal;
}

/*
 *Function that assigns a value to every cell in the map
 *A higher value represents a better position for a defense.
 */
std::vector <std::pair <std::pair<int, int>, float> > evaluateDefenses (int nCellsWidth, int nCellsHeight, float cellWidth, float cellHeight, Defense* mainTower){

	std::vector <std::pair <std::pair<int, int>, float> > cellVal (nCellsWidth*nCellsHeight);
	float maxDistance = euclideanDistance(0,(nCellsWidth-1)*cellWidth,0,(nCellsHeight-1)*cellHeight);

	int i=0;
	for (int x=0; x<nCellsWidth; ++x){
		for (int y=0; y<nCellsHeight;++y){
			//First values are assigned according to proximity to the main tower
			cellVal[i++]=std::make_pair(std::make_pair(x,y),(maxDistance-euclideanDistance(x*cellWidth,mainTower->position.x,y*cellHeight,mainTower->position.y))/maxDistance);
		}
	}

	return cellVal;
}

/*
 *Function for comparing pairs
 */
bool comparePair(const std::pair <std::pair<int, int>, float>& a, const std::pair <std::pair<int, int>, float>& b) {
  return a.second > b.second;
}

/*
 *Function that determines the position of the defenses
 */
void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {

	float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    List<Defense*>::iterator currentDefense = defenses.begin();
    std::vector <std::pair <std::pair<int, int>, float> > cellVal;
    std::vector <std::pair <std::pair<int, int>, float> >::iterator currentCell;

    //MAIN TOWER==============================================================================
    //Cell values for the position of the main tower are calculated
	//A higher value represents a better position.
	cellVal = evaluateMain(nCellsWidth,nCellsHeight,cellWidth,cellHeight,obstacles);
	
	//The values get sorted descendingly to try and place the tower in the best position
	std::sort(cellVal.begin(), cellVal.end(), comparePair);
	
	//We try every position from highest value to lowest
	//The tower is placed in the first feasible position
	bool positioned = false;
	currentCell = cellVal.begin();
	while(currentCell != cellVal.end() && !positioned){
		if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
			(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
        	(*currentDefense)->position.z = 0; 
        	positioned=true;
		} else {
			++currentCell;
		}
	}
	//========================================================================================

	//DEFENSES================================================================================
	//Cell values for the position of the defensive towers are calculated
	//A higher value represents a better position.
	cellVal = evaluateDefenses (nCellsWidth,nCellsHeight,cellWidth,cellHeight,*currentDefense);

	//The values get sorted descendingly to try and place the towers in the best positions
	std::sort(cellVal.begin(), cellVal.end(), comparePair);

	//We try every position from highest value to lowest
	//Each tower is placed when a feasible position is find
	currentCell = cellVal.begin();
	while(currentCell != cellVal.end() && currentDefense != defenses.end()){
		if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
			(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
        	(*currentDefense)->position.z = 0;
        	++currentDefense;
		}
		++currentCell;
	}
	//========================================================================================

#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = 42;
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
