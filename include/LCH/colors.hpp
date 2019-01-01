#ifndef LCH_COLORS
#define LCH_COLORS

// TODO: expand this to some kind of wrapper for a std::ostream& containing a
// stack for colors, to allow for sensible results across multiple levels

namespace LCH::Colors {

constexpr const char* black =   "\x1b[30m";
constexpr const char* red =     "\x1b[31m";
constexpr const char* green =   "\x1b[32m";
constexpr const char* yellow =  "\x1b[33m";
constexpr const char* blue =    "\x1b[34m";
constexpr const char* magenta = "\x1b[35m";
constexpr const char* cyan =    "\x1b[36m";
constexpr const char* white =   "\x1b[37m";

constexpr const char* bg_black =   "\x1b[40m";
constexpr const char* bg_red =     "\x1b[41m";
constexpr const char* bg_green =   "\x1b[42m";
constexpr const char* bg_yellow =  "\x1b[43m";
constexpr const char* bg_blue =    "\x1b[44m";
constexpr const char* bg_magenta = "\x1b[45m";
constexpr const char* bg_cyan =    "\x1b[46m";
constexpr const char* bg_white =   "\x1b[47m";

constexpr const char* reset =   "\x1b[0m";

} // namespace LCH

#endif //LCH_COLORS
