## libRDataFrame
A library, containing the consolidated collection of routines to support R-style Data Structures for C++


### Overview and Statement of purpose (goal development)
see [Project page](https://medmatix.github.io/libRDataFrame/)
  
Some omponents of the is project are of use outside of the R data structure use case, such as the utilisty to read and write CSV files in C++. The links to these are included to below.

This project has the goal of developing an R-like dataframe class and other data structures (like an R factor data type (called a category for C++) for similar applications for analysis of data written entirely in C++. 

The necessary building blocks of this dataframe analog are a Variable composite data structure including vector class for the raw data, for the columns of the dataframe, and a vector class to contain the variable objects. Of note, R arrays are column major memory structures, so this is simulates such a structure to provide at least a virtual variable oriented structure.

The R dataframe is, a list derivative with vectors for the columns as elements of the list.As noted below, this is a bit untenable in C++. The base reference to the  elements (rows and columns) is the usual numeric endices. However, associative reference with variable (column) and observation (row) also a feature. This is accomplished with a vector< vector< Node> > > structure.

Being relatively new to C++, this is my first major project in C++. At this point, my breadth and depth of understanding of C++ is growing but is at times an impediment to finding the best way to do things. Each revision provides new experience. Suggestions and comments are welcome.

###Contributors
  - Author: David York (Medmatix)

###Development Notes
#### A Todo List
1. Decide on the on going approachs to a mixed type list.
2. A complete set of getters and setter as will as appropriate to_string methods for each datatype constructed. Include formatted display methods for each structure.
    - Node class completed getters and setters
    - Category class on going development, see individual project
    - UtilCSV completed getters and setters
    - RDataframe class getters and setters in process, basic ones are complete
3. Develop a list of functions member and non-member, to include as dataframe manipulator and analysis  functions.
4. Continued testing ( main() module) of functions and classes as developed.

#### Design directions
Initially a list of vectors was the basic plan in keeping with the R structure. However R lists and C++ STL lists are different enough as to handicape any attempt to mimic R structures in C++. Thus a move tp the data.frame in C++ being a vector of vectors. 

The principal issue is the need to random access the variables (columns) in the data.frame is the C++ implementation. The C++ list is implemented as a sequentially accessed object to allow access for actions on the elements across the list. The random access of individual list members is not implemented in the list structure.

###Unit Testing Notes
Excluding the category data type class, all the relevant getters, setters and display functions are implemented and tested in the Unit Test main() module.


###References and Acknowledgements
See related project, [UtilCSV](http://medmatix.github.io/UtilCSV)
                     [RDataframe7](http://medmatix.github.io/RDataframe)

###Contacts
Author web page, http://crunches-data.appspot.com
Email, medmatix@gmail.com

Copyright 2016 D.A.York
