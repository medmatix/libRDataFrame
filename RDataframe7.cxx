/** \file
 * \mainpage R-Dataframe
 * \section Program Information and Credits
 *
 * Source Files:
 *
 * *RDataframe7.cxx*
 *
 * (see also *UtilCSV37.cpp*, *Category.cpp* and *main.cpp*.)
 *
 * ##An R-type dataframe data-structure class for C++
 *
 * @author David York
 * @date Saturday August 13, 2016
 * @version 0.7035
 *
 * @brief This creates a datatype "dataframe" modeled on the R language datatype.
 * Initial memory order is simulated or forced column major.
 *
 *
 * *License:*
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * &copy; 2016 David York
 */


#include <cxxabi.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <array>
#include <initializer_list>
#include <boost/any.hpp>
#include <Category.cpp>
#include <UtilCSV37.cpp>
using namespace std;

/**
 *  Node Class to contain a variable, it's meta-data and it's data,
 *  (or rather a pointer to a vector containing the data.
 *
 *  In an Abstract sense, the Nodes are the variables, as contained for example
 *  in a vector of Nodes which is the Dataframe structure.
 *  The meta-data defines the variable fully and a void* pointer to a vector<any>
 *  containing the observation data of the variable.
 *
 *  Class methods allow maintenance and manipulation of the variable it's data
 *  as to variable name, variable (data) type variable id (or position) within
 *  any containing structure and the observation data itself.
 */
class Node {
    //the Node meta-data fields
    protected:
        /** an int holding number of rows in Node data vector (it's length)*/
        int nrows = 0;
        /** the variable name, meta-data, unique to each node */
        string varName = "";
        /** the variable type, meta-data, tracks to type of the data in the vector
         * pointed to */
        string varType = "";
        /** the variable number, meta-data unique to each node, tracks the intended
         * position in the dataframe  */
        int varNumber = 0;
        /** a pointer to the start in memory of the vector for variable data*/
        void* ptrData = nullptr;

        /**Vector to receive integers when known that void* ptrdata holds this*/
        vector<int>* ivData = nullptr;
        /**Vector to receive doubles when known that void* ptrdata holds this*/
        vector<double>* dvData= nullptr;
        /**Vector to receive strings when known that void* ptrdata holds this*/
        vector<string>* svData= nullptr;
        /**Vector to receive factors when known that void* ptrdata holds this*/
        vector<int>* cvData = nullptr;

        /**
         *  Category meta-data as needed for node data of type 'category'
         */

        /**
         *  A map of categorical pairs, the meta-data of the variable storing
         *  the categories. A level number (int) and a level name of title (string)
         */
        map<int, string> categorySet;

        /**
         *  A vector of category levels (numeric only) ie. ints (level names are
         *  obtained as needed  from the map for use in table and plot output.
         */
        vector<int> catVarData;

	public:
	    /** default constructor */
        Node() {
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
        Node(int r, string vName, string vType, int vNumber) {
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
        Node(int r, string vName, string vType, int vNumber, map<int, string>  catSet) {
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
        Node(int r, string vName, string vType, int vNumber, void* pvData) {
            nrows = r;
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = pvData;
        }



        /** the Node class methods */
        //--------------------------------------------------------

        /** get a range of variable data from the node vector
         *  @param start - the starting index for the range of data.
         *  @param the ending index for the range
         *  @return a pointer to the start of memory containing the data range
         */
        void* getVarDataRange(int start, int ending) {
            vector<int> varData;
            vector<int>* ptrVarData = (vector<int>*)ptrData;
            for(int i = 0; i < nrows; ++i){
                //
            }
            return 0;
        }

        /** get all of the variable data from the node vector as a raw data
         * requires variable type to fetch pointer
         *  @param none
         *  @return a pointer to the start of memory containing the data vector
         */
        void* getVarData() {
            return ptrData;
        }

        /** get the variable name (node meta-datum varName)
         *  @param none
         *  @return the variable name (string)
         */
        string getVarName() {
            return varName;
        }

        /** get the variable type (node meta-datum varType)
         *  @param none
         *  @return the variable type (string)
         */
        string getVarType() {
            return varType;
        }

        /** get the variable (position) number (node meta-datum varNumber)
         *  @param none
         *  @return the variable number (int)
         */
        int getVarNumber() {
            return varNumber;
        }

        /** get nrows, the number of data rows in the Node vector
         *  @param none
         *  @return nrows, an int with the number of data rows in vector
         */
        int getNRows() {
            return nrows;
        }

        /** get Node data as a vector of integers
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<int> with the Node data
         */
        vector<int> getNodeIntData (void* pData) {
             ivData = (vector<int>*) ptrData;
             return *ivData;
        }

        /** get Node data as a vector of doubles
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<double> with the Node data
         */
        vector<double> getNodeDblData (void* pData) {
            dvData = (vector<double>*) ptrData;
            return *dvData;
         }

         /** get Node data as a vector of strings
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<string> with the Node data
         */
         vector<string> getNodeStrData (void* pData) {
             svData = (vector<string>*) ptrData;
             return *svData;
         }

         /** get Node data as a vector of categories or factors
         *  @param pData a pointer to the Node data
         *  @return ivData the pointer to a vector<int> with the Node data
         */
         vector<int> getNodeCatData (void* pData) {
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
        void setNodeContent(int r, string vName, string vType, int vNumber, void* pvData) {
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
        void setVarDataRows(int r) {
            nrows = r;
        }

        /** set the variable data, with a pointer to the data vector
         *  @param pointer to data
         *  @return none (void)
         */
        void setVarData(void* pvData) {
            ptrData = pvData;
        }

        /** set the variable Name (nvector<int> year {data[0]};ode meta-datum varName)
         *  @param the variable name (string)
         *  @return none (void)
         */
        void setVarName(string vName) {
            varName = vName;
        }

        /** set the variable type (node meta-datum varType)
         *  @param the variable type (string)
         *  @return none (void)
         */
        void setVarType(string vType) {
            varType = vType;
        }

        /** set the variable (position)number (node meta-datum varNumber)
         *  @param the variable type (string)
         *  @return none (void)
         */
        void setVarNumber(int vNumber) {
            varNumber = vNumber;
        }

        //-------------------------------------------------
        /** display the whole node, meta-data and data
         *  @param none
         *  @return none (void)
         */
		void displayNode() {
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
		void displayName_Type() {
		    cout << "Variable Name: " << varName << endl;
          cout << "Variable Type: " << varType << endl;
		}

        /** convert the node data to a string
         *  @param none
         *  @return the node as a continuous string (potentially a string stream
         */
		string toString() {
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
};

/**
 *  The Dataframe class is an R-like data structure serving as a container for a
 *  dataset to be used in data analysis procedures.
 *
 *  It consists of fields in support of a set of variables contained in Node
 *  structures as a vector<Node>.
 *  The Node class is defined as an external dependency of the dataframe. It
 *  should be thought of as a table like structure with the columns containing
 *  the variable "Nodes" and the rows containing the observation sets of
 *  related variables.
 *
 *  Class methods maintain and manipulate the dataframe and it's observations
 *  and variable.
 */
class Dataframe {
/** the Dataframe meta-data fields and contained variable nodes*/
protected:
    int nrows;
    int ncols;
    string dfName;
    vector<Node> dataframe;
    Node variable;
    vector<string> colNames;
    vector<string> varTypes;
    void* obsDataFrame = nullptr;
    vector<string> obsRowNames;

/** Constructors to create the dataframe made up of Nodes,
 *  . . .  */
public:
    /** the default constructor */
    Dataframe() {
        nrows = 0;
        ncols = 0;
        colNames.push_back("");
        Node variable;
    }

    /** . . . a constructor with the first variable/Node initializes rows and columns to (0,0)*/
    Dataframe(Node varNode) {
        ncols = 0;
        nrows = 0;
        colNames.push_back(varNode.getVarName());
        variable = varNode;        }

    /** . . . constructor with dataframe name, number of rows and number of columns in table */
    Dataframe(string s, int r, int c) {
        dfName = s;
        nrows = r;
        ncols = c;
    }

    /** Dataframe class methods
     *  helper methods (internal/protected)
     *  converters public may be used internally and externally
     *  getters - public
     *  setters - public
     *  utility methods public (usually used externally)
     *  displayers - public
     */

protected:
    /** create a vector of variable (column) types as response to query of dataframe
     *
     *
     */
     vector<string> createTypesVector() {
         //Reads the type of each node
         //constructs a vector<string> from the types of the nodes in the dataframe
         //returns the vector list
     }
    /** create a table of observations from the dataframe listing variable
     *  observation(s) (values) as tuples,
     *  @param none
     *  @return none (void)
     */
    void createObsDataframe() {
    }

    /** create a tuple from a specific row of variables elements, an internal
     *  helper function for the dataframe
     * @param nrow  the row to read accross the table
     * @return obsRow a tuple (pointer to) with the data by type from the line
     */
     boost::any createObsTuple() {
       auto obs = make_tuple("string", 0);
       return  obs;
    }

public:
    /** get the whole dataframe as a vector of nodes
     *  @param none
     *  @return dataframe, ie. a vector of nodes which is the dataframe itself
     */
    vector<Node> getDataframe() {
        return dataframe;
    }

    /** get the dataframe name,
     *  @param none
     *  @return a string with the dataframe's name
     */
    string getDataFrameName() {
        return dfName;
    }

    /** get observations from a row of the dataframe structure
         *  observation(s) as tuples,
         *  @param the row to fetch
         *  @return pointer to tuple containing variable values in the row
         *
         */
    void* getObs(int rowNumber) {                                             // INCOMPLETE function
        string dummyReturn = "";
        //get obs one at a time across row and then pass ALL to make_tuple
        auto obsRow = make_tuple(rowNumber, dummyReturn);
        return &obsRow;
    }
    /** get a variable with meta-data and the dataset stored in it.
         *  This is a node.
         *  @param vName the node or variable name to fetch, default NULL or
         *  @param vNumber the node or variable number to fetch default 0
         *  @return the variable node
         */
    Node getNode(string vName= "", int vNumber = 0) {
        Node variable;
        return variable;
    }


    /** get a range of rows, ie. observation(s) as tuples,
         *  @param the rows to fetch
         *  @return a vector<tuple>, the variable values in the rows (as a
         *                         pointer to a vector of tuple)
         */
    vector<string> getRangeOfRows(int start, int ending) {
        vector<string> aRange;
        aRange.push_back("");
        return aRange;
    }

    /** get data range or block from one or more variables (columns) of the
     *  dataframe structure,
     *  @param r1, c1, r2, c2 - the rows and columns to fetch         *
     *  @return a pointer to a block of values for the range selected
     */
    void* getDataRange(int r1,int c1,int r2, int c2) {
        vector<string> aRange;                                                //??? make an array or matrix of strings ?
        aRange.push_back("");
        return &aRange;
    }

    /** get listing of variable names (column names) of the dataframe.
     *  @param null
     *  @return a vector<string> the variable names as a vector of
     *          strings
     */
    vector<string> getVarNames() {
        return colNames;
    }

    vector<string> getVarTypes() {
        return varTypes;
    }

    /** add a row of observations to the dataframe structure tuples,
     *  @param obsRow a pointer to the tuple of observations to add
     *  @return none (void)
     */
    void addObsRow(void* obsRow) {

    }

    /** add a new Node/variable or (re)set the contents of a Node or variable,
     *  @designnote Consider whether this functionality should be split further
     *        between variable data edit, Node content resets and node add.
     *  @param Node varNode with all the variable meta-data and data,
     *  @param vNumber the position number of the variable. if exists reset, if new add
     *  @return none (void)
     */
    void setNode(Node varNode, int vNumber) {

    }

    /** convert dataframe to a vector of strings
     *
     *
     */
    void convertDfToVStrings(Dataframe df) {
        vector<vector<string> > Vstr;
    }

    /** convert a parsed vector of strings to a dataframe of nodes
     *
     *
     */
    void convertParsedVStrtoDf(vector< vector<string> > parsedVVS) {
        Dataframe df;
    }

    /** load data from a CSV into the dataframe,
         *  @param csvFName name and path of the file to read and import the data from.
         *  @param header a boolean indicating if the first row of CSV contains column names.
         *  @return none (void)
         */
    void loadFromCSV(string csvFName, bool header) {
        // get the raw string data, vector<vector<string> > via UtilsCSV
        string frCSV = csvFName;
        bool head = header;
        int rtoline = 0;
        UtilCSV newCSV(frCSV, head, rtoline);
        vector<vector<string> > fetchedCSV;
        fetchedCSV = newCSV.getDataStruct();
        // get the vector<string> list if data types to be applied by column
        getVarTypes();
        // convert each column to desired data type vector<type>

        // create Node from vectors<type> for each  column
        Node variable;
        // populate columns from Nodes in the generic or blank dataframe
        dataframe.push_back(variable);
        //end
    }

    /** save the dataframe contents (with or without a header line) to a
         *  CSV file,
         *  @param csvFName to save to (defaults to 'datafile').
         *  @param header a boolean to say wther to include column names.
         *  @return none (void)
         */
    void saveToCSV(string csvFName) {
        //
    }

    /** display the dataframe as a table or wxGrid structure,
         *  @param none
         *  @return none (void)
         */
    void displayDataframe() {
        //
    }

    /** display the node/variable of the dataframe,
         *  @param varName variable to display by name
         *  @param varNumber variable number to display
         *  @return none (void)
         */
    void displayNodeData(int position=0, string varName="") {
        // uses Node::displayNode function
    }

    /** convert the full dataframe contents to a string stream,
         *  @param none
         *  @return none (void)
         */
    string toStringStream() {
        return "";
    }
};


/** See unit test code for RDataframe7 in main() module */
// boost::any_cast<int>
