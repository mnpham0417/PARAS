#include "Graphical/EventController.hpp"
#include "Graphical/StableRegion.hpp"
#include "Graphical/EventListener.hpp"

using namespace PARASProgram::Graphical;

/**
 * @brief EventController::EventController creates an event controller that communicates to the given GUIEventObject
 * @param g the guieventobject to communicate with
 */
EventController::EventController(GUIEventObject *g)
{
    listeners = new vector<EventListener*>();
    gui = g;
}

/**
 * @brief EventController::registerListener adds a listener to be talked to when an event happens
 * @param el the listener to add
 */
void EventController::registerListener(EventListener* el)
{
    listeners->push_back(el);
}

/**
 * @brief EventController::deregisterListener removes a listener from the listener list.
 * @param el the listener to remove.
 */
void EventController::deregisterListener(EventListener *el)
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        if(listeners->at(i) == el)
        {
            listeners->erase(listeners->begin() + i);
            break;
        }
    }
}

/**
 * @brief EventController::selectStableRegions communicates to all listeners that a stable region has been selected.
 * @param primarySR the first SR selected
 * @param secondarySR the second SR selected
 */
void EventController::selectStableRegions(StableRegion *primarySR, StableRegion *secondarySR)
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->selectStableRegions(primarySR, secondarySR);
    }
}

/**
 * @brief EventController::applicationSizeChanged communicates to all listeners that the application size has changed
 * @param appWidth the appWidth
 * @param appHeight the App height
 */
void EventController::applicationSizeChanged(int appWidth, int appHeight)
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->applicationSizeChanged(appWidth, appHeight);
    }
}

/**
 * @brief EventController::setRuleMode communicates to all listeners that the rule mode has changed
 * @param ruleMode the new rule mode.
 */
void EventController::setRuleMode(RuleMode ruleMode)
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->setRuleMode(ruleMode);
    }
}

/**
 * @brief EventController::updateIndexInfo communicates to all listeners that the index info has changed
 * @param e the new index info
 */
void EventController::updateIndexInfo(IndexUpdateEvent e)
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->updateIndexInfo(e);
    }
}

/**
 * @brief EventController::closeIndex tells all listeners to close the index.
 */
void EventController::closeIndex()
{
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->closeIndex();
    }
}

/**
 * @brief EventController::updateGranularity tells the GUI object to update the granularity
 * @param g the new granularity
 */
void EventController::updateGranularity(int g){
    gui->updateGranularity(g);
}

/**
 * @brief EventController::updateRedundancy tells the gui object to update the redundancy exclusion/inclusion.
 * @param r the new redundancy
 */
void EventController::updateRedundancy(int r) {
    for(size_t i = 0; i < listeners->size(); i++)
    {
        listeners->at(i)->updateRedundancy(r);
    }

    gui->updateRedundancy(r);
}

