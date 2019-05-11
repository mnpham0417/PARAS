#include <QApplication>

#include "graphical/GUI.hpp"

using namespace PARASProgram::Graphical;
using namespace std;

/**
 * @brief main Entry point for the PARAS GUI program
 * @param argc the # of arguments
 * @param argv the actual arguments
 * @return the outcome code.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    GUI *program = new GUI();
    program->start();
    app.connect(&app, SIGNAL(aboutToQuit()), program, SLOT(onQuit()));
    return app.exec();
}

