//
// Created by Minh Pham on 2019-05-04.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "SequenceDatabase.h"
#include "Sequence.h"

#include <vector>

using namespace std;

/*
 * Parse a string into vetor of integer
 * @param str A string (Ex: 2 3 5)
 * @return a vector of integer
 */
vector<int> parseItemset(string str){
    vector<int> result;
    string token;
    string delimiter = " ";
    size_t pos = 0;
    int num;
    while((pos = str.find(delimiter)) != string::npos){
        token = str.substr(0, pos);
        if(token == ""){ //check if token is empty string
            str.erase(0, pos + delimiter.length());
            continue;
        }else{
            num = atoi(token.c_str());
            result.push_back(num);
        }

        //remove the token to proceed with the next token
        str.erase(0, pos + delimiter.length());
    }

    //store last item
    result.push_back(atoi(str.c_str()));

    return result;
}

/*
 * Parse a string into a sequence
 * @param str A string (Ex: 1 2 -1 3 4 -1 -2)
 * @return sequence or vector of vector of int
 */
Sequence generateSequence(string str){
    size_t pos = 0;
    string delimiter = " -1";
    Sequence result = Sequence(1);
    while ((pos = str.find(delimiter)) != string::npos) {

        string token = str.substr(0, pos);
        vector<int> itemset = parseItemset(token);
        result.addItemset(itemset);

        //remove the token to proceed with the next token
        str.erase(0, pos + delimiter.length());
    }
    return result;
}

/*
 * Parse a txt file into a Sequence Database
 * @param filename str
 */
void SequenceDatabase::loadFile(string filename) {

    //process file
    ifstream myfile ("data.txt");
    string str, token;
    string delimiter = " -1"; //this marks the end of an itemset
    int num;
    set<int> :: iterator itr;


    //process file
    if(myfile.is_open()){ //check if file is open
        while(getline(myfile, str)){
            size_t pos = 0;

            //process each set in the sequence
            Sequence sequence = generateSequence(str);
            this->data.push_back(sequence);
        }
    }
    else{
        cout << "The file is not open \n";
    }

    //close file
    myfile.close();
    cout << endl;
}

/*
 * Add a sequence to the SequenceDatabase
 * @param sequence
 */
void SequenceDatabase::addSequence(Sequence sequence) {
    this->data.push_back(sequence);
}

/*
 * Print the Sequence Database
 */
void SequenceDatabase::toString() {
    for(Sequence s : this->data){
        s.toString();
        cout << endl;
    }
}

vector<Sequence> SequenceDatabase::getSequences() {
    return this->data;
}

int SequenceDatabase::size() {
    return this->data.size();
}
