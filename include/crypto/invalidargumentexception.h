#ifndef INVALID_ARGUMENT_EXCEPTION_H
#define INVALID_ARGUMENT_EXCEPTION_H

#include <stdexcept>

namespace cryto
{
    class InvalidArgumentException : public std::runtime_error
    {
        std::string getErrorMessage(const std::string&);

    public:
        InvalidArgumentException(const std::string&);
    };
}

#endif // INVALID_ARGUMENT_EXCEPTION_H
