/* -*- c++ -*- */
/* 
 * Copyright 2014 - 2014 Ronald Sadlier - Oak Ridge National Laboratory
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
#include "ecc_repetition_encode_bb_impl.h"

namespace gr {
  namespace qitkat {

    ecc_repetition_encode_bb::sptr ecc_repetition_encode_bb::make(unsigned int repetition) {
      return gnuradio::get_initial_sptr(new ecc_repetition_encode_bb_impl(repetition));
    }

    ecc_repetition_encode_bb_impl::ecc_repetition_encode_bb_impl(unsigned int repetition)
      : gr::sync_interpolator("ecc_repetition_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), repetition) {
      d_repetition = repetition;
    }

    ecc_repetition_encode_bb_impl::~ecc_repetition_encode_bb_impl() {
    }

    int ecc_repetition_encode_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

      // TODO: Rewrite this so it is not O(n^2)
      for(int i = 0; i < noutput_items/d_repetition; i++) {
        for(int j = 0; j < d_repetition; j++) {
          memcpy(&out[i*d_repetition + j], &in[i], sizeof(unsigned char));
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace qitkat */
} /* namespace gr */

