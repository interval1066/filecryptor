#pragma once

#if ! defined AES256_PRNG_HPP_
#define AES256_PRNG_HPP_

#include "aes256_base.h"
#include "byte_block.h"
#include <cstdint>

namespace crypto
{
    class AES256_PRNG
    {
      public:
        AES256_PRNG(std::string const& seed = std::string(),
            std::string const& key  = std::string());

        // Reseed the generator
        void
        reseed(std::string const& seed);

        // Get 'size' bytes in a std::string
        std::string
        get(size_t size);

        // Get 'size' bytes into a (user supplied) buffer
        uint8_t* get_buffer(uint8_t* buf, size_t size);

        // Get a N bytes into a (user supplied) Byte_Block object 
	    template<size_t N>
	    void
	    get_block(Byte_Block<N>& dst)
	    {
	    	get_buffer(dst, N);
	    }

    private:
        void fill_pool();

        // AES256_Base instance for encryption
        AES256_Base m_aes256_base;

        // Counter
        Byte_Block<16> m_counter;

        // Ring buffer ("pool") size - this must be an integer multiple of 16
        static size_t const s_pool_size = 64;

        // Ring buffer ("pool") for holding pre-computed random bytes
        Byte_Block<s_pool_size> m_pool;

        // Low amd high filling markers for the buffer
        size_t m_low;
        size_t m_high;
    
        // Initial value of counter
        static uint8_t s_counter[16];

        // Default key for encrypting with AES-256
        static uint8_t s_key[32];
    };
}

#endif

