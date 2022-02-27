#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"
#include "random_process.h"
#include "integrator.h"
#include "filter.h"

namespace {

    using namespace std::chrono; 
    using namespace elma;  
    #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

    TEST(PROBLEMONE,GetMethod) {
        Stopwatch w;
        w.start(); 
        SLEEP;
        w.stop(); 
        std::cout << w.get_minutes() << "\n"; 
        std::cout << w.get_seconds() << "\n"; 
        std::cout << w.get_milliseconds() << "\n"; 
        std::cout << w.get_nanoseconds() << "\n"; 
        SLEEP;
        std::cout << w.get_minutes() << "\n"; 
        std::cout << w.get_seconds() << "\n"; 
        std::cout << w.get_milliseconds() << "\n"; 
        std::cout << w.get_nanoseconds() << "\n"; 
        w.start();
        SLEEP;
        w.stop(); 
        std::cout << w.get_minutes() << "\n"; 
        std::cout << w.get_seconds() << "\n"; 
        std::cout << w.get_milliseconds() << "\n"; 
        std::cout << w.get_nanoseconds() << "\n"; 
        w.reset();
        std::cout << w.get_minutes() << "\n"; 
        std::cout << w.get_seconds() << "\n"; 
        std::cout << w.get_milliseconds() << "\n"; 
        std::cout << w.get_nanoseconds() << "\n"; 
    }

    TEST(PROBLEMTWO,TWOPROCESS) {
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
         .schedule(f, 1_ms)
         .add_channel(link)
         .init()
         .run(15_ms);
    }

    TEST(PROBLEMTHREE,INTEGRATOR) {
        elma::Manager m;

        RandomProcess r("random numbers");
        Integrator i("integrator");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
         .schedule(i, 1_ms)
         .add_channel(link)
         .init()
         .run(15_ms);
    }

}