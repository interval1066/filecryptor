#ifndef RD128_H_
#define RD128_H_

#include <iostream>
#include <string>
#include <QString>
#include <QChar>
#include <ctime>
#include <cstring>
#include <cstdint>

namespace crypto
{
    class RD128
    {
        // 4 32-bit initial words
        uint32_t state[4];

        // 16 32-bit input blocks
        uint32_t X[16];

        // the result
        unsigned char digest[16];

        // left cycle rotate
        uint32_t rotate_l(uint32_t x, unsigned int n);

        // round subfunctions
        uint32_t F(uint32_t x, uint32_t y, uint32_t z);
        uint32_t G(uint32_t x, uint32_t y, uint32_t z);
        uint32_t H(uint32_t x, uint32_t y, uint32_t z);
        uint32_t I(uint32_t x, uint32_t y, uint32_t z);

        // round functions - left part
        void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);

        // round functions - right part
        void FFF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void GGG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void HHH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);
        void III(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s);

        // initialization of the internal states
        void init();

        // adding to 448mod512, making 32-bit chunks
        void compose(const char *str, unsigned int size);

        // transformating blocks
        void transform();

        // char [64] -> uint32_t [16]
        void decode(uint32_t* output, unsigned char input[], unsigned int len);

        // uint32_t [4] -> char [16]
        void encode(unsigned char* output, const uint32_t input[], unsigned int len);

   public:
        explicit RD128(const char* str, unsigned int size);
        QString hexdigest();
    };
}

#endif

