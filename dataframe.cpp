/** \file
 *\page
 * Source Files:
 *
 * *Dataframe.cpp*
 *
 * (see also Node.cpp *UtilCSV37.cpp*, *Category.cpp* and *main.cpp*.)
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

#include "dataframe.hpp"
#include "node.hpp"
#include "utilCSV.hpp"

using namespace std;


    dataframe::dataframe() {}

    /** . . . a constructor with the first variable/Node initializes rows and columns to (0,0)*/
    dataframe::dataframe(node varNode) {
        ncols = 0;
        nrows = 0;
        colNames.push_back(varNode.getVarName());
        varsGrp = varNode;
    }

    /** . . . constructor with dataframe name, number of rows and number of columns in table */
    dataframe::dataframe(string s, int r, int c) {
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

    /** create a vector of variable (column) types as response to query of dataframe
     *
     *
     */
     vector<string> dataframe::createTypesVector() {
         //Reads the type of each node
         //constructs a vector<string> from the types of the nodes in the dataframe
         //returns the vector list
     }
    /** create a table of observations from the dataframe listing variable
     *  observation(s) (values) as tuples,
     *  @param none
     *  @return none (void)
     */
    void dataframe::createObsDataframe() {
    }

    /** create a tuple from a specific row of variables elements, an internal
     *  helper function for the dataframe
     * @param nrow  the row to read accross the table
     * @return obsRow a tuple (pointer to) with the data by type from the line
     */
     boost::any dataframe::createObsTuple() {
       auto obs = make_tuple("string", 0);
       return  obs;
    }

    /** get the whole dataframe as a vector of nodes
     *  @param none
     *  @return dataframe, ie. a vector of nodes which is the dataframe itself
     */
    vector<node> dataframe::getDataframe() {
        return df;
    }

    /** get the dataframe name,
     *  @param none
     *  @return a string with the dataframe's name
     */
    string dataframe::getDataFrameName() {
        return dfName;
    }

    /** get observations from a row of the dataframe structure
         *  observation(s) as tuples,
         *  @param the row to fetch
         *  @return pointer to tuple containing variable values in the row
         *
         */
    void* dataframe::getObs(int rowNumber) {                                             // INCOMPLETE function
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
    node dataframe::getNode(string vName, int vNumber) {
        node varsGrp;
        return varsGrp;
    }


    /** get a range of rows, ie. observation(s) as tuples,
         *  @param the rows to fetch
         *  @return a vector<tuple>, the variable values in the rows (as a
         *                         pointer to a vector of tuple)
         */
    vector<string> dataframe::getRangeOfRows(int start, int ending) {
        vector<string> aRange;
        aRange.push_back("");
        return aRange;
    }

    /** get data range or block from one or more variables (columns) of the
     *  dataframe structure,
     *  @param r1, c1, r2, c2 - the rows and columns to fetch         *
     *  @return a pointer to a block of values for the range selected
     */
    void* dataframe::getDataRange(int r1,int c1,int r2, int c2) {
        vector<string> aRange;                                                //??? make an array or matrix of strings ?
        aRange.push_back("");
        return &aRange;
    }

    /** get listing of variable names (column names) of the dataframe.
     *  @param null
     *  @return a vector<string> the variable names as a vector of
     *          strings
     */
    vector<string> dataframe::getVarNames() {
        return colNames;
    }

    vector<string> dataframe::getVarTypes() {
        return varTypes;
    }

    /** add a row of observations to the dataframe structure tuples,
     *  @param obsRow a pointer to the tuple of observations to add
     *  @return none (void)
     */
    void dataframe::addObsRow(void* obsRow) {

    }

    /** add a new Node/variable or (re)set the contents of a Node or variable,
     *  @designnote Consider whether this functionality should be split further
     *        between variable data edit, Node content resets and node add.
     *  @param Node varNode with all the variable meta-data and data,
     *  @param vNumber the position number of the variable. if exists reset, if new add
     *  @return none (void)
     */
    void dataframe::setNode(node varNode, int vNumber) {

    }

    /** convert dataframe to a vector of strings
     *
     *
     */
    void convertDfToVStrings(dataframe df) {
        vector<vector<string> > Vstr;

    }

    /** convert a parsed vector of strings to a dataframe of nodes
     *
     *
     */
    void dataframe::convertParsedVStrtoDf(vector< vector<string> > parsedVVS) {
        dataframe df;

    }

    /** load data from a CSV into the dataframe,
         *  @param csvFName name and path of the file to read and import the data from.
         *  @param header a boolean indicating if the first row of CSV contains column names.
         *  @return none (void)
         */
    void dataframe::loadFromCSV(string csvFName, bool header) {
        // get the raw string data, vector<vector<string> > via UtilsCSV
        string frCSV = csvFName;
        bool head = header;
        int rtoline = 0;
        utilCSV newCSV(frCSV, head, rtoline);
        vector<vector<string> > fetchedCSV;
        fetchedCSV = newCSV.getStrDataStruct();
        // get the vector<string> list if data types to be applied by column
        getVarTypes();
        // convert each column to desired data type vector<type>

        // create Node from vectors<type> for each  column
        node varsGrp;
        // populate columns from Nodes in the generic or blank dataframe
        df.push_back(varsGrp);
        //end
    }

    /** save the dataframe contents (with or without a header line) to a
         *  CSV file,
         *  @param csvFName to save to (defaults to 'datafile').
         *  @param header a boolean to say wther to include column names.
         *  @return none (void)
         */
    void dataframe::saveToCSV(string csvFName) {
        //
    }

    /** display the dataframe as a table or wxGrid structure,
         *  @param none
         *  @return none (void)
         */
    void dataframe::displayDataframe() {
        //
    }

    /** display the node/variable of the dataframe,
         *  @param varName variable to display by name
         *  @param varNumber variable number to display
         *  @return none (void)
         */
    void dataframe::displayNodeData(int position, string varName) {
        // uses node::displayNode function
    }

    /** convert the full dataframe contents to a string stream,
         *  @param none
         *  @return none (void)
         */
    string dataframe::toStringStream() {
        return "";
    }

