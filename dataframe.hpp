#ifndef DATAFRAME_HPP_INCLUDED
#define DATAFRAME_HPP_INCLUDED

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
#include "node.hpp"



class dataframe {
protected:
    int nrows;
    int ncols;
    std::string dfName;
    node varsGrp;
    std::vector<node> df;
    std::vector<std::string> colNames;
    std::vector<std::string> varTypes;
    void* obsDataFrame = nullptr;
    std::vector<std::string> obsRowNames;
public:

    dataframe();
    dataframe(node varNode);
    dataframe(std::string s, int r, int c);
protected:
    std::vector<std::string> createTypesVector();
    void createObsDataframe();
    boost::any createObsTuple();

public:
    std::vector<node> getDataframe();
    std::string getDataFrameName();
    void* getObs(int rowNumber);
    node getNode(std::string vName= "", int vNumber = 0);
    std::vector<std::string> getRangeOfRows(int start, int ending);
    void* getDataRange(int r1,int c1,int r2, int c2);
    std::vector<std::string> getVarNames();
    std::vector<std::string> getVarTypes();
    void addObsRow(void* obsRow);
    void setNode(node varNode, int vNumber);
    void convertDfToVStrings(dataframe df);
    void convertParsedVStrtoDf(std::vector< std::vector<std::string> > parsedVVS);
    void loadFromCSV(std::string csvFName, bool header);
    std::vector<std::vector<std::string> > makeDataFrame (std::vector<std::vector<std::string> > intStrDStruct);
    void saveToCSV(std::string csvFName);
    void displayDataframe();
    void displayNodeData(int position=0, std::string varName="");
    std::string toStringStream();
};



#endif // DATAFRAME_HPP_INCLUDED
