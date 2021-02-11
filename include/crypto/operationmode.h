#ifndef ENCRYPTION_MODE_H_
#define ENCRYPTION_MODE_H_

#include <fstream>

#include <crypto/blockcipher.h>

namespace crypto
{
    /**
     * OperationMode is an abstract class for modes of operation,
     * which are standard ways data can be encrypted or decrypted
     * using a block cipher. This is required since data comes in
     * varying lengths while these ciphers only accept a fixed
     * number of bytes as input.
     */
    class OperationMode
    {
        public:
            virtual void encrypt(std::istream&, std::ostream&) = 0;
            virtual void decrypt(std::istream&, std::ostream&) = 0;
            void padBuffer(uint8_t*, const int&, const int&);
    };
}

#endif
