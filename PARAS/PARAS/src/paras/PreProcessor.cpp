#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <cstring>

#include "PreProcessor.hpp"
#include "apriori/Apriori.hpp"

#ifdef _WIN32
#include <fcntl.h>
#define mkstemp(p) _open(_mktemp(p),_O_CREAT | _O_SHORT_LIVED | _O_EXCL)
#endif

using namespace std;

/**
 * @brief PreProcessor::PreProcessor
 * @param fileName
 * @param delimiter
 * @param minSup
 * @param minConf
 * @param sizeThreshold
 */

//constructor for csv file
PreProcessor::PreProcessor(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision, bool noQuotes)
{
    //we immediately process the csv file
    //eventually we may check file extenstion to allow further types
    cout << "Processing input file (csv)"<<endl;
    processedFile = processCSV(fileName, delimiter, minSup, minConf, sizeThreshold, precision, noQuotes);
}

//constructor for basket files
PreProcessor::PreProcessor(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision)
{
    cout << "Processing input file as Basket File" <<endl;
    processedFile = processBasketFile(fileName, delimiter, minSup, minConf, sizeThreshold, precision);
}

string PreProcessor::processBasketFile(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision) {
    char *bFile = strdup("/tmp/tmpfileXXXXXX");
    char *oFile = strdup("/tmp/tmpfileXXXXXX");
    mkstemp(bFile);
    mkstemp(oFile);

    basketFile = string(bFile);
    outputFile = string(oFile);

    //TODO: Convert to all numbers
    cout << "Converting basket("<<fileName<<") to ("<<basketFile<<")"<<endl;
    convertBasket(fileName, basketFile, delimiter, precision);

    //Add attribute map
    addStringMap(outputFile);

    //Run Basket through Apriori
    cout << "Processing converted basket("<<basketFile<<") through Apriori to output("<<outputFile<<")"<<endl;
    processApriori(basketFile, outputFile, minSup, minConf, sizeThreshold);

    remove(basketFile.c_str());
    return outputFile;
}

/**
 * @brief Processes the given csv input file into an input readable by PARAS by
 * encoding each attribute/value pair into an integer value. Also creates a mapping.
 * @param fileName the file to process
 * @return the output file
 */
string PreProcessor::processCSV(string fileName, string delimiter, double minSup, double minConf, unsigned long sizeThreshold, double precision, bool noQuotes) {
    //Create temporary file names
    char *bFile = strdup("/tmp/tmpfileXXXXXX");
    char *oFile = strdup("/tmp/tmpfileXXXXXX");
    mkstemp(bFile);
    mkstemp(oFile);


    basketFile = string(bFile);
    outputFile = string(oFile);

    //Convert CSV to Basket
    cout << "Converting csv ("<< fileName<<") to basketfile ("<<basketFile<<")"<<endl;
    csvToBasket(fileName, basketFile, delimiter, precision, noQuotes);

    //Add map onto output file
    cout << "Adding attribute map to output file"<<endl;
    addStringMap(outputFile);

    //Run Basket through Apriori
    cout << "Processing basket("<<basketFile<<") through Apriori to output("<<outputFile<<")"<<endl;
    processApriori(basketFile, outputFile, minSup, minConf, sizeThreshold);

    remove(basketFile.c_str());
    return outputFile;
}

void PreProcessor::convertBasket(string iFile, string oFile, string delimiter, double precision) {
    string line; //the currently read in line

    //Open streams
    ifstream cvsFile;
    cvsFile.open(iFile.c_str());

    ofstream basketFile;
    basketFile.open(oFile.c_str());

    //initialize encodings
    vector<string> encodings;

    cout << "Encoding values"<<endl;
    char *cstr;
    char *pch;
    //Iterate through each line of the infile
    while(getline(cvsFile, line)){
        //Tokenize it by delimiter
        cstr = new char [line.length()+1];
        strcpy (cstr, line.c_str());

        pch = strtok (cstr,delimiter.c_str());

        while (pch != NULL) {
            //and encode the current token
            //encoding = column index + 0 + value index
            //the value index is the index of that value in our vector of values
            int key;
            string value (pch);

            //trim whitespace and enclosing quotes
            size_t startpos = value.find_first_not_of(" \t");
            if( string::npos != startpos )
            {
                value = value.substr( startpos );
            }

            size_t endpos = value.find_last_not_of(" \t");
            if( string::npos != endpos )
            {
                value = value.substr( 0, endpos+1 );
            }

            //Now we handle discretization based on precision level
            double numValue = atof(value.c_str());
            if(numValue != 0.0){
                numValue = floor(numValue/precision +0.5)*precision;
                stringstream convert;
                convert << numValue;
                value = convert.str();
            }

            vector<string>::iterator it = std::find(encodings.begin(), encodings.end(), value);

            if(it == encodings.end()){
                encodings.push_back(value);
                key = encodings.size()-1;
            } else {
                key = it - encodings.begin();
            }
            //output the item
            basketFile << key << " ";

            pch = strtok (NULL, delimiter.c_str());
        }

        //add the newline
        basketFile << "\n";
    }

    //Close streams
    cvsFile.close();
    basketFile.close();

    //now build the mapping
    //variables for storing the map
    cout << "Building attribute map"<<endl;

    //iterate through each header
    mapping << "Attribute Map:\n";
    stringstream encoding_str; //left side, encodings
    stringstream value_str; //right side, values

    value_str << "(";

    for(vector<string>::size_type j = 0; j < encodings.size(); ++j){
        encoding_str << j << " ";

        //trim whitespace from value
        string val = encodings.at(j);
        size_t startpos = val.find_first_not_of(" \t");
        if( string::npos != startpos )
        {

            val = val.substr( startpos );
            std::string myString = val;
            int value = atoi(myString.c_str());

            //uncomment this part for negative rule mining.
            //if (value > encodings.size()/2)
            //{
            //    value = value - encodings.size()/2;
            //    value_str << "," << "~ " << value;
            //}

            //else
            //{
                value_str << "," << val;
            //}
            //end uncomment this part for negative rule mining.
        }
       // value_str << "," << "!" << val;
    }

    value_str << ")\n";
    mapping << encoding_str.str() << value_str.str();
}

/**
 * @brief Converts the given csv file into a basketfile
 * @param iFile the file to convert
 * @param oFile the file to output into
 * @param delimiter the delimiting character
 * @return oFile
 */
void PreProcessor::csvToBasket(string iFile, string oFile, string delimiter, double precision, bool noQuotes) {

    string line; //the currently read in line
    vector<string> headers; //all column header names
    int numColumns = 0; //the number of columns in the data

    //Open streams
    ifstream cvsFile;
    cvsFile.open(iFile.c_str());

    ofstream basketFile;
    basketFile.open(oFile.c_str());

    //get column headers
    getline(cvsFile, line);
    char *cstr;
    char *pch;
    cstr = new char [line.length()+1];
    strcpy (cstr, line.c_str());
    pch = strtok (cstr,delimiter.c_str());

    cout << "Getting column headers"<<endl;
    while (pch != NULL) {

        //pch is the header
        string value(pch);

        //clip quotes
        if(noQuotes) {
            value.erase(
                        remove( value.begin(), value.end(), '\"' ),
                        value.end()
                        );
        }

        //trim whitespace and enclosing quotes
        size_t startpos = value.find_first_not_of(" \t");
        if( string::npos != startpos )
        {
            value = value.substr( startpos );
        }

        size_t endpos = value.find_last_not_of(" \t");
        if( string::npos != endpos )
        {
            value = value.substr( 0, endpos+1 );
        }


        headers.push_back(value);
        numColumns++;
        pch = strtok (NULL, delimiter.c_str());
    }

    //initialize encodings
    vector<string> *encodings[numColumns];
    for(int i = 0; i < numColumns; ++i){
        encodings[i] = new vector<string>();
    }

    cout << "Encoding values"<<endl;
    //Iterate through each line of the infile
    int index = 0;
    while(getline(cvsFile, line)){
        //Tokenize it by delimiter
        cstr = new char [line.length()+1];
        strcpy (cstr, line.c_str());

        pch = strtok (cstr,delimiter.c_str());
        index = 0;

        while (pch != NULL) {
            //and encode the current token
            //encoding = column index + 0 + value index
            //the value index is the index of that value in our vector of values
            int key;
            string value (pch);

            //clip quotes
            if(noQuotes) {
                value.erase(
                            remove( value.begin(), value.end(), '\"' ),
                            value.end()
                            );
            }

            //trim whitespace and enclosing quotes
            size_t startpos = value.find_first_not_of(" \t");
            if( string::npos != startpos )
            {
                value = value.substr( startpos );
            }

            size_t endpos = value.find_last_not_of(" \t");
            if( string::npos != endpos )
            {
                value = value.substr( 0, endpos+1 );
            }

            //Now we handle discretization based on precision level
            double numValue = atof(value.c_str());
            if(numValue != 0.0){
                numValue = floor(numValue/precision +0.5)*precision;
                stringstream convert;
                convert << numValue;
                value = convert.str();
            }

            vector<string>::iterator it = std::find(encodings[index]->begin(), encodings[index]->end(), value);

            if(it == encodings[index]->end()){
                encodings[index]->push_back(value);
                key = encodings[index]->size()-1;
            } else {
                key = it - encodings[index]->begin();
            }
            //output the item
            basketFile << index << "0" << key << " ";

            index++;
            pch = strtok (NULL, delimiter.c_str());
        }

        //add the newline
        basketFile << "\n";
    }

    //Close streams
    cvsFile.close();
    basketFile.close();

    //now build the mapping
    //variables for storing the map
    cout << "Building attribute map"<<endl;

    //iterate through each header
    mapping << "Attribute Map:\n";
    for(int i = 0; i < numColumns; ++i){
        stringstream encoding_str; //left side, encodings
        stringstream value_str; //right side, values

        value_str << "(" << headers[i];

        for(vector<string>::size_type j = 0; j < encodings[i]->size(); ++j){
            encoding_str << i << "0" << j << " ";

            //trim whitespace from value
            string val = encodings[i]->at(j);
            size_t startpos = val.find_first_not_of(" \t");
            if( string::npos != startpos )
            {
                val = val.substr( startpos );
            }
            value_str << "," << val;
        }

        value_str << ")\n";
        mapping << encoding_str.str() << value_str.str();
    }
}

/**
 * @brief Runs apriori on the given file
 * @param iFile the file to process
 * @param oFile the file to outut to
 * @param minSup
 * @param minConf
 * @param sizeThreshold
 */
void PreProcessor::processApriori(string iFile, string oFile, double minSup, double minConf, unsigned long sizeThreshold){
    ifstream basket_file;
    basket_file.open(iFile.c_str());
    Apriori apriori(basket_file, oFile.c_str(), false);
    apriori.APRIORI_alg(minSup, minConf, true, sizeThreshold);
    basket_file.close();
}

/**
 * @brief Returns the path of the processed file
 * @return path of processed file
 */
string PreProcessor::getProcessedFile() {
    return processedFile;
}

/**
 * @brief Adds a map from integer to string for the processed file
 *onto the given file
 * @param fileName the file to add to
 */
void PreProcessor::addStringMap(string fileName) {
    ofstream output_file;
    output_file.open(fileName.c_str());
    output_file << mapping.str();
    output_file.close();
}
