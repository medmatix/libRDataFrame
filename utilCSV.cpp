/**\file
 * * *Source* utilCSV.cpp (current working version of code here)
 *
 * ###C++ classes for Manipulating CSV Files
 *
 * @author David York <david@debian2x8david>
 * @date Sunday September 4, 2016
 * @version 0.4
 *
 * @brief Classes to provide C++ tools to manipulate CSV files,
 *       including reading and writing such files from and to disk
 *       into a string data structure then parsing the individual fields
 *       from the string structure.
 *
 *
 * &copy; 2016 David York
 *
 * @References *References:*
 * 1. "anno" Apr 13, 2010, http://stackoverflow.com/questions/
 * 2625411/how-to-build-a-sentence-parser-using-only-the-c-standared-library
 * 2. Shammas, Namir; C/C++ Mathematical Algorithms for Scientists and Engineers,
 * McGraw-Hill, 1995.
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <typeinfo>
#include <cxxabi.h>
#include <array>
#include <initializer_list>
#include <boost/any.hpp>

#include "utilCSV.hpp"


using namespace std;


/** Declarations */

/** Classes */

/**
 * CSV utilities class
 * @brief Contains the data structures receiving the imported data from the CSV
 * file (or going to be written to a CSV file).
 */



    /** Constructors */
    // Default constructor
    utilCSV::utilCSV() {}

    // Full constructor
    utilCSV::utilCSV(string frCSV, bool header, int rtoline) {
        fromCSVFile = frCSV;
        hasHeader = header;
        readToLine = 0;         // has no effect yet (ie. 0 = 'all')
        csvToParse = readCSV(" ");
        if(hasHeader) {         // if there is header save as column names
            lineToParse = csvToParse[0];
            parsedLine = parseLine(lineToParse);

            colNames = parsedLine;
            csvToParse.erase(csvToParse.begin());
            lineToParse = "";
        }
        else {                  // no header, Vn as column names
            lineToParse = csvToParse[0];
            parsedLine = parseLine(lineToParse);
            stringstream ss;
            string numVar;
            for(unsigned int i=0; i < parsedLine.size(); ++i) {
                ss << "V"<< i;
                numVar = ss.str();
                if(i != parsedLine.size()-1) {
                    colNames.push_back(numVar);
                }else{
                    colNames.push_back(numVar+"\n");
                }
                ss.str("");
                ss.clear();
            }
        }
        setNcols();
        setNrows();
        parsedLine.clear();
        strDataStruct = buildDataStruct(csvToParse);
    }


    /** Methods */
    //Accessors
    /** Accessor-get number of columns/variables in table*/
    int utilCSV::getNcols() {
        return ncols;
    }
    /** Accessor-get number of rows/observations in table*/
    int utilCSV::getNrows() {
        return nrows;
    }
    /** Accessor-set number of columns/variables in table*/
    void utilCSV::setNcols() {
        ncols = parsedLine.size();
    }
    /** Accessor-set number of rows/observations in table*/
    void utilCSV::setNrows() {
        nrows = csvToParse.size();
    }

    /** Accessor-reset column names*/
    void utilCSV::setColNames(vector<string> cnames) {
            if(cnames.size() == colNames.size()) {
                cnames[cnames.size()-1] = cnames[cnames.size()-1] + "\n";
                colNames = cnames;
            } else {
                cout<<" names & column names vectors do not have same length,must match"<<endl;
            }

    }

    /** Accessor-get current column names*/
    vector<string> utilCSV::getColNames() {
        return colNames;
    }

    /** Accessor-return the uploaded CSV file to caller */
    vector<string> utilCSV::getCVS() {return csvToParse;}

    /** Accessor-return the data structure (table) to caller */
    vector<vector<string> > utilCSV::getStrDataStruct() {
        return strDataStruct;
    }

    /** read a stated CSV file from disk */
    vector<string> utilCSV::readCSV(string iFileN) {
        vector<string> theCSV;
        string inFileLine;
        string inFileName = fromCSVFile;
        ifstream infile(fromCSVFile.c_str(), ios::in);
        if (!infile) {
            cout << "Could not open file." << endl;
            exit(1);
        }
        while(true) {
            infile >> inFileLine;
            if(infile.eof()) break;
            theCSV.push_back(inFileLine+"\n");
        }
        infile.close();
        return theCSV;
    }

    /**parse a line of the csv file, return it to caller */
    vector<string> utilCSV::parseLine(string lineToParse) {
        string line = "";
        line = lineToParse;
        vector<string> rowElements;
        // break the input in to tokens using a space as the delimiter
        istringstream sstream(line);
        string obsItem;
        while (!sstream.eof() ) {
            // store each obsItem in a vector
            std::getline(sstream, obsItem, ',');
            rowElements.push_back(obsItem);
        }
    return rowElements;
    }

    /** build a data Structure / Class of records of types string as vectors
     * of parsed strings of observations data (fields). */
    vector<vector<string> > utilCSV::buildDataStruct (vector<string> csvToParse) {
        vector<vector<string> > internStrDataStruct;
        for(unsigned int i = 0; i < csvToParse.size(); ++i) {
        utilCSV::parsedLine.clear();
        lineToParse = "";
        lineToParse.clear();
        lineToParse = csvToParse[i];
        parsedLine = utilCSV::parseLine(lineToParse);
        internStrDataStruct.push_back(parsedLine);
        cout << endl;

        }

        return internStrDataStruct;
    }

    /** write some data structure of strings to disk as a csv */
    void utilCSV::writeCSV(vector<vector<string> > strDataStruct, string oFName) {
        string outFileName;
        if(oFName == "") {
            outFileName = "./data/datafile.csv";
        } else outFileName = oFName;
        vector<string> dataRow;
        string csvLineOut;
        ofstream outFile(outFileName.c_str(), ios::out);
        if (!outFile) {
            cout << "Could not create file." << endl;
            exit(1);
        }
        csvLineOut = "";
        for(unsigned j = 0; j < colNames.size(); j++) {
            if(j != colNames.size() - 1) {
                csvLineOut = csvLineOut + colNames[j] + ',';
            } else {
                csvLineOut = csvLineOut + colNames[j];
            }
            outFile << csvLineOut;
            csvLineOut = "";
        }

        for(vector<vector<string> >::iterator it=strDataStruct.begin(); it != strDataStruct.end(); it++) {
            dataRow.clear();
            dataRow = *it;
            csvLineOut = "";
            for(unsigned int j = 0; j < dataRow.size(); j++){
                if(j != dataRow.size() -1) {
                    csvLineOut = csvLineOut + dataRow[j] + "," ;
                }else{
                    csvLineOut = csvLineOut + dataRow[j];
                }
            }
            outFile <<  csvLineOut;
        }
        outFile.close();
    }

    /**display the current column names */
    void utilCSV::displayColNames() {
        cout << endl << "Column Names" << endl;
        for(unsigned i = 0; i < colNames.size(); ++i) {
            if(i == unsigned(ncols -1)) {
                cout << colNames[i] << "\n";
            } else {
                cout << colNames[i]<<",  ";
            }
        }
        cout << endl;
    }

    /**display the csv data read from disk */
    void utilCSV::displayInternCSV() {
        cout << "unparsed:" << endl;
        for(unsigned i = 0; i < colNames.size(); ++i) {
            if(i == unsigned(ncols - 1)) {
                cout << colNames[i];
            } else {
                cout << colNames[i] << ",";
            }
        }
        for(unsigned i = 0; i < csvToParse.size(); ++i){
            cout << csvToParse[i];
        }
        cout << endl;
    }

    /**display the data structure of class (strDataStruct) as built */
    void utilCSV::displayStrDataStruct() {
        cout << "built data structure:" << endl << endl;
        string dashes(4 * colNames.size(), '-');
        string spaces(1, ' ');
        cout << dashes << endl;
        for(unsigned i = 0; i < colNames.size(); ++i) {
            if(i == unsigned(ncols - 1)) {
                cout << colNames[i];
            } else {
                cout << colNames[i] << spaces;
            }
        }

        vector<string> dataRow;
        string dSLineOut;
        cout << dashes << endl;
        for(vector<vector<string> >::iterator it=strDataStruct.begin(); it != strDataStruct.end(); it++) {
            dataRow.clear();
            dataRow = *it;
            dSLineOut = "";
            for(unsigned int j = 0; j < dataRow.size(); j++){
                dSLineOut = dSLineOut + dataRow[j] + " " ;
            }
            cout <<  dSLineOut << endl;
        }
        cout << dashes << endl;
    }


    /** convert a data structure to a single string object and return the object */
    string utilCSV::toString() {
        string internalContent;
        return internalContent;
    }

