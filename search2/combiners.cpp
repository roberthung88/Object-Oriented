#include "combiners.h"
using namespace std;
// Place your function implementations for your derived
// WebPageSetCombiner classes here


WebPageSet ANDWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet result;
    for(set<WebPage*>::iterator it=setA.begin(); it != setA.end(); ++it){
        if(setB.find(*it) != setB.end()){
            //found in setB so add to result
            result.insert(*it);
        }
    }
    return result;
}


WebPageSet ORWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet result = setA;
    result.insert(setB.begin(), setB.end());
    return result;
}


WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet result = setA;
    for(set<WebPage*>::iterator it = setB.begin(); it != setB.end(); ++it){
        if(result.find(*it) != result.end()){
            //found in setB so add to result
            result.erase(*it);
        }
    }
    return result;
}

