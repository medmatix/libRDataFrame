#ifndef CATEGORY_HPP_INCLUDED
#define CATEGORY_HPP_INCLUDED

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
#include <utility>
#include <boost/any.hpp>

#include "dataframe.hpp"
#include "node.hpp"
#include "category.hpp"


class categoryType{
protected:
    int nRows;
    int nLevels;
    std::string catVarName = "";
    std::vector<int> dummySet;
    std::map<int, std::string> categorySet;
    std::vector<int> catVarRanks;
    std::vector<std::vector<int> > dummyVarData;
public:
    categoryType();
	categoryType(std::string vName);
    categoryType(std::string vName, std::map<int,std::string> catSet);
    categoryType(std::string vName, std::map<int,std::string> catSet, void* ptrData);
    categoryType(std::string vName, void* ptrData);
    categoryType(std::string vName, std::map<int,std::string> catSet, std::vector<int>* ptrData);

	std::vector< std::vector<int> >getDummyVarData();
    void setCategoryLevels(std::vector<std::string> levelStrList, std::vector<int> levelIntList);
    void setCatVarRanks(std::vector<int> cData);
    void setDummyVarData(std::vector< std::vector<int> > dummyVData);
    std::map<int, std::string> getCategoryLevels();
    std::vector<int> getCatVarRanks();
    void addLevNameToData(std::vector<int> cData);
};


#endif // CATEGORY_HPP_INCLUDED
