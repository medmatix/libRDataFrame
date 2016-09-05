/** \file
 * \page "Factor / Category"
 * \section "category data type"
 *
 * Source File:
 * *category.cpp*
 *
 * ## A Categorical or "Factor" data type class for C++
 *
 * @author David York
 * @date Friday August 26, 2016
 * @version 0.7019
 *
 * @description *Description*
 * Creates and provides utilities for a categorical or factor
 * datatype (similar to R's factor type). The utilies allow construction, and
 * population of data type based a vector of factors. There are also functions
 * included to convert factor variables to and from int and string variable
 * collections.
 *
 * The best model to use was considered to be the open source R factor type.
 * In Addition to constructors, utilities to manipulate this variable type are needed.
 * ![UML](../doc/Dataframe_Class.svg) *
 *
 *
 * \subsection License
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

#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <initializer_list>
#include <boost/any.hpp>

using namespace std;


/**\section "Global Declarations"
 * global variables and functions for global access to certain utilities
 * including retyping other types as factors, particularly as obtained from
 * text data file sources for datasets. */




/** Class for a category (factor) container data type consisting of the category
 * name (a string) and an integer ranking, collected into a vector of these
* pairs each an observation from a set */
class category{
    protected:
    /** structure for each data point observed as a factory of categorical type */
    struct categoryLevel {     //? change to multi-pair<int, string> types?
    	/** name of data level point */
    	string levelName;
        /** ranks for that point */
    	int levelRank;
    };

    /** variable for this category variable (also represented by the object
     * name it was created with */
    string catVarName = "";

    /** */
    categoryLevel aFactor;

    /** vector of observations as categorical pairs, level mane and level rank */
    vector<categoryLevel> categorySet;   // change to a vector of multi-pairs?


    public:
    /** Constructors */

    /** construct with name of variable only */
	 category(string vName) {
        catVarName = vName;
        aFactor.levelName = "";
        aFactor.levelRank = 0;
        categorySet.push_back(aFactor);

    }

    /** constructor with every thing except data */
    category(string vName, int lRank, string lName = "") {
        catVarName = vName;
        categoryLevel afactor;
        afactor.levelName = lName;
        afactor.levelRank = lRank;
        categorySet.push_back(afactor);
   }

    /**constructor with metadata and passed a pointer to generic data
     * this data will need to be parsed and sorted the data then group into
     * categories
     */
    category(string vName, int lRank, void* ptrData, string lName = ""){
        catVarName = vName;
        categoryLevel afactor;
        afactor.levelName =lName;
        afactor.levelRank = lRank;
        categorySet.push_back(afactor);
    }
    /**constructor with metadata and passed a fully organized vector of pairs
     * this is already pre-parsed and sorted into categories usually from the data
     * source file*/
    category(string vName, int lRank, vector<categoryLevel>* ptrData, string lName = ""){
        catVarName = vName;
        categoryLevel afactor;
        afactor.levelName =lName;
        afactor.levelRank = lRank;
        categorySet.push_back(afactor);
    }

    /** member functions - class methods */

	 /** set category levels in vector<categoryLevels>
	  *  @param levelStrList a string vector
	  *  @param levelIntList an integer vector
	  *  @return void
     */
	 void setAllLevels(vector<string> levelStrList, vector<int> levelIntList) {}


};

/** See ant unit test code for the Category Data Type Class in main() module */
