##UtilCSV

@brief Contains the data structures receiving the imported data from the CSV
 file (or going to be written to a CSV file).
 
### Design Conveptualizations:

This set of classes and methods represents the structures written to and from
for CSV file datasets with the associated activities to maintain and manipulate
the data for these files.

The Utilities, ultimately deliver a C++ vector of string vectors organized such
that the data rows of the CSV have been parsed and stored in vectors of data
for column variables.

Thus to form a datatable the parsed values in a row need to be placed in vectors and then in
the variable columns in a overall caotaining vector, ie. vector<vector<string> >.

Finally, because the data have all been passed as strings, so the necessary changes
in types for the column variable vectors have to be made.

###Class Diagram
This can again be visualized from the class diagrams for the project. 


![Class Diagram](Dataframe_Class.svg)
