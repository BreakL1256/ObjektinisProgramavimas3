#define CATCH_CONFIG_MAIN  
#include "catch2/catch.hpp"
#include "skaiciavimai.h"

TEST_CASE( "Copy constructor", "[CC]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}};
    mokinys b{a};

    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();

    REQUIRE(a.vard() == b.vard());
    REQUIRE(a.pavard() == b.pavard());
    REQUIRE(aVec.size() == bVec.size());
    for (int i = 0; i < aVec.size(); ++i) {
        REQUIRE(aVec[i] == bVec[i]);
    }
}

TEST_CASE( "Move constructor", "[MC]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}};
    mokinys b{move(a)};

    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();

    REQUIRE(a.vard() == "");
    REQUIRE(a.pavard() == "");
    REQUIRE(a.tarpRezultatai().empty());
    REQUIRE(b.vard() != a.vard());
    REQUIRE(b.pavard() != a.pavard());
    REQUIRE(aVec.size() != bVec.size());
    for (int i = 0; i < bVec.size(); ++i) {
        REQUIRE_FALSE(bVec[i] == aVec[i]);
    }
}

TEST_CASE( "Copy assignment operator", "[CAO]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}}, b;
    b = a;

    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();

    REQUIRE(a.vard() == b.vard());
    REQUIRE(a.pavard() == b.pavard());
    REQUIRE(aVec.size() == bVec.size());
    for (int i = 0; i < aVec.size(); ++i) {
        REQUIRE(aVec[i] == bVec[i]);
    }
    
}

TEST_CASE( "Move assignment operator", "[MAO]" ) {
    mokinys a{"Tom", "Tom", {3, 5, 6}}, b;
    b = move(a);

    vector<int> aVec = a.tarpRezultatai();
    vector<int> bVec = b.tarpRezultatai();

    REQUIRE(a.vard() == "");
    REQUIRE(a.pavard() == "");
    REQUIRE(a.tarpRezultatai().empty());
    REQUIRE(b.vard() != a.vard());
    REQUIRE(b.pavard() != a.pavard());
    REQUIRE(aVec.size() != bVec.size());
    for (int i = 0; i < bVec.size(); ++i) {
        REQUIRE_FALSE(bVec[i] == aVec[i]);
    }
}

TEST_CASE( "Ivesties operatorius", "[IO]" ) {
    mokinys e;
    REQUIRE(cin>>e);
}

TEST_CASE( "Isvesties operatorius", "[IO]" ) {
    mokinys e;
    REQUIRE(cout<<e);
}

TEST_CASE( "BEt koks testas", "II" ) {
    int e = 1, b = 2;
    REQUIRE(e == b);
}


