#include "linalg.h"
#include <iostream>
#include <vector>
#include <assert.h>

typedef std::vector<double> dvec;
double sqdist(const dvec &x, const dvec &y) {
    assert(x.size() == y.size());
    double sum{0.0};
    for (int i = 0; i < x.size(); i++) {
        double difference{(x[i] - y[i])};
        sum += difference * difference;
    }
    return sum;
}

double sqdista(double *x, double *y, int size) {
    double sum{0.0};
    for (int i = 0; i < size; i++) {
        double difference{(x[i] - y[i])};
        sum += difference * difference;
    }
    return sum;
}
