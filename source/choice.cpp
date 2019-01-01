#include "choice.hpp"

#include "LCH/trim.hpp"
#include "LCH/colors.hpp"

namespace Spink {

const std::vector<std::string>& Choice::options() const noexcept {
    return _options;
}

// const std::vector<Line>& Choice::results() const noexcept {
    // return _results;
// }

const std::vector<Line>& Choice::result(const std::vector<Line>::size_type index) const {
    return _results.at(index);
}

namespace {
std::string clean_option(std::string_view inputString) {
    auto bracketPos = inputString.find('[');
    if (bracketPos != std::string_view::npos) {
        auto endBracketPos = inputString.find(']', bracketPos+1);
        if (endBracketPos != std::string_view::npos) {
            inputString.remove_suffix(inputString.size() - endBracketPos);
            LCH::trim_in_place(inputString);
            // have to find the bracket again in case something got trimmed
            bracketPos = inputString.find('[');
            std::string output(inputString);
            output.erase(bracketPos, 1);
            return output;
        }
    }
    LCH::trim_in_place(inputString);
    return std::string(inputString);
}

std::string clean_result(std::string_view inputString) {
    // the brackets are not prefix or suffix here so we need to save the string
    // before removing them -- we get RVO if we do it at the beginning
    LCH::trim_in_place(inputString);
    std::string output(inputString);
    auto bracketPos = inputString.find('[');
    if (bracketPos != std::string_view::npos) {
        auto endBracketPos = inputString.find(']', bracketPos+1);
        if (endBracketPos != std::string_view::npos) {
            std::string output(inputString);
            output.erase(bracketPos, endBracketPos-bracketPos+1);
            LCH::trim_around_in_place(output, bracketPos);
            return output;
        }
    }
    return output;
}
} // anonymous namespace

Choice Choice::parse(std::string_view inputString) {
    Choice choice;

    std::string_view::size_type optionStart = inputString.find('*');
    while (optionStart != std::string_view::npos) {
        // the option is everything from the '*' to the '\n', exclusive
        std::string_view::size_type optionEnd = inputString.find('\n', 
                                                                 optionStart+1);
        choice._options.push_back(clean_option(
                inputString.substr(optionStart+1, optionEnd-optionStart-1)));

        // the result is everything from the '*' to the next '*', exclusive
        // (this can potentially be several lines)
        std::string_view::size_type resultStart = optionStart;
        std::string_view::size_type resultEnd = inputString.find('*', 
                                                                 resultStart+1);
        std::string resultOnly = clean_result(
                inputString.substr(resultStart+1, resultEnd-resultStart-1));
        choice._results.push_back(Line::parse_multiple(resultOnly));

        optionStart = resultEnd;
    }

    return choice;
}

std::ostream& operator<<(std::ostream& outStream, const Choice& choice) {
    const std::vector<std::string>& options = choice.options();
    for (std::vector<std::string>::size_type i = 0; i < options.size(); ++i) {
        outStream << i+1 << ": " << options[i];
        for (const Line& line : choice.result(i)) {
            outStream << '\n' << LCH::Colors::blue << line << LCH::Colors::reset;
        }
        if (i+1 < options.size()) outStream << '\n';
    }
    return outStream;
}

} // namespace Spink
