/** \file
 * \page Node
 *
 * Source Files:
 *
 * *Node.cxx*
 *
 * (see also *RDataframe*, *UtilCSV37.cpp*, *Category.cpp* and *main.cpp*.)
 *
 * ##A Node Class to contain a variable
 *
 * @author David York
 * @date Sunday September 18, 2016
 * @version 0.8
 *
 * @brief This creates a Node class to contain the data and meta-data of a
 *  variable. The Variable Nodes ultimately formpart of the Dataframe class
 *  which is simply a vector of Nodes.
 *
 *  It's data, is implemented as a pointer to a vector containing the data.
 *
 *  In an Abstract sense, the Nodes are the variables, as contained for example
 *  in a vector of Nodes which is the Dataframe structure.
 *  The meta-data defines the variable fully and a void* pointer to a vector<any>
 *  containing the observation data of the#include "dataframe.cpp" variable.
 *
 *  Class methods allow maintenance and manipulation of the variable it's data
 *  as to variable name, variable (data) type variable id (or position) within
 *  any containing structure and the observation data itself.
 *
 *
 *
 *
 * &copy; 2016 David York
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

#include "node.hpp"


using namespace std;

/** default constructor */
        node::node() {
            varName = "";
            varType = "";
            varNumber = 0;
            ptrData = nullptr;

        }

        /** constructor with meta-data for variables and data as pointer to null
         *  @param r and integer value for the total number of rows of data at
         *           void* ptrData
         *  @param vName a tring with the node and variable's name
         *  @param vType a string recording the variable type stored by the
         *         node at pointer ptrData
         *  @param vNumber an integer value with the node number (position
         *         in RDataframe)
         */
        node::node(int r, string vName, string vType, int vNumber) {
            nrows = r;
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = nullptr;
        }

        /** constructor with meta-data for category variable and data as pointer to null
         *  @param r and integer value for the total number of rows of data at
         *           void* ptrData
         *  @param vName a tring with the node and variable's name
         *  @param vType a string recording the variable type stored by the
         *         node at pointer ptrData
         *  @param vNumber an integer value with the node number (position
         *         in RDataframe)
         *  @param catSet a categorySet mapping levels. integers to names
         */
        node::node(int r, string vName, string vType, int vNumber, map<int, string>  catSet) {
            nrows = r;
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = nullptr;
        }

        /** constructor all meta data for variable and data as void pointer to
         *  a vector of actual type vector<vType>
         *  @param r and integer value for the total number of rows of data at
         *           void* ptrData
         *  @param vName a tring with the node and variable's name
         *  @param vType a string recording the variable type stored by the
         *         node at pointer ptrData
         *  @param vNumber an integer value with the node number (position
         *         in RDataframe)
         *  @param pvData a void pointer to the block of data (of type vType)
         *         in memory.
         */
        node::node(int r, string vName, string vType, int vNumber, void* pvData) {
            nrows = r;
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = pvData;
        }



        /** the Node class methods */
        //--------------------------------------------------------

        /** get a range of variable data from the node vector
         *  Remember! The varType needs to be used to type the data of the
         *  returned pointer
         *  @param start - the starting index for the range of data.
         *  @param the ending index for the range
         *  @return a (void) pointer to the start of memory containing the data range
         */
        void* node::getVarDataRange(int start, int ending) {
            if (varType == "int") {
                vector<int> vData = getNodeIntData(ptrData);
                static vector<int> extractData;
                for (int i = start; i <= ending; ++i) {
                    extractData.push_back(vData[i]);
                }

                cout << "extraction complete"<< endl;
                return &extractData;
		    }
		    else if (varType == "double") {
                vector<double> vData = getNodeDblData(ptrData);
                static vector<double> extractData;
                for (int i = start; i <= ending; ++i) {
                    extractData.push_back(vData[i]);
                }

                cout << "extraction complete"<< endl;
                return &extractData;
		    }
		    else if (varType == "string") {
                vector<string> vData = getNodeStrData(ptrData);
                static vector<string> extractData;
                for (int i = start; i <= ending; ++i) {
                    extractData.push_back(vData[i]);
                }

                cout << "extraction complete"<< endl;
                return &extractData;
		    }
		    else if (varType == "categoryType") {
                vector<int> vData = getNodeCatData(ptrData);
                static vector<int> extractData;
                for (int i = start; i <= ending; ++i) {
                    extractData.push_back(vData[i]);
                }

                cout << "extraction complete"<< endl;
                return &extractData;
		    }
		    else {
                cout << "Range Error" << endl;
                return nullptr;
		    }
        }

        /** get all of the variable data from the node vector as a raw data
         * requires variable type to fetch pointer
         *  @param none
         *  @return a pointer to the start of memory containing the data vector
         */
        void* node::getVarData() {
            return ptrData;
        }

        /** get the variable name (node meta-datum varName)
         *  @param none
         *  @return the variable name (string)
         */
        string node::getVarName() {
            return varName;
        }

        /** get the variable type (node meta-datum varType)
         *  @param none
         *  @return the variable type (string)
         */
        string node::getVarType() {
            return varType;
        }

        /** get the variable (position) number (node meta-datum varNumber)
         *  @param none
         *  @return the variable number (int)
         */
        int node::getVarNumber() {
            return varNumber;
        }

        /** get nrows, the number of data rows in the Node vector
         *  @param none
         *  @return nrows, an int with the number of data rows in vector
         */
        int node::getNRows() {
            return nrows;
        }

        /** get Node data as a vector of integers
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<int> with the Node data
         */
        vector<int> node::getNodeIntData (void* pData) {
             ivData = (vector<int>*) ptrData;
             return *ivData;
        }

        /** get Node data as a vector of doubles
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<double> with the Node data
         */
        vector<double> node::getNodeDblData (void* pData) {
            dvData = (vector<double>*) ptrData;
            return *dvData;
         }

         /** get Node data as a vector of strings
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<string> with the Node data
         */
         vector<string> node::getNodeStrData (void* pData) {
             svData = (vector<string>*) ptrData;
             return *svData;
         }

         /** get Node data as a vector of categories or factors
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<int> with the Node data
         */
         vector<int> node::getNodeCatData (void* pData) {
             cvData = (vector<int>*) ptrData;
             return *cvData;}

        //--------------------------------------------------------
        /** set the variable data, with a pointer to the data vector
         *  @param r, int with the number of rows in data vector (i.e its size)
         *  @param vName, string with variable name
         *  @param vType, string with variable type
         *  @param vNumber, int with variable (position number
         *  @param vData, pointer to data vector
         *  @return none, (void)
         */
        void node::setNodeContent(int r, string vName, string vType, int vNumber, void* pvData) {
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = pvData;
            nrows = r;
        }

        /** set the variable data, with a pointer to the data vector
         *  @param r, the number of rows/elements in data vector
         *  @return none (void)
         */
        void node::setVarDataRows(int r) {
            nrows = r;
        }

        /** set the variable data, with a pointer to the data vector
         *  @param pointer to data
         *  @return none (void)
         */
        void node::setVarData(void* pvData) {
            ptrData = pvData;
        }

        /** set the variable Name (nvector<int> year {data[0]};ode meta-datum varName)
         *  @param the variable name (string)
         *  @return none (void)
         */
        void node::setVarName(string vName) {
            varName = vName;
        }

        /** set the variable type (node meta-datum varType)
         *  @param the variable type (string)
         *  @return none (void)
         */
        void node::setVarType(string vType) {
            varType = vType;
        }

        /** set the variable (position)number (node meta-datum varNumber)
         *  @param the variable type (string)
         *  @return none (void)
         */
        void node::setVarNumber(int vNumber) {
            varNumber = vNumber;
        }

        //-------------------------------------------------
        /** display the whole node, meta-data and data
         *  @param none
         *  @return none (void)
         */
		void node::displayNode() {
		    cout << "Variable (Node) Contents" << endl;
		    displayName_Type();
		    cout << "position number: " << varNumber << endl;
		    cout << "number  of data vector items: " << nrows << endl;
		    if (varType == "int") {
                cout <<"All Data in Vector"<<endl;
                vector<int> vData = getNodeIntData(ptrData);
                for (int i = 0; i < vData.size(); ++i) {
                    cout << vData[i]<< ", ";
                }
                cout << endl << endl;
		    }
		    else if (varType == "double") {
                cout <<"All Data in Vector"<<endl;
                vector<double> vData = getNodeDblData(ptrData);
                for (int i = 0; i < vData.size(); ++i) {
                    cout << vData[i]<< ", ";
                }
                cout << endl << endl;
		    }
		    else if (varType == "string") {
                cout <<"All Data in Vector"<<endl;
                vector<string> vData = getNodeStrData(ptrData);
                for (int i = 0; i < vData.size(); ++i) {
                    cout << vData[i]<< ", ";
                }
                cout << endl << endl;
		    }
		    else if (varType == "categoryType") {
                cout <<"All Data in Vector"<<endl;
                vector<int> vData = getNodeCatData(ptrData);
                for (int i = 0; i < vData.size(); ++i) {
                    cout << vData[i]<< ", ";
                }
                cout << endl << endl;
		    }
		    else cout << "Unknown Variable type, Node may be corrupted of not initialized" << endl;
		}

        /** display the variable name and type
         *  @param none
         *  @return none (void)
         */
		void node::displayName_Type() {
		    cout << "Variable Name: " << varName << endl;
          cout << "Variable Type: " << varType << endl;
		}

        /** convert the node data to a string
         *  @param none
         *  @return the node as a continuous string (potentially a string stream
         */
		string node::toString() {
            string strVarName = varName;
            string strVarType = varType;
            string strVarNumber =  to_string(varNumber);
            string strVarData = "";
            int dataElement;

            for(int i = 0; i<nrows; ++i) {
                dataElement = (*(vector<int>*)ptrData)[i];
                strVarData = strVarData+" "+to_string(dataElement);
            }
			string retStr = strVarName+" "+strVarType+" "+strVarNumber+" "+strVarData;
			return retStr;
		}
