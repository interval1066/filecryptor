#include <string>
#include <sstream>

#include "invalidargumentexception.h"

InvalidArgumentException::InvalidArgumentException(const std::string & details)
            : std::runtime_error(getErrorMessage(details)) {}

std::string InvalidArgumentException::getErrorMessage(const std::string & details)
{
    std::ostringstream stringStream;
    stringStream << "Invalid Argument: " << details;
    return stringStream.str();
}
