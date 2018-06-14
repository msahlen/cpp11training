#include "stdafx.h"

#include <gtest/gtest.h>

#include <string>
#include <utility>

TEST(range_based_for, rewrite_to_cpp11)
{
    std::vector<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = 0;
    
    for(auto i:ints)
    {
       result += i;
    } 
    EXPECT_EQ(55, result);
}


template<class Container, class result_type = typename std::remove_reference_t<decltype(*std::begin(std::declval<Container&>()))>>
result_type sum(const Container &c)
{
    result_type result = 0;
    for(auto i:c)
    {
       result += i;
    } 
    return result;
}

TEST(range_based_for, use_on_generic_containers_also_arrays)
{
    std::vector<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(ints) );

    long longs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(longs));
}

class Range {
public:

    Range(int first, int after_last)
        : first{ first }
        , after_last{ after_last }
    {}

    int first;
    int after_last;
};


TEST(range_based_for, we_can_iterate_over_a_collection)
{
    int result = 0;
    // TODO: extend the Range class so that it acts as a
    // real 'range' and can be used in a range based for loop.
    //
    // HINT: This is a harder problem: you need to provide
    // a free begin(const Range&) and end(const Range&) function
    // that returns an iterator-like object.
#ifdef solving_this
    for (const auto &element : Range{ 1, 11 })
    { 
        result += element;
    }
#endif
    EXPECT_EQ(55, result);
}
