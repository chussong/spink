//
//
//

#ifndef SPINK_LINE_HPP
#define SPINK_LINE_HPP

#include <string>
#include <string_view>
#include <iostream>

namespace Spink {

class Line {
  public:
    std::string_view text() const;
    std::string_view tag() const;
    bool empty() const noexcept;

    static Line parse(std::string_view inputString);
  private:
    std::string _text;
    std::string _tag;
};

std::ostream& operator<<(std::ostream& outStream, const Line& line);

} // namespace Spink

#endif // SPINK_LINE_HPP
