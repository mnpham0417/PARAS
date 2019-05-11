#ifndef CREATEINDEXDIALOGBASKET_H
#define CREATEINDEXDIALOGBASKET_H

#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QCheckBox>

#include "paras/PARAS.hpp"

using namespace std;

class CreateIndexDialogBasket : public QDialog
{
    Q_OBJECT
public:
    explicit CreateIndexDialogBasket(QWidget *parent = 0, PARASProgram::PARAS *pInstance = NULL);
    string *GetFileName();

private:
    QLineEdit *iFile;
    QPushButton *iBtn;
    QGroupBox *iGroupBox;

    QLineEdit *oFile;
    QPushButton *oBtn;
    QGroupBox *oGroupBox;

    QLineEdit *minSup;
    QLineEdit *minConf;
    QLineEdit *threshold;
    QLineEdit *precision;
    QLineEdit *delimiter;

    QCheckBox *compressed;
    QPushButton *save;
    QPushButton *cancel;

    QGroupBox *buttonGroupBox;
    QGroupBox *aprioriGroupBox;
    QButtonGroup *saveCancel;

    string outFile;
    PARASProgram::PARAS *pInstance;

private slots:
    void CreateIndex();
    void GetInputFile();
    void GetOutputFile();

};

#endif // CREATEINDEXDIALOGBASKET_H
