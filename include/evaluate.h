#ifndef EVALUATE_H
#define EVALUATE_H
#include "timing.h"
#include <assert.h>
#include <iostream>
#include <vector>

class Eval_res {
public:
  double m_correct;
  double m_took_ms;
  double m_linear_took_ms;
  Eval_res(double correct, double took_ms, double linear_took_ms)
      : m_correct(correct), m_took_ms(took_ms),
        m_linear_took_ms(linear_took_ms){};
  Eval_res() {
    m_correct = 0.0;
    m_took_ms = 0.0;
    m_linear_took_ms = 0.0;
  };
  Eval_res operator+(Eval_res &x);
  Eval_res operator/(int x);
  friend std::ostream &operator<<(std::ostream &os, Eval_res &er);
};

template <typename T1, typename T2>
Eval_res evaluate(T1 ann_function, T2 knn_function) {
  auto annres{Timing<std::vector<int>>::take_time(ann_function)};
  auto knnres{Timing<std::vector<int>>::take_time(knn_function)};
  // double accu{ compare(annres.m_result, knnres.m_result) };
  double sum{0.0};
  assert(annres.m_result.size() == knnres.m_result.size());
  for (int i = 0; i < annres.m_result.size(); i++) {
    for (int j = 0; j < knnres.m_result.size(); j++) {
      if (annres.m_result[i] == knnres.m_result[j]) {
        sum++;
        break;
      }
    }
  }
  return Eval_res(sum / annres.m_result.size(), annres.m_took_ms,
                  knnres.m_took_ms);
}

/*
double compare_res(std::vector<int> x, std::vector<int> y); {
    assert(x.size() == y.size());
    double sum{0};
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == y[i]) {
            sum++;
        }
    }
    return sum / static_cast<double>(x.size());
}
*/
#endif
