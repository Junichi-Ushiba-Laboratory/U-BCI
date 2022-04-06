#ifndef UBCIEXCEPTION_H
#define UBCIEXCEPTION_H

#include "string"

// Generate the exception in U-BCI
class UbciException
{
public:
    // Generate exception
    UbciException(const std::string &message) : MESSAGE(message) {}

    // Get the exception message
    const char *what() { return MESSAGE.c_str(); }

private:
    // Exception message
    const std::string MESSAGE;
};

#endif // UBCIEXCEPTION_H
