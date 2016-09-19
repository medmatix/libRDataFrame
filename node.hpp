#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED


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



class node {
protected:
    int nrows = 0;
    std::string varName = "";
    std::string varType = "";
    int varNumber = 0;
    void* ptrData = nullptr;
    void* retPtr = nullptr;
    std::vector<int>* ivData = nullptr;
    std::vector<double>* dvData= nullptr;
    std::vector<std::string>* svData= nullptr;
    std::vector<int>* cvData = nullptr;
    std::map<int, std::string> categorySet;
    std::vector<int> catVarData;
public:
    node();
    node(int r, std::string vName, std::string vType, int vNumber);
    node(int r, std::string vName, std::string vType, int vNumber, std::map<int, std::string>  catSet);
    node(int r, std::string vName, std::string vType, int vNumber, void* pvData);
    void* getVarDataRange(int start, int ending);
    void* getVarData();
    std::string getVarName();
    std::string getVarType();
    int getVarNumber();
    int getNRows();
    std::vector<int> getNodeIntData (void* pData);
    std::vector<double> getNodeDblData (void* pData);
    std::vector<std::string> getNodeStrData (void* pData);
    std::vector<int> getNodeCatData (void* pData);
    void setNodeContent(int r, std::string vName, std::string vType, int vNumber, void* pvData);
    void setVarDataRows(int r);
    void setVarData(void* pvData);
    void setVarName(std::string vName);
    void setVarType(std::string vType);
    void setVarNumber(int vNumber);
    void displayNode();
    void displayName_Type();
    std::string toString();
};

#endif // NODE_HPP_INCLUDED
