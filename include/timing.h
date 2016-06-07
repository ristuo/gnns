#ifndef TIMING_H
#define TIMING_H
#include <functional>
#include <chrono>
#include <iostream>

template <typename T1>
class Timing {
    public:
        T1 m_result;
        double m_took_ms;
        Timing(double took_ms, T1 result): m_took_ms(took_ms), m_result(result) {};
        template <typename T2>
        static Timing take_time(T2 function) {
            using namespace std::chrono;
            auto start{ high_resolution_clock::now().time_since_epoch() };
            auto res{ function() };
            auto end{ high_resolution_clock::now().time_since_epoch() };
            double took_ms{ duration_cast<microseconds>(end - start).count() / 1000.0 };
            return Timing(took_ms, res);
        }

        friend std::ostream& operator<<(std::ostream &os, Timing<T1> &timinki) {
            os << "took_ms: " << timinki.m_took_ms;
            return os;
        }
};
#endif
