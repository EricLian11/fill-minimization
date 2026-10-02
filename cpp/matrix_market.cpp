#include "matrix_market.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <unordered_set>
CoordinateMatrix read_matrix_market(const std::string& path){
    std::ifstream input(path);
    if (!input){
        throw std::runtime_error("Invalid path" + path);
    }
    std::string mm,matrix,coordinate,real,symmetric;
    if (!(input >> mm >> matrix >> coordinate >> real >> symmetric)) {
        throw std::runtime_error("No header");
    }
    if (mm != "%%MatrixMarket") {
        throw std::runtime_error("Not matrix market");
    }
    if (matrix != "matrix") {
        throw std::runtime_error("Not matrix");
    }
    if (coordinate != "coordinate") {
        throw std::runtime_error("Not coordinates");
    }
    if (real != "real") {
        throw std::runtime_error("Not real values");
    }
    if (symmetric != "symmetric") {
        throw std::runtime_error("Matrix is not symmetric");
    }
    //There are sometimes comment lines between the header and the dimension line, skip those with this
    input >> std::ws;
    std::string comment;
    while (input.peek() == '%'){
        std::getline(input,comment);
        input >> std::ws;
    }

    //Dimension line
    int rows,columns,num_entries;
    if (!(input >> rows >> columns >> num_entries)) {
        throw std::runtime_error("Matrix summary missing");
    }
    if (rows < 0 or columns < 0 or rows != columns or num_entries < 0) {
        throw std::runtime_error("Matrix dimensions invalid");
    }

    //All data lines
    int row, column;
    double value;
    std::vector<MatrixEntry> entries(num_entries);
    for (int i = 0; i < num_entries; i++) {
        if (!(input >> row >> column >> value)){
            throw std::runtime_error("Missing row or column or value");
        }
        if (row < 1 or row > rows or column < 1 or column > columns) {
            throw std::runtime_error("Invalid row or column data");
        }
        MatrixEntry entry{row-1,column-1,value};
        entries[i] = entry;
    }

    CoordinateMatrix cm{rows,columns,std::move(entries)};
    return cm;

}

Graph graph_from_matrix(const CoordinateMatrix& cm){
    if (cm.rows != cm.columns or cm.rows < 0 or cm.columns < 0) {
        throw std::runtime_error("Invalid matrix dimensions");
    }

    std::vector<std::unordered_set<int>> adjacency(cm.rows);
    //auto& entry is already const from the argument, but for clarity 
    for (const auto& entry : cm.entries) {
        if (entry.row < 0 or entry.row >= cm.rows or entry.column < 0 or entry.column >= cm.columns) {
            throw std::runtime_error("Invalid matrix data");
        }
        //ignore self.loop and zero weight edges
        if (entry.row == entry.column or entry.value == 0) continue;
        
        adjacency[entry.row].insert(entry.column);
        adjacency[entry.column].insert(entry.row);
    }
    Graph graph(std::move(adjacency));
    return graph;
}