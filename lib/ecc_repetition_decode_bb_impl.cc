/* -*- c++ -*- */
/*
 * Copyright 2014 Ronald J. Sadlier - Oak Ridge National Laboratory
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
#include "ecc_repetition_decode_bb_impl.h"

#include <numeric>

namespace gr {
  namespace qitkat {

    ecc_repetition_decode_bb::sptr ecc_repetition_decode_bb::make(unsigned int repetition) {
      return gnuradio::get_initial_sptr(new ecc_repetition_decode_bb_impl(repetition));
    }

    ecc_repetition_decode_bb_impl::ecc_repetition_decode_bb_impl(unsigned int repetition)
      : gr::sync_decimator("ecc_repetition_decode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), repetition) {
      d_repetition = repetition;
      d_hamming_middle = repetition/2.0;
    }

    ecc_repetition_decode_bb_impl::~ecc_repetition_decode_bb_impl() {
    }

    int ecc_repetition_decode_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Our reconstructed byte
      std::vector<bool> reconstructed(8, 0);

      // Loop over each bit
      for(int i = 0; i < 8; i++) {
        // Our recovered code word
        std::vector<bool> recovered(d_repetition, 0);

        // Loop over each input byte to get the correct bit for
        // for the code words
        for(int j = 0; j < d_repetition; j++) {
          recovered[j] = (in[j] & (1 << i)) >> i;
        }

        // Check which codeword we have recovered
        if(std::accumulate(recovered.begin(), recovered.end(), 0)> d_hamming_middle) {
          out[0] += 1 << i;
        }
      }

      return 1;
    }
  } /* namespace qitkat */
} /* namespace gr */

