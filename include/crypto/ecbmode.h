#ifndef ECB_MODE_H
#define ECB_MODE_H

#include <crypto/operationmode.h>

namespace crypto
{
    /**
     * ECB (electronic code book) is a basic mode of operation
     * that simply splits data into blocks and encrypts each block
     * independently. Unfortunately, this means encrypting identical
     * blocks of data always produces identical results, which can
     * leave encrypted data open to analysis when blocks repeat.
     */
    class ECBMode : public OperationMode
    {
        BlockCipher& algorithm;

    public:
        ECBMode(BlockCipher&);
        void encrypt(std::istream&, std::ostream&);
        void decrypt(std::istream&, std::ostream&);
    };
}

#endif // ECB_MODE_H
