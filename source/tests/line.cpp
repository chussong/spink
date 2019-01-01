// tests/line.cpp: test line.cpp using Catch2.

#include "line.hpp"

#include "Catch2/catch.hpp"

#include <sstream>

namespace {
const std::vector<std::array<std::string,2>> cases {
    {"",
     ""},
    {"Printable line 1", 
     "Printable line 1"},
    {"Printable line 2 # with a tag", 
     "Printable line 2[33m#with a tag[0m"},
    {"Printable line 3 #with#weird#multiple#tags", 
     "Printable line 3[33m#with#weird#multiple#tags[0m"},
    {"#tag-only line", 
     "[33m#tag-only line[0m"}
};

void run_case(const std::array<std::string,2>& testCase) {
    std::stringstream stringStream;
    Spink::Line line = Spink::Line::parse(testCase[0]);
    stringStream << line;
    REQUIRE(stringStream.str() == testCase[1]);
}
} // anonymous namespace

TEST_CASE("can correctly parse a line", "[line]") {
    SECTION("parse an empty line") {
        run_case(cases[0]);
    }

    SECTION("parse a line without a tag") {
        run_case(cases[1]);
    }

    SECTION("parse a line with a tag") {
        run_case(cases[2]);
    }

    SECTION("parse a line with multiple tags") {
        run_case(cases[3]);
    }

    SECTION("parse a line with a tag and no other text") {
        run_case(cases[4]);
    }
}
