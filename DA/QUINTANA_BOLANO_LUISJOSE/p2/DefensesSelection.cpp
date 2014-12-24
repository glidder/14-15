// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include <algorithm> 
#include <iostream>
#include <vector>

using namespace Asedio;

/*
 * Function that assigns a value to each defense
 */
std::vector<float> evaluateDefenses(std::list<Defense*> defenses) {
    std::vector<float> values(defenses.size());
    std::list<Defense*>::iterator it = defenses.begin();
    for(int i=0; i<defenses.size(); ++i){
        values[i]=(((*it)->damage*(*it)->attacksPerSecond)/5)+((*it)->health/500);
        ++it;
    }
    return values;
}

/*
 * Function that returns the table of optimal solutions for each subproblem.
 */
std::vector<std::vector<float> > subproblemTable(std::list<Defense*> defenses, std::vector<float> values, unsigned int ases) {
    std::vector<std::vector<float> > subTable(defenses.size(),std::vector<float>(ases+1));

    std::list<Defense*>::iterator it = defenses.begin();
    for(int j=0;j<=ases;++j)
        subTable[0][j]=(j<(*it)->cost)? 0:values[0];
    ++it;
    for(int i=1;i<defenses.size();++i){
        for(int j=0;j<=ases;++j){
            subTable[i][j]=(j<(*it)->cost)? subTable[i-1][j]
                                                :std::max(subTable[i-1][j],subTable[i-1][j-(*it)->cost]+values[i]);
        }
        ++it;
    }

    return subTable;
}

/*
 * Function that selects the defenses to be placed
 */
void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs
            , float mapWidth, float mapHeight, std::list<Object*> obstacles) {
    
    //The first element always gets selected, and then is removed from the list
    selectedIDs.push_back(defenses.front()->id);
    ases-=defenses.front()->cost;
    defenses.pop_front();
    //The table of subproblems is calculated
    std::vector<float> values(defenses.size());
    values=evaluateDefenses(defenses);
    std::vector<std::vector<float> > subTable(defenses.size(),std::vector<float>(ases+1));
    subTable=subproblemTable(defenses,values,ases);

    //The list of objects included in the optimal solution is retrieved
    std::list<Defense*>::iterator it = defenses.begin();
    for (int i=defenses.size()-1;i>0;--i){
        if(subTable[i][ases]!=subTable[i-1][ases]){
            selectedIDs.push_back((*it)->id);
            ases-=(*it)->cost;
        }
        ++it; 
    }
    if(subTable[0][ases]!=0)
        selectedIDs.push_back((*it)->id);
}