#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

namespace crypto
{
    namespace utilities
    {
        // String Utilities
        bool equalsIgnoreCase(const char&, const char&);
        bool equalsIgnoreCase(const std::string&, const std::string&);
    }
}

#endif
