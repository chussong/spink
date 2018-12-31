#include "story.hpp"

#include <fstream>

namespace Spink {

std::string_view Story::name() const {
    return {_name.data(), _name.size()};
}

const std::vector<Line>& Story::lines() const noexcept {
    return _lines;
}

Story Story::parse(const std::filesystem::path& inputPath) {
    Story output;
    output._name = inputPath.filename();

    std::ifstream inStream(inputPath);
    for (std::string rawLine; inStream; std::getline(inStream, rawLine)) {
        Line newLine = Line::parse(rawLine);
        if (!newLine.empty()) output._lines.push_back(std::move(newLine));
    }
    return output;
}

std::ostream& operator<<(std::ostream& outStream, const Story& story) {
    outStream << "***** " << story.name() << " *****\n";
    for (const Line& line : story.lines()) {
        outStream << line << '\n';
    }
    return outStream;
}

} // namespace Spink
