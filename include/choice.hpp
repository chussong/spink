//
//
//

#ifndef SPINK_CHOICE_HPP
#define SPINK_CHOICE_HPP

#include "line.hpp"

#include <string>
#include <string_view>
#include <iostream>

namespace Spink {

class Choice {
  public:
    const std::vector<std::string>& options() const noexcept;
    // const std::vector<std::vector<Line>>& results() const noexcept;
    const std::vector<Line>& result(const std::vector<Line>::size_type index) const;

    static Choice parse(std::string_view inputString);
  private:
    // these two should always be in the same size and same order, but are kept
    // separate so that _options can be inspected in place as a vector
    std::vector<std::string> _options;
    std::vector<std::vector<Line>> _results;
};

std::ostream& operator<<(std::ostream& outStream, const Choice& line);

} // namespace Spink

#endif // SPINK_CHOICE_HPP
