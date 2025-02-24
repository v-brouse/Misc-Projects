#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;
/**
 * Table class for table_tester and table_tester2
 *
 * @author Vanessa Brouse
 */

template <typename T>
class Table
{

public:
    //creates table with rows and cols according to teset program
    Table(int rows, int cols) : rows_(rows), cols_(cols)
    {
        data_.resize(rows, vector<T>(cols));
    }

    /**
     * Overloaded << operator 
     * outputs the table in a table-like structure 
     * 
     */
    friend ostream &operator<<(ostream &out, const Table<T> &t)
    {
        // gets width of out
        int width = out.width();

        for (const auto &row : t.data_)
        {
            for (const T &cell : row)
            {
                out << setw(width) << cell << "\t";
            }
            out << "\n";
        }
        return out;
    }

    /**
     * Overloaded () operator for 2 argument tables
     * 
     */
    T &operator()(int row, int col = 0)
    {
        return data_[row][col];
    }

    // Overloaded () operator for the subtables
    Table<T> operator()(int start_row, int start_col, int end_row, int end_col) const
    {
        if (start_row < 0 || start_col < 0 || end_row > rows_ || end_col > cols_ ||
            start_row >= end_row || start_col >= end_col)
        {
            cerr << "Error: Invalid subtable dimensions." << endl;
            return Table<T>(0, 0);
        }
        // creates how many rows cols there should be
        int sub_rows = end_row - start_row + 1;
        int sub_cols = end_col - start_col + 1;
        Table<T> subtable(sub_rows, sub_cols);

        for (int i = 0; i < sub_rows; i++)
        {
            for (int j = 0; j < sub_cols; j++)
            {
                subtable(i, j) = data_[start_row + i][start_col + j];
            }
        }

        return subtable;
    }

    /**
     * Addition operator, overloaded as a function template.
     * The type is read as pointer-to-function-that-take-a-T-value-and-returns-
     * a-T-value.
     */
    Table<T> operator+(T (*f)(T)) const
    {
        Table<T> result(rows_, cols_);
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < cols_; ++j)
            {
                result(i, j) = f(data_[i][j]);
            }
        }
        return result;
    }

    /**
     * Does not modify the object this is called on. 
     * Returns a new table obtained by concatenating the two operands
     * 
     */
    Table<T> append_rows(const Table<T> &r)
    {
        if (r.cols_ != cols_)
        {
            cout << "Error: Incompatible number of columns for row append." << endl;
            return *this;
        }

        int new_rows = rows_ + r.rows_;
        Table<T> result(new_rows, cols_);

        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                result(i, j) = data_[i][j];
            }
        }

        for (int i = 0; i < r.rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                result(rows_ + i, j) = r(i, j);
            }
        }

        return result;
    }

     /**
     * Does not modify the object this is called on. 
     * Returns a new table obtained by concatenating the two operands.
     * 
     */
    Table<T> append_cols(const Table<T> &c)
    {
        if (c.rows_ != rows_)
        {
            cout << "Error: Incompatible number of rows for column append." << endl;
            return *this;
        }

        int new_cols = cols_ + c.cols_;
        Table<T> result(rows_, new_cols);

        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                result(i, j) = data_[i][j];
            }

            for (int j = 0; j < c.cols_; j++)
            {
                result(i, cols_ + j) = c(i, j);
            }
        }

        return result;
    }

    /**
     * Get the cols object
     * 
     * @return int
     */
    int get_cols() const
    {
        return cols_;
    }

    /**
     * Get the rows object
     * 
     * @return int 
     */
    int get_rows() const
    {
        return rows_;
    }
};