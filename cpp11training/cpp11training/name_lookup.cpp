#include <gtest/gtest.h>

namespace outer {
    int a;
    namespace inner {
        void foo() { a = 5; }
        int a;
        int b;
        void bar() { a = 5; }
    }
    int b;
}