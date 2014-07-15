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
#include "ecc_hamming74_encode_bb_impl.h"

namespace gr {
  namespace qitkat {

    ecc_hamming74_encode_bb::sptr ecc_hamming74_encode_bb::make() {
      return gnuradio::get_initial_sptr(new ecc_hamming74_encode_bb_impl());
    }

    // Initialize our encode lookup table.
    // In: (in0, in1, in2, in3)
    // Out: (0, p1, p2, in1, p3, in2, in3, in4)
    const unsigned char ecc_hamming74_encode_bb_impl::d_encodeTable[16] = {
      0x0,	// in: 0000 out: (0)0000000
      0x69,	// in: 0001 out: (0)1101001
      0x2a,	// in: 0010 out: (0)0101010
      0x43,	// in: 0011 out: (0)1000011
      0x4c,	// in: 0100 out: (0)1001100
      0x25,	// in: 0101 out: (0)0100101
      0x66,	// in: 0110 out: (0)1100110
      0xf,	// in: 0111 out: (0)0001111
      0x70,	// in: 1000 out: (0)1110000
      0x19,	// in: 1001 out: (0)0011001
      0x5a,	// in: 1010 out: (0)1011010
      0x33,	// in: 1011 out: (0)0110011
      0x3c,	// in: 1100 out: (0)0111100
      0x55,	// in: 1101 out: (0)1010101
      0x16,	// in: 1110 out: (0)0010110
      0x7f	// in: 1111 out: (0)1111111
    };

    ecc_hamming74_encode_bb_impl::ecc_hamming74_encode_bb_impl()
      : gr::sync_interpolator("ecc_hamming74_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), 2) {
    }

    ecc_hamming74_encode_bb_impl::~ecc_hamming74_encode_bb_impl() {
    }

    int ecc_hamming74_encode_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        for(int i = 0; i < noutput_items; i++) {
          // The first half of the incoming byte.
          out[i*2] = d_encodeTable[in[i] & 0x0f];

          // The other half of the incoming byte.
          out[i*2+1] = d_encodeTable[in[i] >> 4];
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace qitkat */
} /* namespace gr */

