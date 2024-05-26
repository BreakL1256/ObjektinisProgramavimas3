#define CATCH_CONFIG_MAIN  
#include "catch2/catch.hpp"
#include "Vector.h"

using namespace std;

// Test constructors
TEST_CASE("Vector constructors") {
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() >= 1);

    Vector<int> v2(10);
    REQUIRE(v2.size() == 10);
    REQUIRE(v2.capacity() >= 10);

    Vector<int> v3(10, 5);
    REQUIRE(v3.size() == 10);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(v3[i] == 5);
    }

    Vector<int> v4 = {1, 2, 3, 4, 5};
    REQUIRE(v4.size() == 5);
    for (int i = 0; i < 5; ++i) {
        REQUIRE(v4[i] == i + 1);
    }

    Vector<int> v5(v4);
    REQUIRE(v5.size() == v4.size());
    for (int i = 0; i < v4.size(); ++i) {
        REQUIRE(v5[i] == v4[i]);
    }

    Vector<int> v6(std::move(v4));
    REQUIRE(v6.size() == 5);
    REQUIRE(v4.size() == 0);

    Vector<int> v7;
    v7 = v5;
    REQUIRE(v7.size() == v5.size());
    for (int i = 0; i < v5.size(); ++i) {
        REQUIRE(v7[i] == v5[i]);
    }

    Vector<int> v8;
    v8 = std::move(v5);
    REQUIRE(v8.size() == 5);
    REQUIRE(v5.size() == 0);
}

// Test iterators
TEST_CASE("Vector iterators") {
    Vector<int> v = {1, 2, 3, 4, 5};

    REQUIRE(v.begin() != v.end());
    REQUIRE(*v.begin() == 1);
    REQUIRE(*(v.end() - 1) == 5);

    auto it = v.begin();
    ++it;
    REQUIRE(*it == 2);
    
    auto rit = v.rbegin();
    REQUIRE(*rit == 5);
    ++rit;
    REQUIRE(*rit == 4);
}

// Test capacity functions
TEST_CASE("Vector capacity functions") {
    Vector<int> v;
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);

    v.reserve(100);
    REQUIRE(v.capacity() >= 100);

    v.resize(50);
    REQUIRE(v.size() == 50);
    REQUIRE(v.capacity() >= 100);

    v.shrink_to_fit();
    REQUIRE(v.capacity() == 50);
}

// Test element access
TEST_CASE("Vector element access") {
    Vector<int> v = {1, 2, 3, 4, 5};

    REQUIRE(v[0] == 1);
    REQUIRE(v.at(2) == 3);
    REQUIRE(v.front() == 1);
    REQUIRE(v.back() == 5);
    REQUIRE(v.data() != nullptr);

    try {
        v.at(10);
    } catch (const std::out_of_range&) {
        REQUIRE(true);
    }
}

// Test modifiers
TEST_CASE("Vector modifiers") {
    Vector<int> v;

    v.push_back(1);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);

    v.emplace_back(2);
    REQUIRE(v.size() == 2);
    REQUIRE(v[1] == 2);

    v.pop_back();
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);

    v.insert(v.begin(), 0);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 0);

    v.erase(v.begin());
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);

    v.clear();
    REQUIRE(v.empty());

    Vector<int> v2 = {1, 2, 3};
    v.swap(v2);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v2.empty());
}


