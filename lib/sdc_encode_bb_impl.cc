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
#include "sdc_encode_bb_impl.h"
#include <boost/math/common_factor_rt.hpp>

namespace gr {
  namespace qitkat {

    sdc_encode_bb::sptr sdc_encode_bb::make(int n) {
      return gnuradio::get_initial_sptr(new sdc_encode_bb_impl(n));
    }

    sdc_encode_bb_impl::sdc_encode_bb_impl(int n)
      : gr::block("sdc_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
      // Check if n is within a range we can handle: 2 <= n <= 7
      if(n < 2 || n > 7) {
        std::cerr << "gr-qitkat fatal: invalid n value in sdc_encode_bb";
        exit(-1);
      }

      d_n = (unsigned char)n;

      // We need to figure out how many bits can fit within a quantum state space.
      // The quantum state space has size n^2 while the bit space has size 2^n.
      // We need to fit 2^n in n^2.
      d_num_bits_encoded = 1;
      while(pow(2., 1.*d_num_bits_encoded) <= pow(1.*d_n, 2.)) {
        d_num_bits_encoded++;
      }
      // We always overshoot.
      d_num_bits_encoded--;

      // The number of bytes required each iteration.
      d_num_bytes_required = boost::math::lcm((unsigned char)8, d_num_bits_encoded) / 8;

      // The number of items generated each iteration.
      d_num_flags_output = boost::math::lcm((unsigned char)8, d_num_bits_encoded) / d_num_bits_encoded;
      
      // We can only produce output in blocks.
      set_output_multiple(d_num_flags_output);

      // Set our bitmask.
      d_bitmask = (unsigned char)(pow(2., 1.*d_num_bits_encoded) - 1.0);
    }

    sdc_encode_bb_impl::~sdc_encode_bb_impl() {
    }
    
    void sdc_encode_bb_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
      ninput_items_required[0] = (noutput_items/d_num_flags_output)*d_num_bytes_required;
    }

    int sdc_encode_bb_impl::general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      
      // \fixme: Make the unreachable algorithm below work for certain cases
      out[0] = (in[0]) & 3;
      out[1] = (in[0] >> 2) & 3;
      out[2] = (in[0] >> 4) & 3;
      out[3] = (in[0] >> 6) & 3;
      consume_each(1);
      return 4;
      

      // Create our output flags based on our input byte. This makes our flag pattern like so:
      // 000: 0x0
      // 001: 0x1
      // 010: 0x2
      // 011: 0x3
      // 100: 0x4
      // And so on for any dimension
      // With little endian bit order:
      // eg, 0x1 is sent, 00000001, so it is sent as flag 1, then flag 0, then flag 0, then flag 0.

      // The absolute position within the output stream
      unsigned long outPos(0);
      unsigned long inPos(0);
      
      while(outPos < noutput_items) {
        // The current input byte, counting down. This is within our current cluster within the stream.
        char current_input_byte = d_num_bytes_required-1;

        // The bit position within a byte.
        unsigned char inner_byte_bit_pos = 0;

        // The current output flag we are on.
        unsigned char current_output_flag = 0;

        // Loop through our input bytes.
        while(current_input_byte >= 0) {
          // Check for overflow.
          if(inner_byte_bit_pos + d_num_bits_encoded > 8) {
            // Overflow: the current input byte provides an incomplete output flag.
            out[outPos + current_output_flag] = (in[inPos + current_input_byte] >> inner_byte_bit_pos) & d_bitmask;
            // Move on to the next input byte.
            current_input_byte--;
            // Grab what we need from the next byte and apply it to the same flag, completing it.
            out[outPos + current_output_flag] += (in[inPos + current_input_byte] << (8 - inner_byte_bit_pos)) & d_bitmask;
            // Set our position some distance into the new input byte.
            inner_byte_bit_pos = inner_byte_bit_pos + d_num_bits_encoded - 8;
          } else {
            // No overflow, we have a complete flag.
            out[outPos + current_output_flag] = (in[inPos + current_input_byte] >> inner_byte_bit_pos) & d_bitmask;
            // Move over n bits.
            inner_byte_bit_pos += d_num_bits_encoded;
          }
          // Move on to the next output flag.
          current_output_flag++;
        }
        outPos += d_num_flags_output;
        inPos += d_num_bytes_required;
      }

      // Tell runtime system how many input items we consumed on each input stream.
      consume_each(inPos);

      // Tell runtime system how many output items we produced.
      return outPos;
    }
  } /* namespace qitkat */
} /* namespace gr */

