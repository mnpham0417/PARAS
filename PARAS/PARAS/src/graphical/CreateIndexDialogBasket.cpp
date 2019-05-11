#include <QLineEdit>
#include <QApplication>
#include <QFormLayout>
#include <QDoubleValidator>
#include <QPushButton>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <QLabel>
#include <QFont>

#include "CreateIndexDialogBasket.h"

CreateIndexDialogBasket::CreateIndexDialogBasket(QWidget *parent, PARASProgram::PARAS *pInstance) :
    QDialog(parent)
{
    this->pInstance = pInstance;
    setWindowTitle(tr("Create new PSpace Index"));
    setWindowModality(Qt::WindowModal);

    //handle layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //Construct the file selection box
    //input file
    this->setStyleSheet("*[valid='false'] { background-color: gray }");

    iFile = new QLineEdit(this);
    iBtn = new QPushButton("Browse", this);
    QObject::connect(iBtn, SIGNAL(pressed()), this, SLOT(GetInputFile()));
    iFile->setPlaceholderText("Select a Data File");

    QHBoxLayout *iGroupLayout = new QHBoxLayout;
    iGroupLayout->addWidget(iFile);
    iGroupLayout->addWidget(iBtn);
    iGroupBox = new QGroupBox(tr("Data File"));
    iGroupBox->setLayout(iGroupLayout);

    //output file
    oFile = new QLineEdit(this);
    oBtn = new QPushButton("Browse", this);
    QObject::connect(oBtn, SIGNAL(pressed()), this, SLOT(GetOutputFile()));
    oFile->setPlaceholderText("Save Location");

    QHBoxLayout *oGroupLayout = new QHBoxLayout;
    oGroupLayout->addWidget(oFile);
    oGroupLayout->addWidget(oBtn);
    oGroupBox = new QGroupBox(tr("Output File"));
    oGroupBox->setLayout(oGroupLayout);

    //construct the Apriori input box
    QDoubleValidator *supConfVal = new QDoubleValidator( 0.0001, .9999, 4, this );
    QDoubleValidator *precisionVal = new QDoubleValidator( 0.00000001, 10000000, 8, this );
    supConfVal->setNotation(QDoubleValidator::StandardNotation);
    precisionVal->setNotation(QDoubleValidator::StandardNotation);

    //minsup
    minSup = new QLineEdit(this);
    minSup->setValidator(supConfVal);
    minSup->setText("0.3");

    //minconf
    minConf = new QLineEdit(this);
    minConf->setValidator(supConfVal);
    minConf->setText("0.3");

    //size threshold
    threshold = new QLineEdit(this);
    threshold->setValidator(new QIntValidator(this));
    threshold->setText("1");

    //precision
    precision = new QLineEdit(this);
    precision->setValidator(precisionVal);
    precision->setText("1.0");

    //delimiter
    delimiter = new QLineEdit(this);
    delimiter->setText(" ");

    //compression
    compressed = new QCheckBox(this);
    compressed->setChecked(false);

    QFormLayout *aprioriFormLayout = new QFormLayout;
    aprioriGroupBox = new QGroupBox(tr("Import Parameters"));
    aprioriFormLayout->addRow(tr("&Minimum Support:"), minSup);
    aprioriFormLayout->addRow(tr("&Minimum Confidence:"), minConf);
    aprioriFormLayout->addRow(tr("&Threshold Value:"), threshold);
    aprioriFormLayout->addRow(tr("&Number Precision:"), precision);
    aprioriFormLayout->addRow(tr("&Delimiter:"), delimiter);
    aprioriFormLayout->addRow(tr("&Compress JSON:"), compressed);
    aprioriGroupBox->setLayout(aprioriFormLayout);

    //Construct the save and cancel buttons
    save = new QPushButton("Create Index", this);
    QObject::connect(save, SIGNAL(pressed()), this, SLOT(CreateIndex()));

    cancel = new QPushButton("   Cancel   ", this);
    cancel->setDefault(true);
    QObject::connect(cancel, SIGNAL(pressed()), this, SLOT(reject()));

    QHBoxLayout *buttonGroupLayout = new QHBoxLayout;
    buttonGroupBox = new QGroupBox();
    buttonGroupLayout->addWidget(cancel);
    buttonGroupLayout->addWidget(save);
    buttonGroupBox->setLayout(buttonGroupLayout);
    buttonGroupBox->setFlat(true);

    QLabel *header = new QLabel("Create New Index");
    header->setAlignment(Qt::AlignHCenter);
    QFont f;
    f.setBold(true);
    f.setPointSize(12);
    header->setFont(f);

    mainLayout->addWidget(header);
    mainLayout->addWidget(iGroupBox);
    mainLayout->addWidget(oGroupBox);
    mainLayout->addWidget(aprioriGroupBox);
    mainLayout->addWidget(buttonGroupBox);

    setLayout(mainLayout);
    iFile->clearFocus();
    oFile->clearFocus();
    this->setFocus();
}

//Creates a filedialog for the user to select the input file
void CreateIndexDialogBasket::GetInputFile () {
    QString fileChosen = QFileDialog::getOpenFileName(this, QString("Open Data File."), QString(), QString("*"));
    if(fileChosen != NULL) {
        iFile->setText(fileChosen);
        if(oFile->text() == ""){
            string newOutFile = fileChosen.toStdString();
            newOutFile = newOutFile.substr(0, newOutFile.length() - 4)+".psi";
            oFile->setText(QString::fromStdString(newOutFile));
        }
    }
    iFile->clearFocus();
}

//Creates a filedialog for the user to select where to save the output file
void CreateIndexDialogBasket::GetOutputFile () {
    QString fileChosen = QFileDialog::getSaveFileName(this, QString("Select Save Location."), QString(), QString("*.psi"));
    if(fileChosen != NULL) {
        oFile->setText(fileChosen);
        outFile = fileChosen.toStdString();
    }
    oFile->clearFocus();
}

//Create the index, called on acceptance
void CreateIndexDialogBasket::CreateIndex() {
    double minSupport = minSup->text().toDouble();
    double minConfidence = minConf->text().toDouble();
    double precisionVal = precision->text().toDouble();
    unsigned long thresholdVal = threshold->text().toULong();
    bool compress = compressed->isChecked();
    string delim = delimiter->text().toStdString();
    string iFilePath = iFile->text().toStdString();
    outFile = oFile->text().toStdString();

    //check if files are valid
    string oExt;

    if(outFile.size() >= 4){
        oExt = outFile.substr(outFile.length() - 4, outFile.npos);
    } else {
        oExt = "";
    }

    bool iValid = (fstream(iFilePath.c_str()).good());
    bool oValid = (oExt.compare(".psi") == 0 || oExt.compare(".PSI") == 0);


    if(!iValid || !oValid) return; //if no valid extensioned file is selected, do nothing.
    pInstance->createIndexBasket(iFilePath, outFile, delim, minSupport, minConfidence, thresholdVal, precisionVal, compress);
    accept();
}

string *CreateIndexDialogBasket::GetFileName(){
    return new string(outFile);
}


