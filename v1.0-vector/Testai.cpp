#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "skaiciavimai.h"

TEST_CASE( "Copy constructor", "[CC]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}};
    mokinys b{a};
    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();
    REQUIRE(a.vard() == b.vard() && a.pavard() == b.pavard() && aVec.size() == bVec.size());
    for (int i = 0; i < aVec.size(); ++i) {
        REQUIRE(aVec[i] == bVec[i]);
    }
}

TEST_CASE( "Move constructor", "[MC]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}};
    mokinys b{move(a)};
    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();
    REQUIRE(a.vard() == "" && a.pavard() == "" && a.tarpRezultatai().empty());

}

TEST_CASE( "Copy assignment operator", "[CAO]" ) {
   
}

TEST_CASE( "Move assignment operator", "[MAO]" ) {
   
}

TEST_CASE( "Ivesties operatorius", "[IO]" ) {
   
}

TEST_CASE( "Isvesties operatorius", "[IO]" ) {
   
}

