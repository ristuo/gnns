#ifndef CSVIO_H
#define CSVIO_H
#include "matrix.h"
#include <vector>
Matrix read_csv(const char * file_path);
std::vector<int> read_values(const char * file_path, int cols, int rows);
int count_lines(const char * file_path);
int count_cols(const char * file_path);
std::vector<std::vector<double>> read_values_csv(const char * file_path);
#endif
