/* -*- c++ -*- */
/*
 * Copyright 2014 Ronald Sadlier - Oak Ridge National Laboratory
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ecc_hamming74_decode_bb_impl.h"

namespace gr {
  namespace qitkat {

    ecc_hamming74_decode_bb::sptr ecc_hamming74_decode_bb::make() {
      return gnuradio::get_initial_sptr(new ecc_hamming74_decode_bb_impl());
    }

    // Initialize our decode lookup table.
    // In: (in0, in1, in2, in3)
    // Out: (0, p1, p2, d1, p3, d2, d3, d4)
    const unsigned char ecc_hamming74_decode_bb_impl::d_decodeTable[16] = {
      0x0,	// in: (0)0000000 out: 0000
      0x69,	// in: (0)1101001 out: 0001
      0x2a,	// in: (0)0101010 out: 0010
      0x43,	// in: (0)1000011 out: 0011
      0x4c,	// in: (0)1001100 out: 0100
      0x25,	// in: (0)0100101 out: 0101
      0x66,	// in: (0)1100110 out: 0110
      0xf,	// in: (0)0001111 out: 0111
      0x70,	// in: (0)1110000 out: 1000
      0x19,	// in: (0)0011001 out: 1001
      0x5a,	// in: (0)1011010 out: 1010
      0x33,	// in: (0)0110011 out: 1011
      0x3c,	// in: (0)0111100 out: 1100
      0x55,	// in: (0)1010101 out: 1101
      0x16,	// in: (0)0010110 out: 1110
      0x7f	// in: (0)1111111 out: 1111
    };

    // Initialize our 3x8 H matrix.
    // Each row is treated as a byte with each bit representing an element.
    const unsigned char ecc_hamming74_decode_bb_impl::d_H[3] = {
      0x55,	// (0)1010101
      0x33,	// (0)0110011
      0x0f	// (0)0001111
    };

    ecc_hamming74_decode_bb_impl::ecc_hamming74_decode_bb_impl()
      : gr::sync_decimator("ecc_hamming74_decode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), 2) {
    }

    ecc_hamming74_decode_bb_impl::~ecc_hamming74_decode_bb_impl(){
    }

    int ecc_hamming74_decode_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      unsigned int outputPos = 0;

      for(int i = 0; i < noutput_items*2; i+=2) {
        // Copy of our two input bytes so we may modify them (and keep a record of what we received).
        unsigned char inputByte[2] = {in[i], in[i+1]};

        // The syndrome of the error correction algorithm. This is the base2 result
        // result of d_H*inputByteN, which is why we use bool. Each time we add to an
        // element, we just invert it.
        bool syndrome[3] = {false};

        // Decode two input bytes into one output byte.
        for(unsigned char inputByteN = 0; inputByteN < 2; inputByteN++) {
          // Clear our syndrome vector.
          memset(syndrome, false, 3);

          // Multiply each bit in d_H by inputByteN.
          for(unsigned char h = 0; h < 3; h++) {
            // Check each bit in the row of H and the col of the incoming byte.
            for(unsigned char col = 0; col < 8; col++) {
              // We multiply each element in the two rows.
              if((((d_H[h] & (1 << col)) & (inputByte[inputByteN] & (1 << col))) >> col) != 0) {
                // Since we are adding in base 2, we can simply flip the proper syndrome bit.
                syndrome[h] = !syndrome[h];
              }
            }
          }

          // If our syndrome does not have trivial elements, we need to perform error correction.
          if((syndrome[0] || syndrome[1] || syndrome[2]) == true) {
            // We convert the three boolean values to a 3 bit number representing the bit we need to flip.
            // We'd like to ensure our boolean true is cast properly (if this is even a problem).
            inputByte[inputByteN] ^= 1 << (7 - (((syndrome[2]?1:0) << 2) + ((syndrome[1]?1:0) << 1) + (syndrome[0]?1:0)));
          }

          // Try to decode the input byte.
          for(unsigned char j = 0; j < 16; j++) {
            if(inputByte[inputByteN] == d_decodeTable[j]) {
              // This bit shifting is really a hack.
              out[outputPos] += (j << 4*inputByteN);
              j = 16;
            }
          }
        }
        outputPos++;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
  } /* namespace qitkat */
} /* namespace gr */

