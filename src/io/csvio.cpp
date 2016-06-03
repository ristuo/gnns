#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include "csvio.h"
#include "matrix.h"
#include <sstream>
#include <vector>

Matrix read_csv(const char * file_path) {
    int cols = count_cols(file_path);    
    int rows = count_lines(file_path);
    auto values = read_values(file_path, rows, cols); 
    return Matrix(values, rows, cols);
}

std::vector<std::vector<double>> read_values_csv(const char * file_path) {
    int cols = count_cols(file_path);
    int rows = count_lines(file_path);
    std::ifstream filestream{file_path}; 
    if (!filestream) {
        std::cerr << "Opening file failed!" << std::endl;
        exit(1);
    }

    std::vector<std::vector<double>> res; 
    res.reserve(rows);
    while (filestream) {
        std::vector<double> vec;
        vec.reserve(cols);

        std::string in_line; 
        getline(filestream, in_line);

        std::stringstream stringstream{in_line};
        while (stringstream) {
            std::string in_val;
            getline(stringstream, in_val,',');
            try {
                vec.push_back(std::stod(in_val));
            } catch (std::invalid_argument) {
            }
        }
        res.push_back(vec);
    }
    return res;
}

std::vector<int> read_values(const char * file_path, int rows, int cols) {
    std::ifstream filestream{file_path}; 
    if (!filestream) {
        std::cerr << "Opening file failed!" << std::endl;
        exit(1);
    }
    std::string instring; 
    std::vector<int> res; 
    res.reserve(cols*rows);
    while (filestream) {
        getline(filestream, instring);
        for (char character : instring) {
            if (character != ',') {
                res.push_back(static_cast<int>(character) - '0');
            }
        }
    }
    return res;
}

int count_lines(const char * file_path) {
    std::ifstream filestream{file_path}; 
    if (!filestream) {
        std::cerr << "Opening file failed!" << std::endl;
        exit(1);
    }
    std::string instring; 
    int line_counter = 0;
    while (filestream) {
        getline(filestream, instring);
        line_counter++;
    }
    return line_counter-1;
}

int count_cols(const char * file_path) {
    std::ifstream filestream{file_path}; 
    if (!filestream) {
        std::cerr << "Opening file failed!" << std::endl;
        exit(1);
    }
    std::string instring; 
    getline(filestream, instring);
    int counter = 0;
    for (char character : instring) {
        if (character == ',') {
            counter++;
        }
    }
    return counter+1;
}
