#include <iostream>

constexpr const char* version = SPINK_VERSION;

int main(int /*argc*/, char** /*argv*/) {
    std::cout << "Spink, an ink parser for C++\nVersion " << version 
        << "\nCompiled " << __DATE__ << " at " << __TIME__ << '\n';
    return EXIT_SUCCESS;
}
