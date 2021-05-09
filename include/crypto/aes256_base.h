#pragma once

#if ! defined AES256_BASE_H_
#define AES256_BASE_H_

#include "byte_block.h"
#include "s_box.h"
#include <string>

/*---------------------------------------------*
 * Class implementing the basic AES-256 encryption
 * and decryption methods on 16-byte wide buffers
 * (the 'BO' stands for "byte oriented"). This
 * class is used in all others for doing the low
 * level work.
 *---------------------------------------------*/
namespace crypto
{
    class AES256_Base
    {
    	typedef  unsigned char  byte;

    public:
        // Constructor with key given as a std::string
        AES256_Base(std::string const & key);

        // Constructor with key given as 32-byte block
        AES256_Base(Byte_Block<32> const & key);

        // Change the key
        void
        set_key(std::string const& key);

        // Returns the key
        Byte_Block<32> const&
        get_key() const;

        // Encrypts a block of 16 bytes (in place or returned as a new block)
        Byte_Block<16>&
        encrypt(Byte_Block<16>& buf);

        Byte_Block<16>
        encrypt(Byte_Block<16> const& buf);

        // Decrypts a block of 16 bytes (in place or returning new block)
        Byte_Block<16> &
        decrypt(Byte_Block<16> & buf);

        Byte_Block<16>
        decrypt(Byte_Block<16> const& buf);

    private:
        // Methods doing all the low level work
        void
        expand_enc_key(Byte_Block<32>& key,
                    byte           & rcon);

        void
        expand_dec_key(Byte_Block<32> & key,
                   byte           & rcon);

        void
        sub_bytes(Byte_Block<16> & buf);

        void
        inv_sub_bytes(Byte_Block<16> & buf);

        void
        add_round_key(Byte_Block<16>       & buf,
                  Byte_Block<16> const & key);

        void
        shift_rows(Byte_Block<16> & buf);

        void
        inv_shift_rows(Byte_Block<16> &  buf);

        void
        mix_columns(Byte_Block<16> & buf);

        void
        inv_mix_columns(Byte_Block<16> & buf);

        byte
        rj_xtime(byte x);

        // Initialization method, sets up the keys
    	void
    	init(Byte_Block<32> const & key);

        Byte_Block<32> m_enc_key; 
        Byte_Block<32> m_dec_key;

        // Rijndael S-box and its inverse
        static S_Box<false> const s_sbox;
        static S_Box<true > const s_inv_sbox;

        static bool s_rcon[];
    };
}

#endif

