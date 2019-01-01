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

Choice Choice::parse(std::string_view inputString) {
    Choice choice;

    std::string_view::size_type optionStart = inputString.find('*');
    while (optionStart != std::string_view::npos) {
        // the option is everything from the '*' to the '\n', exclusive
        std::string_view::size_type optionEnd = inputString.find('\n', 
                                                                 optionStart+1);
        choice._options.emplace_back(LCH::trim(
                inputString.substr(optionStart+1, optionEnd-optionStart-1)));

        // the result is everything from the '*' to the next '*', exclusive
        // (this can potentially be several lines)
        std::string_view::size_type resultStart = optionStart;
        std::string_view::size_type resultEnd = inputString.find('*', 
                                                                 resultStart+1);
        choice._results.push_back(Line::parse_multiple(
                inputString.substr(resultStart+1, resultEnd-resultStart-1)));

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
