#pragma once
#include <vector>
#include <string>
//holds (row,column,value) from matrix market data file
struct MatrixEntry {
    int row;
    int column;
    double value;
};

//holds number of rows, number of columns, and vector of matrix entries
struct CoordinateMatrix {
    int rows;
    int columns;
    std::vector<MatrixEntry> entries;
};

//reads the matrix market data file, returns a coordinate matrix
CoordinateMatrix read_matrix_market(const std::string& path);