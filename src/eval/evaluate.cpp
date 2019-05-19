#include "evaluate.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, Eval_res &er) {
  os << er.m_correct << " " << er.m_took_ms << " " << er.m_linear_took_ms;
  return os;
}

Eval_res Eval_res::operator+(Eval_res &x) {
  return Eval_res(m_correct + x.m_correct, m_took_ms + x.m_took_ms,
                  m_linear_took_ms + x.m_linear_took_ms);
}

Eval_res Eval_res::operator/(int x) {
  return Eval_res(m_correct / x, m_took_ms / x, m_linear_took_ms / x);
}
