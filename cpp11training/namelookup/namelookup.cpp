// namelookup.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

template<typename T>
auto dump(const T &what, const char* context = "") {
    std::cout << context << ": " << what << "\n";
}

namespace outer {

    auto a = "outer::a";
    namespace inner {

        void before_declaration() { dump(a, "free before"); }
        auto a = "inner::a";

        void after_declaration() { dump(a, "free after"); 
            dump(a, "function body, before");
            auto a = "inner::after_declaration()::a";
            dump(a, "function body, after");
            {
                int a = 300;
            }
        }

        void dump() { before_declaration(); after_declaration(); }
    }
    int b = 0;
    void dump() {
        inner::dump();
    }
}
void dump()
{
    outer::dump();
}

template<typename T>
void generic_algorithm(T &value)
{
    reset(value);
}

namespace my_namespace {
    struct X {};
    void reset(X &) {
        dump("X::reset(x)");
    }
}

template<typename T>
void reset(T &) {
    dump("::reset(T)");
}

int main()
{
    dump();

    my_namespace::X x;
    generic_algorithm(x);
    return 0;
}

