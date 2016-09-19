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
#include <boost/any.hpp>

#include "dataframe.hpp"
#include "node.hpp"
#include "category.hpp"




class categoryType{
protected:
    struct categoryLevel {
    	std::string levelName;
    	int levelRank;
    };
    std::string catVarName = "";
    std::map<int, std::string> categorySet;
    std::vector<int> catVarData;
public:
    categoryType();
	categoryType(std::string vName);
    categoryType(std::string vName, int lRank, std::string lName = "");
    categoryType(std::string vName, int lRank, void* ptrData, std::string lName = "");
    categoryType(std::string vName, int lRank, std::vector<categoryLevel>* ptrData, std::string lName = "");
	void setCategoryLevels(std::vector<std::string> levelStrList, std::vector<int> levelIntList);
    void setCatVarData(std::vector<int> cData);
    std::map<int, std::string> getCategoryLevels(std::vector<std::string> levelStrList, std::vector<int> levelIntList);
    std::vector<int> getCatVarData();
    void addLevNameToData(std::vector<int> cData);
};


#endif // CATEGORY_HPP_INCLUDED
