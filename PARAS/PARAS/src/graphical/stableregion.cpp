#include <algorithm>

#include "paras/Rule.hpp"
#include "Graphical/StableRegion.hpp"

using namespace PARASProgram;
using namespace PARASProgram::Graphical;

StableRegion::StableRegion (ColorMap *cMap, double sup, double conf, set<Rule*> *allRules, set<Rule*> *uniqueRules, set<Rule*> *allRules_nr, set<Rule*> *uniqueRules_nr)
{
    this->colorMap = cMap;
    support = sup;
    confidence = conf;
    this->allRules = allRules;
    this->uniqueRules = uniqueRules;
    this->allRules_nr = allRules_nr;
    this->uniqueRules_nr = uniqueRules_nr;
    selected = false;
}

StableRegion::~StableRegion(){}

/**
 * @brief StableRegion::fullDelete fully and safely deletes the SR outside of the destructor.
 * This should be used rather than a destructor for safely deleting
 */
void StableRegion::fullDelete()
{
    allRules->clear();
    uniqueRules->clear();
    allRules_nr->clear();
    uniqueRules_nr->clear();

    set<Rule*>().swap(*allRules_nr);
    set<Rule*>().swap(*uniqueRules_nr);
    set<Rule*>().swap(*allRules);
    set<Rule*>().swap(*uniqueRules);
    delete this;
}


/**
 * @brief StableRegion::setRect sets the rectangle for the SR to the given rect.
 * @param r the rect to set for the SR.
 */
void StableRegion::setRect(QRect r){
    rect = r;
}

/**
 * @brief StableRegion::draw draws the sr using the given painter
 * @param p the painter to use
 */
void StableRegion::draw(QPainter *p)
{
    //Draws the stable region rectangle
    //updateRect();
    if(!rect.isEmpty()){
        p->save();
        p->setBrush(curColor);
        p->drawRect(rect);
        p->restore();
    }
}

/**
 * @brief StableRegion::deselect deselect the SR
 */
void StableRegion::deselect()
{
    //Reverts the color to our base
    selected = false;
}

/**
 * @brief StableRegion::highlight Highlights the SR
 */
void StableRegion::highlight()
{
    //Reverts the color to our base
    if(selected)
        return;

    curColor = QColor(200,200,200,255);
}

/**
 * @brief StableRegion::select selects the SR
 * @param secondary whether it is a secondary or primary selection
 */
void StableRegion::select(bool secondary)
{
    //Changes color to indicate selection
    selected = true;
    if(secondary)
    {
        curColor = QColor(155,155,155,255);
    }
    else
    {
        curColor = QColor(0,0,0,255);
    }
}

/**
 * @brief StableRegion::getRules retrieves the set of rules in this SR based on the
 * @param mode mode
 * @param includeRedundancies whether to include redunancies or not
 * @return the set of rules in this SR
 */
set<Rule*> *StableRegion::getRules(RuleMode mode,  bool includeRedundancies)
{
    switch(mode)
    {
        case UNIQUE:
            if(includeRedundancies)
                return uniqueRules;
            else
                return uniqueRules_nr;
        case ALL:
        if(includeRedundancies)
            return allRules;
        else
            return allRules_nr;
    }
}

/*
 * Comparator functions for sorting purposes
 */
bool StableRegion::operator < (StableRegion s){
    return (support < s.support || (confidence < s.confidence && support == s.support));
}

bool StableRegion::operator > (StableRegion s){
    return (support > s.support || (confidence > s.confidence && support == s.support));
}
