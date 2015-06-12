/* -*- c++ -*- */
/* 
 * Copyright 2013, 2014 Ronald J. Sadlier - Oak Ridge National Laboratory
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
#include "sdc_decode_bb_impl.h"
#include <boost/math/common_factor_rt.hpp>

namespace gr {
  namespace qitkat {

    sdc_decode_bb::sptr sdc_decode_bb::make(int n) {
      return gnuradio::get_initial_sptr(new sdc_decode_bb_impl(n));
    }

    sdc_decode_bb_impl::sdc_decode_bb_impl(int n)
      : gr::block("sdc_decode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
      // Check if n is within a range we can handle: 1 <= n <= 7
      if(n < 1 || n > 7) {
        std::cerr << "gr-qitkat fatal: invalid n value in sdc_decode_bb: " << (int)n;
        exit(-1);
      }

      d_n = (unsigned char)n;

      // We need to figure out how many bits can fit within a quantum state space.
      // The quantum state space has size n^2 while the bit space has size 2^n.
      // We need to fit 2^n in n^2. See SDC Encode for the encoding process.
      d_num_bits_encoded = 1;
      if(n != 1) {
        while(pow(2., 1.*d_num_bits_encoded) <= pow(1.*d_n, 2.)) {
          d_num_bits_encoded++;
        }
        // We always overshoot.
        d_num_bits_encoded--;
      }

      // The number of items required each iteration.
      // LCM is always divisible by 8, so this is OK. (Needed for a few lower dimensional cases).
      d_num_flags_required = boost::math::lcm((unsigned char)8, d_num_bits_encoded) / d_num_bits_encoded;

      // The number of bytes generated each iteration.
      // LCM is always divisible by n, so this is OK. (Needed for a few lower dimensional cases).
      d_num_bytes_output = boost::math::lcm((unsigned char)8, d_num_bits_encoded) / (unsigned char)8;
      
      // We can only produce output in blocks.
      set_output_multiple(d_num_bytes_output);
    }

    sdc_decode_bb_impl::~sdc_decode_bb_impl() {
    }
    
    void sdc_decode_bb_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
      ninput_items_required[0] = (noutput_items/d_num_bytes_output)*d_num_flags_required;
    }

    int sdc_decode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // The absolute position within the output stream
      int inPos = 0;
      int outPos = 0;
    
      while(outPos < noutput_items) {
        // The input flag we are currently on. This is within our current cluster within the stream.
        unsigned char current_input_flag = 0;

        // The output byte we are currently on. This is within our current cluster within the stream.
        unsigned char current_output_byte = d_num_bytes_output-1;

        // The bit position within the output byte.
        unsigned char inner_byte_bit_pos = 0;

        // Loop through each input flag.
        while(current_input_flag < d_num_flags_required) {
          // Check for overflow.
          if(inner_byte_bit_pos + d_num_bits_encoded > 8) {
            // Overflow: the current input flag provides an incomplete output byte.
            out[outPos + current_output_byte] += in[inPos + current_input_flag] << inner_byte_bit_pos;
            // Move on to the next output byte.
            current_output_byte--;
            // Grab what we can with the next byte.
            out[outPos + current_output_byte] = in[inPos + current_input_flag] >> (8 - inner_byte_bit_pos);
            // Set our position some distance into the new input flag.
            inner_byte_bit_pos = inner_byte_bit_pos + d_num_bits_encoded - 8;
          } else {
            // No overflow, we have a complete output byte.
            out[outPos + current_output_byte] += in[inPos + current_input_flag] << inner_byte_bit_pos;
            // Move over by n bits.
            inner_byte_bit_pos += d_num_bits_encoded;
          }
          // Move on to the next output flag.
          current_input_flag++;
        }
        outPos += d_num_bytes_output;
        inPos += d_num_flags_required;
      }

      // Tell runtime system how many input items we consumed on each input stream.
      consume_each(inPos);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
  } /* namespace qitkat */
} /* namespace gr */

