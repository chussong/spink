//
//
//

#ifndef SPINK_STORY_HPP
#define SPINK_STORY_HPP

#include "line.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <iostream>

namespace Spink {

class Story {
  public:
    std::string_view name() const;
    const std::vector<Line>& lines() const noexcept;

    static Story parse(const std::filesystem::path& inputPath);
  private:
    std::string _name;
    std::vector<Line> _lines;
};

std::ostream& operator<<(std::ostream& outStream, const Story& story);

} // namespace Spink

#endif // SPINK_STORY_HPP
