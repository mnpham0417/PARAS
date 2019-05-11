#ifndef EVENTCONTROLLER_HPP
#define EVENTCONTROLLER_HPP

#include <vector>
#include "Graphical/EventListener.hpp"
#include "Graphical/IndexUpdateEvent.hpp"
#include "Graphical/GUIEventObject.h"

using namespace std;

namespace PARASProgram
{
    namespace Graphical
    {
        class EventController
        {
            public:
                EventController(GUIEventObject *g);

                void registerListener(EventListener* el);
                void deregisterListener(EventListener* el);

                void selectStableRegions(StableRegion *primarySR, StableRegion *secondarySR);
                void applicationSizeChanged(int appWidth, int appHeight);
                void setRuleMode(RuleMode ruleMode);
                void updateIndexInfo(IndexUpdateEvent e);
                void closeIndex();
                void updateGranularity(int g);
                void updateRedundancy(int r);

            private:
                vector<EventListener*> *listeners;
                GUIEventObject *gui;
        };
    }
}
#endif // EVENTCONTROLLER_HPP
