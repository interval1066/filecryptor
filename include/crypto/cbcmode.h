#ifndef CBC_MODE_H
#define CBC_MODE_H

#include <crypto/operationmode.h>

namespace crypto
{
    /**
     * CBC (cipher block chaining) is a mode of operation that
     * "adds" (XOR) the previous cipher block (already encrypted)
     * to the current block of data before encrypting. For the
     * first block, an initialization vector is used in place of
     * a previous cipher block (which does not exist).
     */
    class CBCMode : public OperationMode
    {
        BlockCipher& algorithm;
        uint8_t* initializationVector;

    public:
        explicit CBCMode(BlockCipher&, uint8_t*);
        virtual ~CBCMode();

        void encrypt(std::istream&, std::ostream&);
        void decrypt(std::istream&, std::ostream&);
        void addBlock(uint8_t*, uint8_t*, const int&);
    };
}

#endif // CBC_MODE_H
