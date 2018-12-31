#include "story.hpp"

#include <fstream>
#include <iterator>

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
    std::string rawFile(std::istreambuf_iterator<char>{inStream}, {});

    // erase block comments
    std::string::size_type blockStart = rawFile.find("/*");
    while (blockStart != std::string::npos) {
        std::string::size_type blockEnd = rawFile.find("*/", blockStart+2);
        if (blockEnd != std::string::npos) {
            rawFile.erase(blockStart, blockEnd-blockStart+2);
        } else {
            break;
        }
        blockStart = rawFile.find("/*");
    }

    // erase inline comments
    while (true) {
        std::string::size_type commentStart = rawFile.find("//");
        if (commentStart == std::string::npos) break;
        std::string::size_type commentEnd = rawFile.find("\n", commentStart+2);
        // careful not to delete the newline
        rawFile.erase(commentStart, commentEnd-commentStart);
    }

    // parse lines from whatever's left
    std::string::size_type lineEnd = -1;
    do {
        std::string::size_type lineStart = lineEnd+1;
        lineEnd = std::min(rawFile.find("\n", lineStart), rawFile.size());
        Line newLine = Line::parse({rawFile.data() + lineStart, 
                                    lineEnd - lineStart});
        if (!newLine.empty()) output._lines.push_back(std::move(newLine));
    } while (lineEnd < rawFile.size());

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
