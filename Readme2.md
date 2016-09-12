
## Design Notes

Initially a list of vectors was the basic plan in keeping with the R
structure. However R lists and C++ STL lists are different enough as to
handicape any attempt to mimic R structures in C++. Thus a move tp the
data.frame in C++ being a vector of vectors.

The principal issue is the need to random access the variables (columns) in
the data.frame is the C++ implementation. The C++ list is implemented as a
sequentially accessed object to allow access for actions on the elements
across the list. The random access of individual list members is not
implemented in the list structure.

![UML](Dataframe_Class.svg)

