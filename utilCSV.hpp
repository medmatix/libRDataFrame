#ifndef UTILCSV_HPP_INCLUDED
#define UTILCSV_HPP_INCLUDED


#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <initializer_list>
#include <boost/any.hpp>


class utilCSV
{
protected:
    std::string fromCSVFile;
    int readToLine;
    bool hasHeader;
    int nrows;
    int ncols;
    std::string lineToParse;
    std::vector<std::string> parsedLine;
    std::vector<std::string> colNames;
    std::vector<std::string> csvToParse;
    std::vector<std::vector<std::string> > strDataStruct;

public:
    utilCSV();
    utilCSV(std::string frCSV, bool header, int rtoline = 0);
    int getNcols();
    int getNrows();
    void setNcols();
    void setNrows();
    void setColNames(std::vector<std::string> cnames);
    std::vector<std::string> getColNames();
    std::vector<std::string> getCVS();
    std::vector<std::vector<std::string> > getStrDataStruct();
    std::vector<std::string> readCSV(std::string iFileN);
    std::vector<std::string> parseLine(std::string lineToParse);
    std::vector<std::vector<std::string> > buildDataStruct(std::vector<std::string> csvToParse);
    void writeCSV(std::vector<std::vector<std::string> > strDataStruct, std::string oFName = "./data/datafile.csv");
    void displayColNames();
    void displayInternCSV();
    void displayStrDataStruct();
    std::string toString();
};


#endif // UTILCSV_HPP_INCLUDED
