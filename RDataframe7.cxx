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
 * @version 0.703
 *
 * *Description:*
 *
 * This creates a datatype "dataframe" modeled on the R language datatype.
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
 * \page "Design Notes"
 *  ![UML](./Dataframe_Class.svg)
 */


#include <cxxabi.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <initializer_list>
#include <boost/any.hpp>
#include <Category.cpp>
using namespace std;

/**
 * Node Class to contain a variable, it's meta-data and it's data,
 *  (or rather a pointer to a vector containing the data
 */
class Node {
    //the Node meta-data fields
    protected:
        /** an int holding number of rows in Node data vector (it's length)*/
        int nrows;
        /** the variable name, meta-data, unique to each node */
        string varName;
        /** the variable type, meta-data, tracks to type of the data in the vector
         * pointed to */
        string varType;
        /** the variable number, meta-data unique to each node, tracks the intended
         * position in the dataframe  */
        int varNumber;
        /** a pointer to the start in memory of the vector for variable data*/
        void* ptrData;

        /**Vector to receive integers when known that void* ptrdata holds this*/
        vector<int>* ivData = nullptr;
        /**Vector to receive doubles when known that void* ptrdata holds this*/
        vector<double>* dvData= nullptr;
        /**Vector to receive strings when known that void* ptrdata holds this*/
        vector<string>* svData= nullptr;
        /**Vector to receive factors when known that void* ptrdata holds this*/
        vector<category>* cvData = nullptr;


	public:
	    /** default constructor */
        Node() {
            varName = "";
            varType = "";
            varNumber = 0;

        }

        /** constructor all meta data for variable and data as pointer to a vector */
        Node(int r, string vName, string vType, int vNumber, void* pVData) {
            varName = vName;
            varType = vType;
            varNumber = vNumber;
            ptrData = pVData;
            nrows = r;
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

        /** get a all of the variable data from the node vector
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
         vector<category> getNodeCatData (void* pData) {
             cvData = (vector<category>*) ptrData;
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
        void setVarData(void* vData) {
            ptrData = vData;
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
		    cout << "name: " << varName << endl;
		    cout << "type: " << varType << endl;
		    cout << "position number: " << varNumber << endl;
		    cout << "number  of data vector items: " << nrows << endl;
		    cout << "data address: " << ptrData << endl;
		    cout << "first data point value: " << (*(vector<int>*)ptrData)[0] << endl;

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
 * The Dataframe class to present the R like structure to use in data analysis
 */
class Dataframe {
/** the Dataframe meta-data fields */
protected:
    int nrows;
    int ncols;
    string dfName;
    vector<Node> dataframe;
    Node variable;
    vector<string> colNames;
    void* obsDataFrame = nullptr;
    vector<string> obsRowNames;

public:
        /** the default constructor */
        Dataframe() {
            nrows = 0;
            ncols = 0;
            colNames.push_back("");
            Node variable;
        }

        /** a constructor with the first variable/Node initializes rows and columns to (0,0)*/
        Dataframe(Node varNode) {
            ncols = 0;
            nrows = 0;
            colNames.push_back(varNode.getVarName());
            variable = varNode;
        }

        /** constructor with dataframe name, number of rows and number of columns in table */
        Dataframe(string s, int r, int c) {
            dfName = s;
            nrows = r;
            ncols = c;
        }


        /** Dataframe class methods     */

        /** get the dataframe name,
         *  @param none
         *  @return a string with the dataframe's name
         */
        string getDataFrameName() {
            return dfName;
        }

        /** create a table of observations from the dataframe listing variable
         *  observation(s) (values) as tuples,
         *  @param none
         *  @return none (void)
         */
        void createObsDataframe() {
        }

        /** get the whole dataframe as a vector of nodes
         *  @param none
         *  @return dataframe, ie. a vector of nodes which is the dataframe itself
         */
        vector<Node> getDataframe() {
            return dataframe;
        }

        /** get observations from a row of the dataframe structure
         *  observation(s) as tuples,
         *  @param the row to fetch
         *  @return a pointer to the tuple containing variable values in the
         *          row
         */
        void* getObs(int rowNumber) {
            string dummyReturn = "";
            //get obs one at a time across row and then pass ALL to make_tuple
            auto obsRow = make_tuple(rowNumber, dummyReturn);
            return &obsRow;
        }

        /** get a range of rows, ie. observation(s) as tuples,
         *  @param the rows to fetch
         *  @return a vector<tuple>, the variable values in the rows (as a
         *                         pointer to a vector of tuple)
         */
        vector<string> getRangeRows() {
            vector<string> aRange;
            aRange.push_back("");
            return aRange;
        }

        /** get listing of variable names (column names) of the dataframe.
         *  @param null
         *  @return a vector<string> the variable names as a vector of
         *          strings
         */
        vector<string> getVarNames() {
            return colNames;
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

        /** get data range or block from one or more variables (columns) of the
         *  dataframe structure,
         *  @param r1, c1, r2, c2 - the rows and columns to fetch         *
         *  @return a pointer to a block of values for the range selected
         */
        void* getDataRange(int r1,int c1,int r2, int c2) {
            vector<string> aRange;
            aRange.push_back("");
            return &aRange;
        }

        /** add a row of observations to the dataframe structure tuples,
         *  @param obsRow a pointer to the tuple of observations to add
         *  @return none (void)
         */
        void addObsTuple(void* obsRow) {
        }

        /** add a new Node/variable or (re)set the contents of a Node or variable,
         *  @designnote Consider whether this functionality should be split further
         *        between variable data edit, Node content resets and node add.
         *  @param Node varNode with all the variable meta-data and data,
         *  @param vNumber the position number of the variable. if exists reset, if new add
         *  @return none (void)
         */
        void setNodeData(Node varNode, int vNumber) {
        }

        /** load data from a CSV into the dataframe,
         *  @param csvFName name and path of the file to read and import the data from.
         *  @param header a boolean indicating if the first row of CSV contains column names.
         *  @return none (void)
         */
        void loadFromCSV(string csvFName, bool header) {
        }

        /** save the dataframe contents (with or without a header line) to a
         *  CSV file,
         *  @param csvFName to save to (defaults to 'datafile').
         *  @param header a boolean to say wther to include column names.
         *  @return none (void)
         */
        void saveToCSV(string csvFName) {
        }

        /** display the dataframe as a table or wxGrid structure,
         *  @param none
         *  @return none (void)
         */
        void displayDataframe() {
        }

        /** display the node/variable of the dataframe,
         *  @param varName variable to display by name
         *  @param varNumber variable number to display
         *  @return none (void)
         */
        void displayNodeData() {
        }

        /** convert the full dataframe contents to a string stream,
         *  @param none
         *  @return none (void)
         */
        string toStringStream() {
            return "";
        }
};

/** See unit test code for UtilCSV in main() module */
// boost::any_cast<int>
