// provides LCH::trim functions that take std::string and std::string_view and
// return copies without leading and trailing white space, as well as 
// LCH::trim_in_place functions which do the same operations to references

#ifndef LCH_TRIM
#define LCH_TRIM

#include <string>
#include <string_view>
#include <cctype> // std::isspace
#include <algorithm> // std::find_if

namespace LCH {

namespace Detail {
using namespace std::string_view_literals;
const std::string_view WHITE_SPACE = " \f\n\r\t\v"sv;
} // namespace Detail

// TODO: have these use unicode-aware isspace

inline void trim_in_place(std::string& inputString) {
    inputString.erase(inputString.begin(), 
                      std::find_if(inputString.begin(), inputString.end(),
                                   [](unsigned char c){return !std::isspace(c);}));
    auto lastChar = std::find_if(inputString.rbegin(), inputString.rend(),
                                 [](unsigned char c) {return !std::isspace(c);});

    if (lastChar != inputString.rend()) {
        inputString.erase(std::next(lastChar).base(), inputString.end());
    }
}

// if pos is white space, collapse all contiguous white space into one char
inline void trim_around_in_place(std::string& inputString,
                                 const std::string::size_type pos) {
    if (pos < inputString.size() && std::isspace(inputString[pos])) {
        auto rightEdge = inputString.find_first_not_of(Detail::WHITE_SPACE, pos);
        if (rightEdge != std::string::npos) {
            rightEdge -= 1;
        }
        if (rightEdge != pos) inputString.erase(pos+1, rightEdge-pos);

        auto leftEdge = inputString.find_last_not_of(Detail::WHITE_SPACE, pos);
        if (leftEdge == std::string::npos) {
            leftEdge = 0;
        } else {
            leftEdge += 1;
        }
        if (leftEdge != pos) inputString.erase(leftEdge, pos-leftEdge);
    }
}

inline void trim_in_place(std::string_view& inputString) {
    auto firstChar = inputString.find_first_not_of(Detail::WHITE_SPACE);
    if (firstChar != std::string_view::npos) {
        inputString.remove_prefix(firstChar);
    }
    auto lastChar = inputString.find_last_not_of(Detail::WHITE_SPACE);
    if (lastChar != std::string_view::npos) {
        inputString.remove_suffix(inputString.size() - lastChar - 1);
    }
}

inline std::string trim(std::string inputString) {
    trim_in_place(inputString);
    return inputString;
}

// if pos is white space, collapse all contiguous white space into one char
inline std::string trim_around(std::string inputString, 
                               const std::string::size_type pos) {
    trim_around_in_place(inputString, pos);
    return inputString;
}

inline std::string_view trim(std::string_view inputString) {
    trim_in_place(inputString);
    return inputString;
}

} // namespace LCH

#endif //LCH_TRIM
