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
#include "ber_bf_impl.h"
#include <bitset>

using namespace std;

namespace gr {
  namespace qitkat {

    ber_bf::sptr ber_bf::make(unsigned int num_items, unsigned char bit_mask) {
      return gnuradio::get_initial_sptr(new ber_bf_impl(num_items, bit_mask));
    }

    ber_bf_impl::ber_bf_impl(unsigned int num_items, unsigned char bit_mask)
      : gr::sync_decimator("ber_bf",
              gr::io_signature::make(2, 2, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(float)), num_items) {
      // Initialize frame length.
      d_num_items = num_items;

      // Initialize bit mask for encoded alphabet.
      d_bit_mask = bit_mask;

      // Calculate size of d_bit_mask.
      d_bit_mask_len = bitset<8>(d_bit_mask).count();
    }

    ber_bf_impl::~ber_bf_impl() {
    }

    int ber_bf_impl::work(int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in0 = (const unsigned char *) input_items[0];
      const unsigned char *in1 = (const unsigned char *) input_items[1];
      float *out = (float *) output_items[0];

      // We know noutput_items is a fixed multiple of d_num_items, but not necessarily equal.
      // So we loop through all input items in blocks of length d_num_items.
      unsigned long outputPos(0);
      unsigned long sum(0);
      
      for(unsigned long i = 0; outputPos < noutput_items; i += d_num_items) {
        sum = 0;

        // Calculate BER over frame length
        for(unsigned long j = 0; j < d_num_items; j++) {
         sum += bitset<8>((in0[i+j] ^ in1[i+j]) & d_bit_mask).count();
        }

        // Multiply by number of encoded bits per item to get correct statistics
        out[outputPos] = (float)sum / (d_num_items*d_bit_mask_len);
        outputPos++;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
  } /* namespace qitkat */
} /* namespace gr */

