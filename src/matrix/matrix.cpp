#include "matrix.h"
#include <vector>
#include <assert.h>

Matrix::Matrix(std::vector<int> values, int cols, int rows) {
    m_rows = rows;
    m_cols = cols;
    m_values = values;
}

Matrix::Matrix(char * file_path) {
    m_rows = 2;
    m_cols = 2;
    m_values = std::vector<int>{};
}

Matrix::Matrix(int rows, int cols) {
    m_cols = cols;
    m_rows = rows;
    m_values = std::vector<int>(cols*rows);
}

int& Matrix::operator()(int i, int j) {
    assert(i >= 0);
    assert(j >= 0);
    assert(i < m_rows);
    assert(j < m_cols);
    return m_values[i*m_rows + j];
}

std::ostream& operator<<(std::ostream& os, Matrix& matrix) {
    int counter{0};
    for (int value : matrix.m_values) {
        os << value << " ";
        counter++;
        if (counter == matrix.m_cols) {
            os << "\n";
            counter = 0;
        }
    }
    return os;
}
