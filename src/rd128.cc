#include <crypto/rd128.h>

using namespace crypto;

RD128::RD128(const char* str, unsigned int size)
{
    init();
    compose(str, size);
}

uint32_t
RD128::rotate_l(uint32_t x, unsigned int n)
{
    return (x << n) | (x >> (32 - n));
}

uint32_t
RD128::F(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

uint32_t
RD128::G(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (~x & z);
}

uint32_t
RD128::H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x | ~y) ^ z;
}

uint32_t
RD128::I(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & z) | (y & ~z);
}

void
RD128::FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + F(b, c, d) + X[k]), s);
}

void
RD128::GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + G(b, c, d) + X[k] + 0x5a827999), s);
}

void
RD128::HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + H(b, c, d) + X[k] + 0x6ed9eba1), s);
}

void
RD128::II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + I(b, c, d) + X[k] + 0x8f1bbcdc), s);
}

void
RD128::FFF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + F(b, c, d) + X[k] + 0x00000000), s);
}

void
RD128::GGG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + G(b, c, d) + X[k] + 0x6d703ef3), s);
}

void
RD128::HHH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + H(b, c, d) + X[k] + 0x5c4dd124), s);
}

void
RD128::III(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, unsigned int k, unsigned int s)
{
    a = rotate_l((a + I(b, c, d) + X[k] + 0x50a28be6), s);
}

void
RD128::init()
{
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

void
RD128::compose(const char* str, unsigned int length)
{
    unsigned int rest = length % 64, size;
    //making 448mod512
    if (rest < 56)
        size = 56 - rest + length + 8; //8 bytes - initial legth
    else
        size = 64 - rest + 56 + length + 8;

    unsigned char* message = new unsigned char[size];
    for (unsigned i = 0; i < length; i++)
        message[i] = str[i];

    //adding 1
    message[length] = 0x80;
    for (unsigned i = length + 1; i < size; i++)
        message[i] = 0;

    //64-bit initial length
    unsigned char chunk[64];
    uint64_t length64 = (uint64_t)length * 8;

    //go to the last chunk ( or the only one chunk )
    if(size == 64)
        goto last_chunk;

    //transforming 64-bit chunks except the last
    for(unsigned i = 0; i <= (size - 128); i += 64) {
        for (int j = 0; j < 64; j++)
            chunk[j] = message[i + j];

        decode(X, chunk, 64);
        transform();
    }

    last_chunk:
    for(unsigned i = (size - 64); i < size; i++)
        chunk[i - (size - 64)] = message[i];

    decode(X, chunk, 64);
    uint32_t length64_l = (uint32_t)length64;
    uint32_t length64_r = (uint32_t)(length64 << 32);

    X[14] = length64_l;
    X[15] = length64_r;
    transform();

    delete[] message;
}

void
RD128::decode(uint32_t* output, unsigned char input[], unsigned int len)
{
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
        (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
}

void
RD128::encode(unsigned char *output, const uint32_t input[], unsigned int len)
{
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = input[i] & 0xff;
        output[j + 1] = (input[i] >> 8) & 0xff;
        output[j + 2] = (input[i] >> 16) & 0xff;
        output[j + 3] = (input[i] >> 24) & 0xff;
    }
}

void
RD128::transform()
{
    uint32_t aa = state[0], bb = state[1], cc = state[2], dd = state[3];
    uint32_t aaa = state[0], bbb = state[1], ccc = state[2], ddd = state[3];

    /*LEFT PART*/
    /* round 1 */
    FF(aa, bb, cc, dd,  0 , 11);
    FF(dd, aa, bb, cc,  1 , 14);
    FF(cc, dd, aa, bb,  2 , 15);
    FF(bb, cc, dd, aa,  3 , 12);
    FF(aa, bb, cc, dd,  4 , 5);
    FF(dd, aa, bb, cc,  5 , 8);
    FF(cc, dd, aa, bb,  6 , 7);
    FF(bb, cc, dd, aa,  7 , 9);
    FF(aa, bb, cc, dd,  8 , 11);
    FF(dd, aa, bb, cc,  9 , 13);
    FF(cc, dd, aa, bb,  10 , 14);
    FF(bb, cc, dd, aa,  11 , 15);
    FF(aa, bb, cc, dd,  12 , 6);
    FF(dd, aa, bb, cc,  13 , 7);
    FF(cc, dd, aa, bb,  14 , 9);
    FF(bb, cc, dd, aa,  15 , 8);

    /* round 2 */
    GG(aa, bb, cc, dd,  7 , 7);
    GG(dd, aa, bb, cc,  4 , 6);
    GG(cc, dd, aa, bb,  13 , 8);
    GG(bb, cc, dd, aa,  1 , 13);
    GG(aa, bb, cc, dd,  10 , 11);
    GG(dd, aa, bb, cc,  6 , 9);
    GG(cc, dd, aa, bb,  15 , 7);
    GG(bb, cc, dd, aa,  3 , 15);
    GG(aa, bb, cc, dd,  12 , 7);
    GG(dd, aa, bb, cc,  0 , 12);
    GG(cc, dd, aa, bb,  9 , 15);
    GG(bb, cc, dd, aa,  5 , 9);
    GG(aa, bb, cc, dd,  2 , 11);
    GG(dd, aa, bb, cc,  14 , 7);
    GG(cc, dd, aa, bb,  11 , 13);
    GG(bb, cc, dd, aa,  8 , 12);

    /* round 3 */
    HH(aa, bb, cc, dd,  3 , 11);
    HH(dd, aa, bb, cc,  10 , 13);
    HH(cc, dd, aa, bb,  14 , 6);
    HH(bb, cc, dd, aa,  4 , 7);
    HH(aa, bb, cc, dd,  9 , 14);
    HH(dd, aa, bb, cc,  15 , 9);
    HH(cc, dd, aa, bb,  8 , 13);
    HH(bb, cc, dd, aa,  1 , 15);
    HH(aa, bb, cc, dd,  2 , 14);
    HH(dd, aa, bb, cc,  7 , 8);
    HH(cc, dd, aa, bb,  0 , 13);
    HH(bb, cc, dd, aa,  6 , 6);
    HH(aa, bb, cc, dd,  13 , 5);
    HH(dd, aa, bb, cc,  11 , 12);
    HH(cc, dd, aa, bb,  5 , 7);
    HH(bb, cc, dd, aa,  12 , 5);

    /* round 4 */
    II(aa, bb, cc, dd,  1 , 11);
    II(dd, aa, bb, cc,  9 , 12);
    II(cc, dd, aa, bb,  11 , 14);
    II(bb, cc, dd, aa,  10 , 15);
    II(aa, bb, cc, dd,  0 , 14);
    II(dd, aa, bb, cc,  8 , 15);
    II(cc, dd, aa, bb,  12 , 9);
    II(bb, cc, dd, aa,  4 , 8);
    II(aa, bb, cc, dd,  13 , 9);
    II(dd, aa, bb, cc,  3 , 14);
    II(cc, dd, aa, bb,  7 , 5);
    II(bb, cc, dd, aa,  15 , 6);
    II(aa, bb, cc, dd,  14 , 8);
    II(dd, aa, bb, cc,  5 , 6);
    II(cc, dd, aa, bb,  6 , 5);
    II(bb, cc, dd, aa,  2 , 12);

    /* parallel round 1 */
    III(aaa, bbb, ccc, ddd,  5 , 8);
    III(ddd, aaa, bbb, ccc,  14 , 9);
    III(ccc, ddd, aaa, bbb,  7 , 9);
    III(bbb, ccc, ddd, aaa,  0 , 11);
    III(aaa, bbb, ccc, ddd,  9 , 13);
    III(ddd, aaa, bbb, ccc,  2 , 15);
    III(ccc, ddd, aaa, bbb,  11 , 15);
    III(bbb, ccc, ddd, aaa,  4 , 5);
    III(aaa, bbb, ccc, ddd,  13 , 7);
    III(ddd, aaa, bbb, ccc,  6 , 7);
    III(ccc, ddd, aaa, bbb,  15 , 8);
    III(bbb, ccc, ddd, aaa,  8 , 11);
    III(aaa, bbb, ccc, ddd,  1 , 14);
    III(ddd, aaa, bbb, ccc,  10 , 14);
    III(ccc, ddd, aaa, bbb,  3 , 12);
    III(bbb, ccc, ddd, aaa,  12 , 6);

    /* parallel round 2 */
    HHH(aaa, bbb, ccc, ddd,  6 , 9);
    HHH(ddd, aaa, bbb, ccc,  11 , 13);
    HHH(ccc, ddd, aaa, bbb,  3 , 15);
    HHH(bbb, ccc, ddd, aaa,  7 , 7);
    HHH(aaa, bbb, ccc, ddd,  0 , 12);
    HHH(ddd, aaa, bbb, ccc,  13 , 8);
    HHH(ccc, ddd, aaa, bbb,  5 , 9);
    HHH(bbb, ccc, ddd, aaa,  10 , 11);
    HHH(aaa, bbb, ccc, ddd,  14 , 7);
    HHH(ddd, aaa, bbb, ccc,  15 , 7);
    HHH(ccc, ddd, aaa, bbb,  8 , 12);
    HHH(bbb, ccc, ddd, aaa,  12 , 7);
    HHH(aaa, bbb, ccc, ddd,  4 , 6);
    HHH(ddd, aaa, bbb, ccc,  9 , 15);
    HHH(ccc, ddd, aaa, bbb,  1 , 13);
    HHH(bbb, ccc, ddd, aaa,  2 , 11);

    /* parallel round 3 */
    GGG(aaa, bbb, ccc, ddd,  15 , 9);
    GGG(ddd, aaa, bbb, ccc,  5 , 7);
    GGG(ccc, ddd, aaa, bbb,  1 , 15);
    GGG(bbb, ccc, ddd, aaa,  3 , 11);
    GGG(aaa, bbb, ccc, ddd,  7 , 8);
    GGG(ddd, aaa, bbb, ccc,  14 , 6);
    GGG(ccc, ddd, aaa, bbb,  6 , 6);
    GGG(bbb, ccc, ddd, aaa,  9 , 14);
    GGG(aaa, bbb, ccc, ddd,  11 , 12);
    GGG(ddd, aaa, bbb, ccc,  8 , 13);
    GGG(ccc, ddd, aaa, bbb,  12 , 5);
    GGG(bbb, ccc, ddd, aaa,  2 , 14);
    GGG(aaa, bbb, ccc, ddd,  10 , 13);
    GGG(ddd, aaa, bbb, ccc,  0 , 13);
    GGG(ccc, ddd, aaa, bbb,  4 , 7);
    GGG(bbb, ccc, ddd, aaa,  13 , 5);

    /* parallel round 4 */
    FFF(aaa, bbb, ccc, ddd,  8 , 15);
    FFF(ddd, aaa, bbb, ccc,  6 , 5);
    FFF(ccc, ddd, aaa, bbb,  4 , 8);
    FFF(bbb, ccc, ddd, aaa,  1 , 11);
    FFF(aaa, bbb, ccc, ddd,  3 , 14);
    FFF(ddd, aaa, bbb, ccc,  11 , 14);
    FFF(ccc, ddd, aaa, bbb,  15 , 6);
    FFF(bbb, ccc, ddd, aaa,  0 , 14);
    FFF(aaa, bbb, ccc, ddd,  5 , 6);
    FFF(ddd, aaa, bbb, ccc,  12 , 9);
    FFF(ccc, ddd, aaa, bbb,  2 , 12);
    FFF(bbb, ccc, ddd, aaa,  13 , 9);
    FFF(aaa, bbb, ccc, ddd,  9 , 12);
    FFF(ddd, aaa, bbb, ccc,  7 , 5);
    FFF(ccc, ddd, aaa, bbb,  10 , 15);
    FFF(bbb, ccc, ddd, aaa,  14 , 8);


    ddd += cc + state[1];
    state[1] = state[2] + dd + aaa;
    state[2] = state[3] + aa + bbb;
    state[3] = state[0] + bb + ccc;
    state[0] = ddd;
}

QString
RD128::hexdigest()
{
    encode(digest, state, 16);
    char buf[33];

    for(int i = 0; i < 16; i++)
        sprintf(buf + i * 2, "%02x", digest[i]);

    buf[32] = 0;

    return QString(buf);
}
