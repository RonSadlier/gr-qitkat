/* -*- c++ -*- */
/* 
 * Copyright 2011 - 2014 Travis S. Humble - Oak Ridge National Laboratory
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
#include "bsc_bb_impl.h"

namespace gr {
  namespace qitkat {

    bsc_bb::sptr bsc_bb::make(float error_rate, unsigned int seed, unsigned char bit_mask) {
      return gnuradio::get_initial_sptr(new bsc_bb_impl(error_rate, seed, bit_mask));
    }

    bsc_bb_impl::bsc_bb_impl(float error_rate, unsigned int seed, unsigned char bit_mask)
      : gr::block("bsc_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
      // BSC error rate.
      d_error_rate = error_rate;

      // PRNG seed.
      d_seed = seed;

      // PRNG initializer: srand() sets the seed for rand().
      srand(seed);
  
      // Initialize bit mask for encoded alphabet.
      d_bit_mask = bit_mask;
    }

    bsc_bb_impl::~bsc_bb_impl() {
    }

    int bsc_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Yes, this has a slight bias, but it serves our purposes for now.
      // TODO: Rewrite to implement Boost library instead of rand().

      // Loop through bytes
      // TODO: Rewrite this to optimize
      for(int i = 0; i < noutput_items; i++) {
        out[i] = in[i];
        // Loop through bits in the byte
        for(unsigned char j = 0; j < 8; j++) {
          // We only care about the bits set in the bitset
          if(d_bit_mask & (1 << j)) {
            // Bin the random number into 0x0 or 0x1
            if(((double) rand() / RAND_MAX) + 1 < d_error_rate + 1) {
              // Flip the ith bit in the byte
              out[i] ^= 1 << j;
            }
          }
        }
      }

      // Tell runtime system how many input items we consumed on each input stream.
      consume_each(noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
  } /* namespace qitkat */
} /* namespace gr */

