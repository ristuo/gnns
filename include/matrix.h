#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>

class Matrix {
    private: 
        std::vector<int> m_values;
        int m_rows;
        int m_cols;
    public:
        Matrix(std::vector<int> values = {1,1,0,0}, int rows = 2, int cols = 2);
        Matrix(char * file_path);
        Matrix(int rows, int cols);
        int& operator()(int i, int j);
        int get_m_cols() {return m_cols;};
        int get_m_rows() {return m_rows;};
        friend std::ostream& operator<<(std::ostream& os, Matrix& matrix);
};
#endif

