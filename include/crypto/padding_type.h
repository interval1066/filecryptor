#pragma once

#if ! defined PADDING_TYPE_H_
#define PADDING_TYPE_H_

/*---------------------------------------------*
 * Structure declared only in order to have
 * the exact same enumeration in both the
 * AES256 and the Byte_Block class.
 *---------------------------------------------*/
namespace crypto
{
    struct Padding_Type
    {
        enum Padding_Mode
        {
            PKCS7,           // all padding bytes contain their number
            ANSIX9_23,       // last byte contains their number, all others 0
            ISO7816_4,       // first padding byte is 0x80, all others 0
            ALL_NULL         // all unused bytes set to 0
        };
    };
}

#endif

