#include <iostream>
#include "graph.h"
#include "node.h"
#include "matrix.h"
#include "csvio.h"
#include <vector>
#include "knn.h"
#include <ctime>
#include "heap.h"
#include "arrayutil.h"
#include <functional>
#include <timing.h>
#include "evaluate.h"
#include "linalg.h"
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include <cmath>

int we(std::vector<int> &x) {
    sort(x);
    return 1;
}

int main(int argc, char ** argv) {

    std::vector<int> iterations{1, 2, 5, 10, 20 };
    std::vector<int> e_params{ 2, 5, 10, 20, 30, 50, 100 };
    std::vector<int> steps{ 2, 5, 10, 100 };
    std::vector<int> randomi(17000);
    for (int i = 0; i < 17000; i++) {
        randomi[i] = rand();
    }
    auto testi1{ Timing<int>::take_time(std::bind(we, randomi)) };
    std::cout << testi1.m_took_ms << std::endl;

    auto data{ read_values_csv("../data/sift17k.csv") };
    data.resize( data.size() -1 );
    auto testset = read_values_csv("../data/sift100k_test.csv");
    testset.resize( testset.size() - 1 );
    auto graafi{ create_graph(200, data) };
    for (int step : steps) {
        for (int iteration : iterations) {
            for (int e_param : e_params) {
                Eval_res xyz{};    
                for (std::vector<double> query_point : testset) {
                    auto result3 { evaluate(  std::bind(knn, 30, query_point, graafi, iteration, e_param, step), std::bind(linear_search, 30, query_point, data) ) };
                    xyz = xyz + result3;
                }
                auto mean{ xyz/testset.size() };
                auto speedup{mean.m_linear_took_ms / mean.m_took_ms};
                bool col{mean.m_correct > 0.9};
                if (col) {
                    std::cout << "\033[1;32m";
                } else if (mean.m_correct > 0.7) {
                    std::cout << "\033[1;33m";
                }
                std::cout << round(speedup*10)/10.0 << " " << static_cast<int>(mean.m_correct*100) << "% R: " << iteration << ", E: " << e_param << ", T" << step << " " << mean << std::endl;
                if (mean.m_correct > 0.7) {
                    std::cout << "\033[0m";
                }
            }
        }
    }
    return 0;
}
