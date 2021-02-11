#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <crypto/aesconstants.h>
#include <crypto/blockcipher.h>

namespace crypto
{
    /**
     * Given a key and key size, an AES instance can encrypt
     * or decrypt 16-byte blocks of data.
     */
    class AES : public BlockCipher
    {
        uint8_t* keySchedule;
        int keyByteSize;
        int numberRounds;

        uint8_t* generateKeySchedule(uint8_t*);
        void addWords(uint8_t*, uint8_t*);
        void addKey(uint8_t*, uint8_t*);

        void leftCyclicByteShiftWord(uint8_t*);
        uint8_t* aesG(uint8_t*, int);
        uint8_t* aesH(uint8_t*);

        void byteSubstitution(uint8_t*);
        void inverseByteSubstitution(uint8_t*);
        void shiftRows(uint8_t*);

        void inverseShiftRows(uint8_t*);
        void mixColumns(uint8_t*);
        void inverseMixColumns(uint8_t*);

     public:
            AES(uint8_t*, const int&);
            ~AES();
            void encrypt(uint8_t*);
            void decrypt(uint8_t*);
    };
}
#endif // AES_H
