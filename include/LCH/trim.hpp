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

inline void trim_in_place(std::string_view& inputString) {
    using namespace std::string_view_literals;
    auto firstChar = inputString.find_first_not_of(" \f\n\r\t\v"sv);
    if (firstChar != std::string_view::npos) {
        inputString.remove_prefix(firstChar);
    }
    auto lastChar = inputString.find_last_not_of(" \f\n\r\t\v"sv);
    if (lastChar != std::string_view::npos) {
        inputString.remove_suffix(inputString.size() - lastChar - 1);
    }
}

inline std::string trim(std::string inputString) {
    trim_in_place(inputString);
    return inputString;
}

inline std::string_view trim(std::string_view inputString) {
    trim_in_place(inputString);
    return inputString;
}

} // namespace LCH

#endif //LCH_TRIM
