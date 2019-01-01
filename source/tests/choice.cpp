// tests/choice.cpp: test choice.cpp using Catch2.

#include "choice.hpp"

#include "Catch2/catch.hpp"

#include <sstream>

namespace {
const std::vector<std::array<std::string,2>> cases {
    {"",
     ""},
    {"* choice 1", 
     "1: choice 1\n[34mchoice 1[0m"},
    {"* choice 1\ncontinuation 1", 
     "1: choice 1\n[34mchoice 1[0m\n[34mcontinuation 1[0m"},
    {"* choice 1\n* choice 2", 
     "1: choice 1\n[34mchoice 1[0m\n2: choice 2\n[34mchoice 2[0m"},
    {"*choice 1\ncontinuation 1\n* choice2\ncontinuation 2", 
     "1: choice 1\n[34mchoice 1[0m\n[34mcontinuation 1[0m\n2: choice2\n[34mchoice2[0m\n[34mcontinuation 2[0m"},
    {"*choice 1\ncontinuation 1a\ncontinuation 1b\n"
        "* choice2\ncontinuation 2a\ncontinuation 2b", 
     "1: choice 1\n[34mchoice 1[0m\n[34mcontinuation 1a[0m\n[34mcontinuation 1b[0m\n2: choice2\n[34mchoice2[0m\n[34mcontinuation 2a[0m\n[34mcontinuation 2b[0m"}
};

void run_case(const std::array<std::string,2>& testCase) {
    std::stringstream stringStream;
    Spink::Choice choice = Spink::Choice::parse(testCase[0]);
    stringStream << choice;
    REQUIRE(stringStream.str() == testCase[1]);
}
} // anonymous namespace

TEST_CASE("can correctly parse a choice", "[choice]") {
    SECTION("parse an empty choice") {
        run_case(cases[0]);
    }

    SECTION("parse a choice with 1 option and no result") {
        run_case(cases[1]);
    }

    SECTION("parse a choice with 1 option and a result") {
        run_case(cases[2]);
    }

    SECTION("parse a choice with 2 options and no results") {
        run_case(cases[3]);
    }

    SECTION("parse a choice with 2 options and 1 result each") {
        run_case(cases[4]);
    }

    SECTION("parse a choice with 2 options and 2 results each") {
        run_case(cases[5]);
    }
}
