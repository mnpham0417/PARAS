#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include <string>
#include <sstream>


using namespace std;

class PreProcessor
{
public:
    PreProcessor(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision, bool noQuotes);
    PreProcessor(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision);
    string getProcessedFile();
private:
    string processCSV(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision, bool noQuotes);
    string processBasketFile(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision);
    void convertBasket(string iFile, string oFile, string delimiter, double precision);
    void csvToBasket(string iFile, string oFile, string delimiter, double precision, bool noQuotes);
    void addStringMap(string fileName);
    void processApriori(string iFile, string oFile, double minSup, double minConf, unsigned long sizeThreshold);
    string processedFile;
    stringstream mapping;
    string basketFile;
    string outputFile;
};

#endif // PREPROCESSOR_HPP
