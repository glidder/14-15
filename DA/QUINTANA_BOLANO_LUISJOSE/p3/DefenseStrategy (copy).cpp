// ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

// #ifdef PRINT_DEFENSE_STRATEGY
// #include "ppm.h"
// #endif

// #ifdef CUSTOM_RAND_GENERATOR
// long SimpleRandomGenerator::a;
// #endif

#include <math.h>
#include <utility>
#include <vector>

using namespace Asedio;
typedef std::vector <std::pair <std::pair<int, int>, float> > values_t;
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
values_t evaluateMain (int nCellsWidth, int nCellsHeight, float cellWidth, float cellHeight, std::list<Object*> obstacles){

	values_t cellVal (nCellsWidth*nCellsHeight);
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
values_t evaluateDefenses (int nCellsWidth, int nCellsHeight, float cellWidth, float cellHeight, Defense* mainTower){

	values_t cellVal (nCellsWidth*nCellsHeight);
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

/**********************************************************************************************
 * Sorting functions
 **********************************************************************************************/
/*
 *Merge sort
 */
values_t merge(values_t l_left, values_t l_right){
	values_t result(l_left.size()+l_right.size());
	values_t::iterator ileft=l_left.begin(),
					   iright=l_right.begin(),
					   iresult=result.begin();
	while(ileft!=l_left.end() && iright!=l_right.end()){
		if(ileft->second>=iright->second){
			*iresult=*ileft;
			++ileft;
		} else {
			*iresult=*iright;
			++iright;
		}
		++iresult;
	}
	while(ileft!=l_left.end()){
		*iresult=*ileft;
		++iresult;++ileft;
	}
	while(iright!=l_right.end()){
		*iresult=*iright;
		++iresult;++iright;
	}
	return result;
}

values_t mergeSort(values_t list){
	//Base case
	if (list.size()<=1){
		return list;
	} else {
	//Recursive case
		values_t l_left(list.begin(),list.begin()+(list.size()/2)),
				 l_right(list.begin()+(list.size()/2),list.end());
		values_t fl_left=mergeSort(l_left);
		values_t fl_right=mergeSort(l_right);

		return merge(fl_left,fl_right);
	}
}

/*
 *Quick Sort
 */
values_t concatenate(values_t less, values_t equal, values_t greater){
	values_t result(greater.begin(), greater.end());
	result.insert(result.end(),equal.begin(),equal.end());
	result.insert(result.end(),less.begin(),less.end());
	return result;
}

values_t quickSort(values_t list){
	values_t less,equal,greater;
	if (list.size()>1){
		float pivot=(list.begin()+(list.size()/2))->second;
		for(values_t::iterator i=list.begin();i!=list.end();++i){
			if(i->second>pivot)
				greater.push_back(*i);
			else if(i->second==pivot)
				equal.push_back(*i);
			else
				less.push_back(*i);
		}
		return concatenate(quickSort(less),equal,quickSort(greater));
	} else {
		return list;
	}
}

/*
 *Function that returns the highest value of the vector
 */
values_t::iterator highestValue(values_t list){
	values_t::iterator current=list.begin();
	for (values_t::iterator i=list.begin();i!=list.end();++i){
		if(i->second > current->second)
			current=i;
	}
	return current;
}
/**********************************************************************************************
 **********************************************************************************************/
/*
 *Function that determines the position of the defenses
 */
void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {

	float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    List<Defense*>::iterator currentDefense;
    values_t cellVal;
    values_t::iterator currentCell;
    bool positioned;
    cronometro c;
    long int r;

    //******************************************************************************************
    // Medida del tiempo de la versión que usa la matriz para guardar los valores de las celdas
    //******************************************************************************************
    c.activar();
    do {
    	currentDefense = defenses.begin();
    	positioned=false;
    	r=0;
    	//MAIN TOWER============================================================================
    	cellVal = evaluateMain(nCellsWidth,nCellsHeight,cellWidth,cellHeight,obstacles);
		//<<<NO SORT HERE>>>
		while(cellVal.size()>0 && !positioned){
			currentCell = highestValue(cellVal);
			if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
				(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
	        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
	        	(*currentDefense)->position.z = 0; 
	        	positioned=true;
			} 
			cellVal.erase(currentCell);
		}
    	//DEFENSES==============================================================================
    	cellVal = evaluateDefenses (nCellsWidth,nCellsHeight,cellWidth,cellHeight,*currentDefense);
    	//<<<NO SORT HERE>>>
		while(cellVal.size()>0 && currentDefense != defenses.end()){
			currentCell = highestValue(cellVal);
			if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
				(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
	        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
	        	(*currentDefense)->position.z = 0;
	        	++currentDefense;
			}
			cellVal.erase(currentCell);
		}
		//======================================================================================
    	++r;
    } while(c.tiempo()<1.0);
    c.parar();
 	float tiempo_matriz = c.tiempo()/r;

 	//******************************************************************************************
    // Medida del tiempo de la versión que usa una lista preordenada (ordenación por fusión)
    //******************************************************************************************
 	c.activar();
    do {
    	currentDefense = defenses.begin();
    	positioned=false;
    	r=0;
    	//MAIN TOWER============================================================================
    	cellVal = evaluateMain(nCellsWidth,nCellsHeight,cellWidth,cellHeight,obstacles);
		cellVal = mergeSort(cellVal);//<<<SORT HERE>>>
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
    	//DEFENSES==============================================================================
    	cellVal = evaluateDefenses (nCellsWidth,nCellsHeight,cellWidth,cellHeight,*currentDefense);
    	cellVal = mergeSort(cellVal);//<<<SORT HERE>>>
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
		//======================================================================================
    	++r;
    } while(c.tiempo()<1.0);
    c.parar();
 	float tiempo_fusion = c.tiempo()/r;

 	//******************************************************************************************
    // Medida del tiempo de la versión que usa una lista preordenada (ordenación rápida)
    //******************************************************************************************
 	c.activar();
    do {
    	currentDefense = defenses.begin();
    	positioned=false;
    	r=0;
    	//MAIN TOWER============================================================================
    	cellVal = evaluateMain(nCellsWidth,nCellsHeight,cellWidth,cellHeight,obstacles);
		cellVal=quickSort(cellVal);//<<<SORT HERE>>>
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
    	//DEFENSES==============================================================================
    	cellVal = evaluateDefenses (nCellsWidth,nCellsHeight,cellWidth,cellHeight,*currentDefense);
    	cellVal=quickSort(cellVal);//<<<SORT HERE>>>
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
		//======================================================================================
    	++r;
    } while(c.tiempo()<1.0);
    c.parar();
 	float tiempo_rapido = c.tiempo()/r;

 	//******************************************************************************************
    // Medida del tiempo de la versión que usa un montículo
    //******************************************************************************************
 	c.activar();
    do {
    	currentDefense = defenses.begin();
    	positioned=false;
    	r=0;
    	//MAIN TOWER============================================================================
    	cellVal = evaluateMain(nCellsWidth,nCellsHeight,cellWidth,cellHeight,obstacles);
		std::make_heap(cellVal.begin(),cellVal.end(),comparePair);//<<<SORT HERE>>>
		while(cellVal.size()>0 && !positioned){
			currentCell = cellVal.begin();
			if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
				(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
	        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
	        	(*currentDefense)->position.z = 0; 
	        	positioned=true;
			} else {
				pop_heap(cellVal.begin(),cellVal.end(),comparePair);
				cellVal.pop_back();
			}
		}
    	//DEFENSES==============================================================================
    	cellVal = evaluateDefenses (nCellsWidth,nCellsHeight,cellWidth,cellHeight,*currentDefense);
    	std::make_heap(cellVal.begin(),cellVal.end(),comparePair);//<<<SORT HERE>>>
    	currentCell = cellVal.begin();
		while(cellVal.size()>0 && currentDefense != defenses.end()){
			currentCell = cellVal.begin();
			if(feasibility(cellWidth,cellHeight,currentCell->first.first,currentCell->first.second,currentDefense,obstacles,defenses)){
				(*currentDefense)->position.x = currentCell->first.first * cellWidth + cellWidth * 0.5f;
	        	(*currentDefense)->position.y = currentCell->first.second * cellHeight + cellHeight * 0.5f;
	        	(*currentDefense)->position.z = 0;
	        	++currentDefense;
			}
			pop_heap(cellVal.begin(),cellVal.end(),comparePair);
			cellVal.pop_back();
		}
		//======================================================================================
    	++r;
    } while(c.tiempo()<1.0);
    c.parar();
 	float tiempo_monticulo = c.tiempo()/r;

 	std::cout << (nCellsWidth * nCellsHeight) << '\t' << tiempo_matriz << '\t' << tiempo_fusion << '\t' << tiempo_rapido << '\t' << tiempo_monticulo << std::endl;

// #ifdef PRINT_DEFENSE_STRATEGY

//     float** cellValues = new float* [nCellsHeight]; 
//     for(int i = 0; i < nCellsHeight; ++i) {
//        cellValues[i] = new float[nCellsWidth];
//        for(int j = 0; j < nCellsWidth; ++j) {
//            cellValues[i][j] = 42;
//        }
//     }
//     dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells
//                          , cellValues, std::list<Defense*>(), true);

//     for(int i = 0; i < nCellsHeight ; ++i)
//         delete [] cellValues[i];
// 	delete [] cellValues;
// 	cellValues = NULL;

// #endif
}
