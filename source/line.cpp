#include "line.hpp"

#include "LCH/colors.hpp"
#include "LCH/trim.hpp"

namespace Spink {

std::string_view Line::text() const {
    return {_text.data(), _text.size()};
}

std::string_view Line::tag() const {
    return {_tag.data(), _tag.size()};
}

bool Line::empty() const noexcept {
    return _text.empty() && _tag.empty();
}

Line Line::parse(std::string_view inputString) {
    Line output;

    if (inputString.empty()) return output;

    std::string_view::size_type tagPos = inputString.find('#');
    if (tagPos != std::string_view::npos) {
        output._tag = LCH::trim(inputString.substr(tagPos+1));
    }
    output._text = LCH::trim(inputString.substr(0, tagPos));
    return output;
}

std::vector<Line> Line::parse_multiple(std::string_view inputString) {
    std::vector<Line> output;
    std::string_view::size_type lineStart = 0;
    while (lineStart < inputString.size()) {
        std::string_view::size_type lineEnd = 
            std::min(inputString.find('\n', lineStart), inputString.size());
        output.push_back(parse(inputString.substr(lineStart, lineEnd-lineStart)));
        lineStart = lineEnd+1;
    }
    return output;
}

std::ostream& operator<<(std::ostream& outStream, const Line& line) {
    outStream << line.text();
    if (!line.tag().empty()) {
        outStream << LCH::Colors::yellow << "#" << line.tag() 
            << LCH::Colors::reset;
    }
    return outStream;
}

} // namespace Spink
