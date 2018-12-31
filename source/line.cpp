#include "line.hpp"

#include "LCH/colors.hpp"

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
    std::string_view::size_type commentPos = inputString.find("//");
    if (commentPos != std::string_view::npos) {
        inputString.remove_suffix(inputString.size() - commentPos);
    }
    if (inputString.empty()) return output;

    std::string_view::size_type tagPos = inputString.find('#');
    if (tagPos != std::string_view::npos) {
        output._tag = inputString.substr(tagPos+1);
    }
    output._text = inputString.substr(0, tagPos);
    return output;
}

std::ostream& operator<<(std::ostream& outStream, const Line& line) {
    outStream << line.text()
        << LCH::Colors::yellow << "#" << line.tag() << LCH::Colors::reset;
    return outStream;
}

} // namespace Spink
