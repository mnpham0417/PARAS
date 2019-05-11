#include <QRadioButton>
#include <QButtonGroup>

#include "graphical/ruleview/RuleView.hpp"
#include "graphical/ruleview/singlerule/SingleView.hpp"
#include "graphical/ruleview/doublerule/DoubleRuleTable.hpp"

using namespace PARASProgram::Graphical;

/**
 * @brief RuleView::RuleView creates the rule view that will display multiple different representations of rules
 * @param parent the parent
 * @param evCont the event controller
 * @param coloring the color map to follow
 */
RuleView::RuleView(QWidget *parent, EventController *evCont, ColorMap *coloring) : QFrame(parent)
{
    this->colorMapping = coloring;
    singRT = new SingleView(this,evCont, coloring);
    singRT->setVisible(true);

    doubRT = new DoubleRuleTable(this,evCont);
    doubRT->setVisible(false);
}

/**
 * @brief RuleView::paintEvent paints the title for the rule view.
 * @param e the paint event
 */
void RuleView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QFont newFont = font();

    QFontMetrics fm(newFont);
    setFont(newFont);


    painter.drawText(width() / 2 - fm.width("Rule Space View")/2, 30, "Rule Space View");
}

/**
 * @brief RuleView::selectStableRegions updates the SR selection
 * @param primarySR
 * @param secondarySR
 */
void RuleView::selectStableRegions(StableRegion *primarySR, StableRegion *secondarySR)
{
    doubRT->setVisible(false);
    singRT->setVisible(true);

    if(primarySR == NULL)
    {
        singRT->selectStableRegions(secondarySR, primarySR);
    }
    else
    {
        singRT->selectStableRegions(primarySR,secondarySR);
    }

    doubRT->selectStableRegions(primarySR,secondarySR);

    if(primarySR != NULL && secondarySR != NULL)
    {
        doubRT->setVisible(true);
        singRT->setVisible(false);
    }
}

/**
 * @brief RuleView::applicationSizeChanged updates the size of the rule view based on the app's width/height
 * @param width the new width of the app
 * @param height the new height of the app
 */
void RuleView::applicationSizeChanged(int width, int height)
{
    int thisWidth = (width / 2 - 50);
    this->move(width/2+25,0);
    this->resize(thisWidth,height);

    singRT->applicationSizeChanged(thisWidth, height);
    doubRT->applicationSizeChanged(thisWidth,height );
}

/**
 * @brief RuleView::setRuleMode updates the rule mode
 * @param ruleMode the new rule mode
 */
void RuleView::setRuleMode(RuleMode ruleMode)
{
    singRT->setRuleMode(ruleMode);
    doubRT->setRuleMode(ruleMode);
}

/**
 * @brief RuleView::updateIndexInfo Updates the index info
 * @param e the new index info
 */
void RuleView::updateIndexInfo(IndexUpdateEvent e)
{
    singRT->updateIndexInfo(e);
    doubRT->updateIndexInfo(e);
}

/**
 * @brief RuleView::updateRedundancy sets whether to show redundancies
 * @param include whether to include redundancies or not
 */
void RuleView::updateRedundancy(bool include)
{
    singRT->updateRedundancy(include);
    doubRT->updateRedundancy(include);
}

/**
 * @brief RuleView::closeIndex closes the index information in the rule view.
 */
void RuleView::closeIndex()
{
    singRT->closeIndex();
    doubRT->closeIndex();
    singRT->setVisible(true);
    doubRT->setVisible(false);
}
