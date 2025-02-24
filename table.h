// table.h
#include <iostream>
using namespace std;
/**
 * Header file for table.cpp
 * 
 * @author Vanessa Brouse
 */

template <typename T>
class Table
{
    template <typename S>
    //friend overloaded << operator
    friend ostream &operator<<(ostream&, const Table<S>&);

    public:
    //overloaded operators
    T &operator()(int, int);
    Table<T> operator+(T (*f)(T)) const;
    Table<T> operator()(int, int, int, int) const;
    Table<T> operator+(T (*f)(T)) const;
    Table<T> append_rows(const Table<T> &);
    Table<T> append_cols(const Table<T> &);

    private:
    int rows_;
    int cols_;
    vector<vector<T>> data_;

    int get_rows() const;
    int get_cols() const;

};
#endif


