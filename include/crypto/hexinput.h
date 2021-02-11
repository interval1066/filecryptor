#ifndef HEX_INPUT_H
#define HEX_INPUT_H

#include <string>
#include <cstdint>

namespace crypto
{
    /**
     * The HexInput class takes ASCII strings representing hexadecimal
     * values (ex. "0A") and creates an array of bytes holding the
     * interpreted values (owned by the class).
     */
    class HexInput
    {
        uint8_t* keyBytes;
        int keyByteSize;
        std::string prompt;
        bool isValidHexValue(const char&);
        uint8_t getHexValue(const char&);

    public:
        explicit HexInput(const int&);
        explicit HexInput(const int&, const std::string&);
        virtual ~HexInput();

        uint8_t* keyRead(); //throws InvalidKeyException
        uint8_t* keyRead(const std::string&); //throws InvalidKeyException
    };
}

#endif // HEX_INPUT_H
