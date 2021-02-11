#ifndef INVALID_KEY_EXCEPTION_H
#define INVALID_KEY_EXCEPTION_H

#include <stdexcept>

namespace crypto
{
    class InvalidKeyException : public std::runtime_error
    {
        std::string getErrorMessage(const int&);
        std::string getErrorMessage(const int&, const int&);

    public:
        InvalidKeyException(const int&, const int&);
        InvalidKeyException(const int&);
    };
}

#endif // INVALID_KEY_EXCEPTION_H
